
#include <exception>
#include <iostream>

#include "common_protocol_server.h"
#include "common_socket.h"

// Pre: -
// Post: -
int main(int argc, char* argv[]) {
    try {
        int ret = -1;

        const char* servname = NULL;

        if (argc == 2) {
            servname = argv[1];
        } else {
            std::cerr << "Bad program call. Expected " << argv[0] << " <servname>\n";
            return ret;
        }

        ProtocolServer protocolo = ProtocolServer(servname);

        protocolo.accept();

        ret = 0;
        return ret;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
