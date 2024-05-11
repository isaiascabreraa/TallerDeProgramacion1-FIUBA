
#ifndef SERVER_ENEMIGO_H
#define SERVER_ENEMIGO_H

class Enemigo {
private:
    bool esta_vivo;
    int turnos_resurreccion;

public:
    Enemigo();

    bool recibir_ataque();

    bool revivir();

    Enemigo(const Enemigo&) = delete;
    Enemigo& operator=(const Enemigo&) = delete;
};

#endif
