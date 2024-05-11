
#include <exception>
#include <fstream>
#include <iostream>

#include "client_mensajero_cliente.h"

// Pre: -
// Post: -
int main(int argc, char* argv[]) {
    try {
        int ret = -1;

        if (argc != 3) {
            std::cerr << "Bad program call. Expected " << argv[0] << " without arguments.\n";
            return ret;
        }

        Mensajero mensajero = Mensajero(argv[1], argv[2]);

        std::string linea;
        while (std::getline(std::cin, linea)) {

            if (linea == "Salir")
                break;

            mensajero.enviar_mensaje(linea);
        }

        ret = 0;

        return ret;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.";
        return -1;
    }
}
