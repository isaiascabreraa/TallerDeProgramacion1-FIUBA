
#include "common_movimientos.h"

// Pre: -
// Post: Contabiliza los movimientos encontrados.
void Movimientos::contabilizarMovimientos(std::string& result, int& movimientos) {

    std::string palabra;
    std::stringstream stream(result);

    while (stream >> palabra) movimientos++;
}

// Pre: -
// Post: Aplica los combos encontrados.
void Movimientos::localizarCombos(std::string& result) {

    for (const auto& pair: replacements) {

        std::string target = pair.first;
        std::string replacement = pair.second;

        size_t pos = 0;
        while ((pos = result.find(target, pos)) != std::string::npos) {
            result.replace(pos, target.length(), replacement);
            pos += replacement.length();
        }
    }
}


// Pre: -
// Post: Encapsulo los metodos empleados en la clase.
void Movimientos::configurar_movimientos(std::string& result, int& value) {

    localizarCombos(result);
    contabilizarMovimientos(result, value);
}
