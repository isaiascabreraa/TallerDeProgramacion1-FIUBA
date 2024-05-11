#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

#include <stdexcept>

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "common_liberror.h"
#include "common_resolver.h"

class Socket {
private:
    int skt;
    bool closed;

    explicit Socket(int skt);

    void chk_skt_or_fail() const;

public:
    Socket(const char* hostname, const char* servname);

    explicit Socket(const char* servname);

    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    Socket(Socket&&);
    Socket& operator=(Socket&&);

    int sendall(const void* data, unsigned int sz, bool* was_closed);
    int recvall(void* data, unsigned int sz, bool* was_closed);

    Socket accept();

    void shutdown(int how);

    int close();

    ~Socket();
};
#endif
