
#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <variant>
#include <vector>

#include "common_queue.h"
#include "common_socket.h"
#include "common_thread.h"
#include "server_controlador_partida.h"
#include "server_estado_partida.h"

class Sender: public Thread {
private:
    Socket& skt;
    Queue<EstadoPartida>& cola_jugador;
    unsigned int id_sender;
    bool& jugador_sigue_activo;

public:
    Sender(Socket& socket, Queue<EstadoPartida>& cola_jugador, const unsigned int& id_sender,
           bool& jugador_online);

    virtual void run() override;
};

#endif
