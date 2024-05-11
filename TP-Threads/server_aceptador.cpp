
#include "server_aceptador.h"

Aceptador::Aceptador(const std::string& servname, bool& server_closed):
        skt(servname.c_str()),
        server_closed(server_closed),
        controlador(server_closed),
        partida(controlador, server_closed) {}

// Pre: -
// Post: -
void Aceptador::finalizar_conexion() {
    skt.shutdown(2);
    skt.close();
}

// Pre: -
// Post: -
void Aceptador::limpiar_jugadores(std::list<Jugador>& jugadores) {

    auto it = jugadores.begin();
    while (it != jugadores.end()) {
        if (!it->desconectar()) {
            it = jugadores.erase(it);
        } else {
            it++;
        }
    }

    if (server_closed)
        jugadores.clear();
}

// Pre: -
// Post: -
void Aceptador::run() {

    std::list<Jugador> jugadores;
    try {
        partida.start();
        unsigned int identificador_jugadores = 0;

        while (not server_closed) {

            Socket peer = skt.accept();
            if (server_closed)
                break;

            jugadores.emplace_back(std::move(peer), controlador, identificador_jugadores,
                                   server_closed);
            jugadores.back().run();
            identificador_jugadores++;

            limpiar_jugadores(jugadores);
        }


    } catch (const std::exception& e) {
        if (not server_closed)
            std::cerr << "Se capturó una excepción: " << e.what() << "\n";

        limpiar_jugadores(jugadores);
        partida.join();

    } catch (...) {
        std::cerr << "Se capturó una excepción desconocida.\n";
    }
}
