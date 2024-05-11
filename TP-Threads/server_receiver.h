
#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "common_queue.h"
#include "common_socket.h"
#include "common_thread.h"
#include "server_controlador_partida.h"

class Receiver: public Thread {
private:
    Socket& skt;
    ControladorPartida& controlador;
    unsigned int id_receiver;
    bool& jugador_sigue_activo;

public:
    Receiver(Socket& socket, const unsigned int& id_receiver, ControladorPartida& controlador,
             bool& jugador_online);

    virtual void run() override;
};

#endif
