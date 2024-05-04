
#include "common_protocol_client.h"

// Pre: -
// Post: -
ProtocolClient::ProtocolClient(const std::string& hostname, const std::string& servname):
        hostname(hostname), skt(hostname.c_str(), servname.c_str()) {}


// Pre: -
// Post: Aplica el protocolo correspondiente antes de enviar la informacion.
void ProtocolClient::enviar_comandos(const std::vector<std::string>& resource) {
    bool was_closed = false;

    uint8_t valor;
    std::vector<uint8_t> comandos;

    for (const auto& word: resource) {

        if (word_values.find(word) != word_values.end()) {
            comandos.push_back(word_values[word]);
        } else {
            continue;
        }
    }

    int cantidad_comandos = comandos.size();
    skt.sendall(comandos.data(), sizeof(valor) * cantidad_comandos, &was_closed);

    valor = word_values["NOP"];
    skt.sendall(&valor, sizeof(valor), &was_closed);
}


// Pre: -
// Post: Espera hasta recibir una respuesta del servidor y al recibirla, la procesa.
void ProtocolClient::esperar_respuesta(std::vector<char>& respuestas) {

    bool was_closed = false;
    uint16_t response_length = 0;

    skt.recvall(&response_length, sizeof(response_length), &was_closed);

    response_length = ntohs(response_length);
    std::vector<char> response(response_length);

    skt.recvall(response.data(), response_length * sizeof(uint8_t), &was_closed);

    respuestas = response;
}

// Pre: -
// Post: Encapsula los metodos emplados dentro del protocolo.
void ProtocolClient::procesar_comando(const std::vector<std::string>& resource,
                                      std::vector<char>& respuestas) {
    enviar_comandos(resource);
    esperar_respuesta(respuestas);
}
