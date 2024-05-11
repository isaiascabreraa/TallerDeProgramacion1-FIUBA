
#include "server_controlador_partida.h"

ControladorPartida::ControladorPartida(bool& server_closed):
        shared_queues(), partida_queue(), server_closed(server_closed) {}

// Pre:
// Post: Añade la referencia de la cola del jugador a las de la partida.
void ControladorPartida::unirse_a_partida(Queue<EstadoPartida>& cola_jugador,
                                          unsigned int& id_jugador) {
    if (server_closed)
        return;

    std::unique_lock<std::mutex> lck(mtx_shared_queue);

    auto resultado = shared_queues.emplace(id_jugador, std::ref(cola_jugador));

    if (!resultado.second) {
        // Nunca deberia pasar que dos jugadores tengan el mismo id.
        std::cout << "Ya existe una Queue con el ID del jugador en el map.\n" << std::endl;
    }
}

// Pre:
// Post: Elimina de nuestra shared_queues la queue del jugador desconectado.
void ControladorPartida::desconectar_jugador(unsigned int& id_jugador) {

    std::unique_lock<std::mutex> lck(mtx_shared_queue);

    auto it = shared_queues.find(id_jugador);
    if (it != shared_queues.end()) {
        it->second.get().close();
        shared_queues.erase(it);
    }
}

// Pre:
// Post: Carga los valores de la partida a todas las queue.
void ControladorPartida::cargar_mensaje(const EstadoPartida& mensaje) {

    std::unique_lock<std::mutex> lck(mtx_shared_queue);

    for (auto& par: shared_queues) {
        Queue<EstadoPartida>& cola_jugador = par.second.get();
        cola_jugador.push(mensaje);
    }
}

// Pre:
// Post: Es la funcion que carga elementos a la partida queue.
void ControladorPartida::cargar_valor(const uint8_t& value) {
    if (server_closed)
        return;

    try {
        partida_queue.try_push(value);
    } catch (const std::exception& e) {
        if (not server_closed)
            std::cerr << "Se capturó una excepción: " << e.what() << "\n";
    }
}

// Pre:
// Post: Es la funcion que le devuelve a partida el elemento del pop().
bool ControladorPartida::obtener_mensaje(uint8_t& value) {
    if (server_closed)
        return false;

    try {
        return partida_queue.try_pop(value);

    } catch (const std::exception& e) {
        if (not server_closed)
            std::cerr << "Se capturó una excepción: " << e.what() << "\n";

        return false;
    }
}
