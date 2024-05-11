#ifndef CLIENT_MENSAJERO_CLIENTE_H
#define CLIENT_MENSAJERO_CLIENTE_H

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <arpa/inet.h>

#include "client_protocol_client.h"


class Mensajero {

private:
    ProtocolClient protocolo;
    std::vector<std::string> respuestas;

    std::vector<std::string> empaquetar_linea(std::string& linea);

public:
    explicit Mensajero(const std::string& hostname, const std::string& servname);

    void enviar_mensaje(std::string& linea);

    Mensajero(const Mensajero&) = delete;
    Mensajero& operator=(const Mensajero&) = delete;

    Mensajero(Mensajero&&) = default;
    Mensajero& operator=(Mensajero&&) = default;
};

#endif
