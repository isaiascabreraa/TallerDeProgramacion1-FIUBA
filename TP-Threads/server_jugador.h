
#ifndef SERVER_JUGADOR_H
#define SERVER_JUGADOR_H

#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <variant>

#include "common_queue.h"
#include "common_socket.h"
#include "common_thread.h"
#include "server_controlador_partida.h"
#include "server_estado_partida.h"
#include "server_receiver.h"
#include "server_sender.h"

class Jugador {
private:
    Socket conexion_cliente;
    ControladorPartida& controlador;
    unsigned int id_jugador;
    bool jugador_online;
    bool& server_closed;
    Queue<EstadoPartida> cola_jugador;
    Sender send;
    Receiver receiver;

public:
    Jugador(Socket&& socket, ControladorPartida& controlador, unsigned int& id_jugador,
            bool& server_closed);

    bool desconectar();

    void run();

    Jugador(const Jugador&) = delete;
    Jugador& operator=(const Jugador&) = delete;

    Jugador(Jugador&&);
    Jugador& operator=(Jugador&&);
};

#endif
