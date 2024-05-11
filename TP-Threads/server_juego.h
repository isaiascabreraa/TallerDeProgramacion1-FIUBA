
#ifndef SERVER_JUEGO_H
#define SERVER_JUEGO_H

#include <string>

#include "common_queue.h"
#include "common_thread.h"
#include "server_aceptador.h"
#include "server_partida.h"

class Juego {
private:
    const std::string& servname;

public:
    explicit Juego(const std::string& servname);

    void run_game();

    Juego(const Juego&) = delete;
    Juego& operator=(const Juego&) = delete;
};

#endif
