
#ifndef COMMON_PROTOCOL_SERVER_H
#define COMMON_PROTOCOL_SERVER_H

#include <string>
#include <variant>
#include <vector>

#include <arpa/inet.h>

#include "common_queue.h"
#include "common_thread.h"
#include "server_estado_partida.h"

class ProtocolServer {
private:
public:
    ProtocolServer();

    std::string traducir_comandos(const uint8_t& valor);

    EstadoPartida generar_respuesta(int& enemigos_vivos, int& enemigos_muertos, const int& evento);
};

#endif
