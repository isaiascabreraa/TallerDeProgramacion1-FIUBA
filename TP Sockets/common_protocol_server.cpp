
#include "common_protocol_server.h"

// Pre: -
// Post: -
ProtocolServer::ProtocolServer(const std::string& servname): skt(servname.c_str()), movs() {}

// Pre: -
// Post: Recibe informacion y la almacena en un string hasta que encuentre un caracter 'NOP'.
void ProtocolServer::obtenerLinea(Socket& peer, std::string& result, bool& was_closed) {

    bool findelectura = false;
    uint8_t value = 0;

    // Recibir información hasta encontrar el valor 0
    while (findelectura != true) {
        peer.recvall(&value, sizeof(value), &was_closed);
        if (was_closed)
            break;

        if (value != 0) {

            if (!result.empty())
                result += ' ';

            result += value_to_word[value];
        } else {
            findelectura = true;
        }
    }
}


// Pre: -
// Post: Aceppt nos bloqueara hasta que algún cliente se conecte a nosotros.
void ProtocolServer::accept() {
    bool server_closed = false;

    int contador_movimientos = 0;
    Socket peer = this->skt.accept();

    while (not server_closed) {
        std::string result = "";
        uint16_t cantidad_caracteres = 0;

        obtenerLinea(peer, result, server_closed);
        if (server_closed)
            break;

        movs.configurar_movimientos(result, contador_movimientos);
        cantidad_caracteres = htons((result.size()));

        peer.sendall(&cantidad_caracteres, sizeof(cantidad_caracteres), &server_closed);
        if (server_closed)
            break;
        peer.sendall(&result[0], sizeof(uint8_t) * result.size(), &server_closed);
        if (server_closed)
            break;
    }
    std::cout << "Actions: " << contador_movimientos << "\n";
}
