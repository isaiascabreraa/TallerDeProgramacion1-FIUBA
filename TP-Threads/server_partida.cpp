
#include "server_partida.h"

Partida::Partida(ControladorPartida& controlador, bool& server_closed):
        controlador(controlador),
        server_closed(server_closed),
        cantidad_vivos(5),
        cantidad_muertos(0),
        enemigos(5) {}

// Pre: Los valores recibidos deben ser 1 o 2 segun el caso.
// Post: -
void Partida::imprimir_estado(const int& evento) {

    std::string mensaje;
    if (evento == 1) {
        mensaje += "Un enemigo ha muerto. ";
    } else if (evento == 2) {
        mensaje += "Un enemigo ha revivido. ";
    } else {
        return;
    }
    mensaje += std::to_string(cantidad_vivos);
    mensaje += " vivo(s) y ";
    mensaje += std::to_string(cantidad_muertos);
    mensaje += " muerto(s).";
    std::cout << mensaje << std::endl;
}

// Pre:
// Post:
void Partida::notificar_ataque_enemigo(ProtocolServer& protocolo) {
    if (server_closed)
        return;

    for (auto& it: enemigos) {
        if (it.recibir_ataque()) {
            cantidad_vivos--;
            cantidad_muertos++;
            EstadoPartida estado = protocolo.generar_respuesta(cantidad_vivos, cantidad_muertos, 1);
            controlador.cargar_mensaje(estado);
            imprimir_estado(1);
            break;
        }
    }
}

// Pre:
// Post:
void Partida::notificar_resurrecion_enemigos(ProtocolServer& protocolo) {
    if (server_closed)
        return;

    for (auto& it: enemigos) {
        if (it.revivir()) {
            cantidad_vivos++;
            cantidad_muertos--;
            EstadoPartida estado = protocolo.generar_respuesta(cantidad_vivos, cantidad_muertos, 2);
            controlador.cargar_mensaje(estado);
            imprimir_estado(2);
        }
    }
}


// Pre:
// Post:
void Partida::run() {

    // std::fill(enemigos.begin(), enemigos.end(), 0);
    ProtocolServer protocolo = ProtocolServer();

    while (not server_closed) {

        uint8_t value = 0;
        while (controlador.obtener_mensaje(value)) {
            std::string comando = protocolo.traducir_comandos(value);
            if (comando == "Atacar")
                notificar_ataque_enemigo(protocolo);
        }
        notificar_resurrecion_enemigos(protocolo);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
