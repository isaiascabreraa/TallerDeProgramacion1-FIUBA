
#include "client_protocol_client.h"

const uint8_t envio_server = 0x06;
const uint8_t enemigo_muerto = 0x04;
const uint8_t enemigo_revivido = 0x05;

// Pre: -
// Post: -
ProtocolClient::ProtocolClient(const std::string& hostname, const std::string& servname):
        hostname(hostname), skt(hostname.c_str(), servname.c_str()) {}


// Pre: -
// Post: Aplica el protocolo correspondiente antes de enviar la informacion.
void ProtocolClient::enviar_comandos(const std::vector<std::string>& resource) {
    bool was_closed = false;
    bool valor_encontrado = false;
    uint8_t comando = 0;

    for (const auto& word: resource) {

        if (client_comands.find(word) != client_comands.end()) {
            comando = client_comands[word];
            valor_encontrado = true;
        } else {
            continue;
        }
    }
    if (not valor_encontrado)
        return;
    skt.sendall(&comando, sizeof(comando), &was_closed);
}


// Pre: -
// Post: Convierte los valores recibidos en algo entendible para el cliente.
std::string ProtocolClient::empaquetar_mensaje(uint8_t& codigo, uint16_t& cant_vivos,
                                               uint16_t& cant_muertos, uint8_t& evento) {

    std::string mensaje;
    std::string mensaje_evento;
    if (static_cast<int>(evento) == 4) {
        mensaje_evento = "Un enemigo ha muerto. ";
    } else if (static_cast<int>(evento) == 5) {
        mensaje_evento = "Un enemigo ha revivido. ";
    }
    mensaje += mensaje_evento;
    mensaje += std::to_string(static_cast<int>(cant_vivos));
    mensaje += " vivo(s) y ";
    mensaje += std::to_string(static_cast<int>(cant_muertos));
    mensaje += " muerto(s).";

    return mensaje;
}


// Pre: -
// Post: Espera hasta recibir una respuesta del servidor y al recibirla, la procesa.
void ProtocolClient::esperar_respuesta(std::vector<std::string>& respuestas) {
    uint8_t value8a = 0, value8b = 0;
    uint16_t value16a = 0, value16b = 0;
    bool was_closed = false;

    skt.recvall(&value8a, sizeof(value8a), &was_closed);
    if (was_closed)
        return;

    uint16_t values16[2] = {0};
    skt.recvall(&values16, sizeof(values16), &was_closed);
    if (was_closed)
        return;
    value16a = ntohs(values16[0]);
    value16b = ntohs(values16[1]);

    skt.recvall(&value8b, sizeof(value8b), &was_closed);
    if (was_closed)
        return;

    respuestas.push_back(empaquetar_mensaje(value8a, value16a, value16b, value8b));
}

// Pre: -
// Post: Encapsula los metodos emplados dentro del protocolo.
void ProtocolClient::procesar_comando(const std::vector<std::string>& resource,
                                      std::vector<std::string>& respuestas) {
    if (resource.empty())
        return;

    if (resource[0] == "Leer") {
        for (int i = 0; i < std::stoi(resource[1]); i++) esperar_respuesta(respuestas);

    } else if (resource[0] == "Atacar") {
        enviar_comandos(resource);
    }
}
