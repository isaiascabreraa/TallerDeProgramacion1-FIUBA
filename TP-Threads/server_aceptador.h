
#ifndef SERVER_ACEPTADOR_H
#define SERVER_ACEPTADOR_H

#include <iostream>
#include <list>
#include <string>
#include <utility>

#include "common_socket.h"
#include "common_thread.h"
#include "server_controlador_partida.h"
#include "server_jugador.h"
#include "server_partida.h"

class Aceptador: public Thread {
private:
    Socket skt;
    bool& server_closed;
    ControladorPartida controlador;
    Partida partida;

public:
    Aceptador(const std::string& servname, bool& server_closed);

    void finalizar_conexion();

    void limpiar_jugadores(std::list<Jugador>& jugadores);

    virtual void run() override;
};

#endif
