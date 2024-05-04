#ifndef COMMON_MENSAJERO_H
#define COMMON_MENSAJERO_H

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <arpa/inet.h>

#include "common_protocol_client.h"


class Mensajero {

private:
    ProtocolClient protocolo;
    std::vector<char> respuestas;

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
