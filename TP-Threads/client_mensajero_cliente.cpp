
#include "client_mensajero_cliente.h"

// Pre: -
// Post: -
Mensajero::Mensajero(const std::string& hostname, const std::string& servname):
        protocolo(hostname, servname), respuestas() {}

// Pre: -
// Post: Convierte el mensaje recibido en un formato estandar para el protocolo.
std::vector<std::string> Mensajero::empaquetar_linea(std::string& linea) {

    std::vector<std::string> palabras;
    std::istringstream iss(linea);

    for (std::string s; iss >> s;) palabras.push_back(s);

    return palabras;
}


// Pre: -
// Post: Envia al protocolo determinado la informacion a enviar.
void Mensajero::enviar_mensaje(std::string& linea) {
    if (linea.empty())
        return;

    std::vector<std::string> paquete;
    paquete = empaquetar_linea(linea);
    protocolo.procesar_comando(paquete, respuestas);

    if (not respuestas.empty()) {
        for (const std::string& respuesta: respuestas) {
            std::cout << respuesta << std::endl;
        }
        respuestas.clear();
    }
}
