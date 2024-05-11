
#ifndef SERVER_PARTIDA_H
#define SERVER_PARTIDA_H

#include <chrono>
#include <functional>
#include <string>
#include <thread>
#include <variant>
#include <vector>

#include "common_queue.h"
#include "common_thread.h"
#include "server_controlador_partida.h"
#include "server_enemigo.h"
#include "server_estado_partida.h"
#include "server_protocol_server.h"

class Partida: public Thread {
private:
    ControladorPartida& controlador;
    bool& server_closed;
    int cantidad_vivos;
    int cantidad_muertos;
    std::vector<Enemigo> enemigos;

    void imprimir_estado(const int& evento);

    void notificar_ataque_enemigo(ProtocolServer& protocolo);

    void notificar_resurrecion_enemigos(ProtocolServer& protocolo);

public:
    Partida(ControladorPartida& controlador, bool& server_closed);

    virtual void run() override;

    Partida(const Partida&) = delete;
    Partida& operator=(const Partida&) = delete;

    Partida(Partida&&);
    Partida& operator=(Partida&&);
};

#endif
