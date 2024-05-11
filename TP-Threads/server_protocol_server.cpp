
#include "server_protocol_server.h"

const uint8_t envio_server = 0x06;
const uint8_t enemigo_muerto = 0x04;
const uint8_t enemigo_revivido = 0x05;

ProtocolServer::ProtocolServer() {}

// Pre: -
// Post: Traduce la informacion recibida del cliente al lenguaje de juego.
std::string ProtocolServer::traducir_comandos(const uint8_t& valor) {
    std::string comando = "";

    if (valor == 0x03) {
        comando = "Atacar";
    }
    return comando;
}

// Pre: -
// Post: Genera una respuesta en base al estado del juego.
EstadoPartida ProtocolServer::generar_respuesta(int& cantidad_vivos, int& cantidad_muertos,
                                                const int& evento) {

    uint8_t evento_recibido = 0;
    if (evento == 1) {
        evento_recibido = enemigo_muerto;
    } else if (evento == 2) {
        evento_recibido = enemigo_revivido;
    } else {
        std::cout << "El estado no se creo correctamente" << std::endl;
    }

    EstadoPartida estado(envio_server, htons(static_cast<uint16_t>(cantidad_vivos)),
                         htons(static_cast<uint16_t>(cantidad_muertos)), evento_recibido);
    return estado;
}
