#ifndef COMMON_PROTOCOL_SERVER_H
#define COMMON_PROTOCOL_SERVER_H

#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common_movimientos.h"
#include "common_socket.h"

class ProtocolServer {
private:
    const std::string servname;
    Socket skt;
    Movimientos movs;

    std::unordered_map<uint8_t, std::string> value_to_word = {{0x01, "JUMP"}, {0x05, "HIT"},
                                                              {0x00, "NOP"},  {0x02, "RIGHT"},
                                                              {0x03, "LEFT"}, {0x04, "DUCK"}};

    void obtenerLinea(Socket& peer, std::string& result, bool& was_closed);

public:
    explicit ProtocolServer(const std::string& servname);

    void accept();

    ProtocolServer(const ProtocolServer&) = delete;
    ProtocolServer& operator=(const ProtocolServer&) = delete;


    ProtocolServer(ProtocolServer&&) = default;
    ProtocolServer& operator=(ProtocolServer&&) = default;
};

#endif
