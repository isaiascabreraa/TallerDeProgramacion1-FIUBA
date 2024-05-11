
#include "server_jugador.h"

Jugador::Jugador(Socket&& socket, ControladorPartida& controlador, unsigned int& id_jugador,
                 bool& server_closed):
        conexion_cliente(std::move(socket)),
        controlador(controlador),
        id_jugador(id_jugador),
        jugador_online(true),
        server_closed(server_closed),
        cola_jugador(),
        send(conexion_cliente, cola_jugador, id_jugador, jugador_online),
        receiver(conexion_cliente, id_jugador, controlador, jugador_online) {}

// Pre: -
// Post: -
bool Jugador::desconectar() {

    if (server_closed) {
        jugador_online = false;
        conexion_cliente.shutdown(2);
        conexion_cliente.close();
    }

    if (not jugador_online) {
        controlador.desconectar_jugador(id_jugador);
        receiver.join();
        send.join();
    }
    return jugador_online;
}

// Pre: -
// Post: -
void Jugador::run() {
    controlador.unirse_a_partida(cola_jugador, id_jugador);
    send.start();
    receiver.start();
}
