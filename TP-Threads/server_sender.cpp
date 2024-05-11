
#include "server_sender.h"

Sender::Sender(Socket& socket, Queue<EstadoPartida>& cola_jugador, const unsigned int& id_sender,
               bool& jugador_online):
        skt(socket),
        cola_jugador(cola_jugador),
        id_sender(id_sender),
        jugador_sigue_activo(jugador_online) {}

// Pre: -
// Post: -
void Sender::run() {

    bool client_closed = false;

    try {
        while (jugador_sigue_activo) {

            EstadoPartida estado = cola_jugador.pop();
            skt.sendall(&estado, sizeof(estado), &client_closed);
            if (client_closed)
                break;
        }

    } catch (const std::exception& e) {
        if (jugador_sigue_activo)
            std::cerr << "Se capturó una excepción: " << e.what() << "\n";
    }

    jugador_sigue_activo = false;
}
