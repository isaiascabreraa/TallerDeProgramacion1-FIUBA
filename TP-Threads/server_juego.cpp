
#include "server_juego.h"

Juego::Juego(const std::string& servname): servname(servname) {}

void Juego::run_game() {

    bool server_closed = false;

    Aceptador aceptador(servname, server_closed);
    aceptador.start();
    while (std::cin.get() != 'q') {}
    server_closed = true;
    aceptador.finalizar_conexion();
    aceptador.join();
}
