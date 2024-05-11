
#include "server_receiver.h"

Receiver::Receiver(Socket& socket, const unsigned int& id_receiver, ControladorPartida& controlador,
                   bool& jugador_online):
        skt(socket),
        controlador(controlador),
        id_receiver(id_receiver),
        jugador_sigue_activo(jugador_online) {}

// Pre: -
// Post: Espera pacientemente a recibir informacion del cliente. Cuando la recibe se la deriva al
// protocolo.
void Receiver::run() {

    bool client_closed = false;
    uint8_t value = 0;

    while (jugador_sigue_activo) {

        skt.recvall(&value, sizeof(value), &client_closed);
        if (client_closed)
            break;

        controlador.cargar_valor(value);
    }
    jugador_sigue_activo = false;
}
