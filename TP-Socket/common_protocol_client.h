
#ifndef COMMON_PROTOCOL_CLIENT_H
#define COMMON_PROTOCOL_CLIENT_H

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

    std::unordered_map<std::string, uint8_t> word_values = {{"NOP", 0x00},   {"JUMP", 0x01},
                                                            {"RIGHT", 0x02}, {"LEFT", 0x03},
                                                            {"DUCK", 0x04},  {"HIT", 0x05}};

    void enviar_comandos(const std::vector<std::string>& resource);

    void esperar_respuesta(std::vector<char>& respuestas);

public:
    explicit ProtocolClient(const std::string& hostname, const std::string& servname);

    void procesar_comando(const std::vector<std::string>& resource, std::vector<char>& respuestas);

    ProtocolClient(const ProtocolClient&) = delete;
    ProtocolClient& operator=(const ProtocolClient&) = delete;

    ProtocolClient(ProtocolClient&&) = default;
    ProtocolClient& operator=(ProtocolClient&&) = default;
};

#endif
