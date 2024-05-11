
#ifndef ESTADO_PARTIDA_H
#define ESTADO_PARTIDA_H


struct EstadoPartida {
    uint8_t codigo;
    uint16_t enemigos_vivos;
    uint16_t enemigos_muertos;
    uint8_t estado_partida;

    EstadoPartida(const uint8_t codigo, const uint16_t enemigos_vivos,
                  const uint16_t enemigos_muertos, const uint8_t estado_partida):
            codigo(codigo),
            enemigos_vivos(enemigos_vivos),
            enemigos_muertos(enemigos_muertos),
            estado_partida(estado_partida) {}


} __attribute__((packed));

#endif
