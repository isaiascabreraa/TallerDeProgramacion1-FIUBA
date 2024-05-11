
#ifndef SERVER_CONTROLADOR_PARTIDA_H
#define SERVER_CONTROLADOR_PARTIDA_H

#include <condition_variable>
#include <map>
#include <mutex>
#include <string>
#include <variant>
#include <vector>

#include "common_queue.h"
#include "common_socket.h"
#include "common_thread.h"
#include "server_estado_partida.h"

class ControladorPartida {
private:
    std::map<unsigned int, std::reference_wrapper<Queue<EstadoPartida>>> shared_queues;
    Queue<uint8_t> partida_queue;
    bool& server_closed;

    std::mutex mtx_shared_queue;

public:
    explicit ControladorPartida(bool& server_closed);

    void unirse_a_partida(Queue<EstadoPartida>& cola_jugador, unsigned int& id_jugador);
    void desconectar_jugador(unsigned int& id_jugador);

    void cargar_mensaje(const EstadoPartida& mensaje);

    bool obtener_mensaje(uint8_t& value);
    void cargar_valor(const uint8_t& value);

    ControladorPartida(const ControladorPartida&) = delete;
    ControladorPartida& operator=(const ControladorPartida&) = delete;

    ControladorPartida(ControladorPartida&&);
    ControladorPartida& operator=(ControladorPartida&&);
};

#endif
