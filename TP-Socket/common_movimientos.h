#ifndef COMMON_MOVIMIENTOS_H
#define COMMON_MOVIMIENTOS_H

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>

class Movimientos {
private:
    std::vector<std::pair<std::string, std::string>> replacements = {
            {"JUMP JUMP HIT", "UPPERCUT"},
            {"HIT DUCK LEFT", "SIDEKICK"},
            {"LEFT RIGHT JUMP HIT", "HIGHKICK"}};

    void localizarCombos(std::string& result);

    void contabilizarMovimientos(std::string& result, int& value);

public:
    Movimientos() = default;

    void configurar_movimientos(std::string& result, int& value);

    Movimientos(const Movimientos&) = delete;
    Movimientos& operator=(const Movimientos&) = delete;
};

#endif
