
#include "server_enemigo.h"

// Pre: -
// Post: -
Enemigo::Enemigo(): esta_vivo(true), turnos_resurreccion(0) {}

// Pre: -
// Post: -
bool Enemigo::recibir_ataque() {

    bool recibio_ataque = false;

    if (esta_vivo) {
        turnos_resurreccion = 15;
        esta_vivo = false;
        recibio_ataque = true;
    }
    return recibio_ataque;
}

// Pre: -
// Post: -
bool Enemigo::revivir() {

    bool revivio = false;

    if (turnos_resurreccion == 1) {
        turnos_resurreccion = 15;
        esta_vivo = true;
        revivio = true;
    } else if (turnos_resurreccion > 1) {
        turnos_resurreccion--;
    }

    return revivio;
}
