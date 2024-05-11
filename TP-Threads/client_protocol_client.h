
#ifndef CLIENT_PROTOCOL_CLIENT_H
#define CLIENT_PROTOCOL_CLIENT_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <arpa/inet.h>

#include "common_socket.h"

class ProtocolClient {

private:
    const std::string hostname;
    const std::string servname;
    Socket skt;

    std::unordered_map<std::string, uint8_t> client_comands = {{"Atacar", 0x03}};

    void enviar_comandos(const std::vector<std::string>& resource);

    void esperar_respuesta(std::vector<std::string>& respuestas);

    std::string empaquetar_mensaje(uint8_t& codigo, uint16_t& cant_vivos, uint16_t& cant_muertos,
                                   uint8_t& evento);

public:
    explicit ProtocolClient(const std::string& hostname, const std::string& servname);

    void procesar_comando(const std::vector<std::string>& resource,
                          std::vector<std::string>& respuestas);

    ProtocolClient(const ProtocolClient&) = delete;
    ProtocolClient& operator=(const ProtocolClient&) = delete;

    ProtocolClient(ProtocolClient&&) = default;
    ProtocolClient& operator=(ProtocolClient&&) = default;
};

#endif
