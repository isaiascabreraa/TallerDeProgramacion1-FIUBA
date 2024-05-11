
#include "common_socket.h"

Socket::Socket(const char* hostname, const char* servname) {
    Resolver resolver(hostname, servname, false);

    int s = -1;
    int skt = -1;
    this->closed = true;

    while (resolver.has_next()) {
        struct addrinfo* addr = resolver.next();

        if (skt != -1)
            ::close(skt);

        skt = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (skt == -1) {
            continue;
        }

        s = connect(skt, addr->ai_addr, addr->ai_addrlen);
        if (s == -1) {
            continue;
        }

        this->closed = false;
        this->skt = skt;
        return;
    }
    int saved_errno = errno;

    if (skt != -1)
        ::close(skt);

    throw LibError(saved_errno, "socket construction failed (connect to %s:%s)",
                   (hostname ? hostname : ""), (servname ? servname : ""));
}

Socket::Socket(const char* servname) {
    Resolver resolver(nullptr, servname, true);

    int s = -1;
    int skt = -1;
    this->closed = true;
    while (resolver.has_next()) {
        struct addrinfo* addr = resolver.next();

        if (skt != -1)
            ::close(skt);

        skt = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (skt == -1) {
            continue;
        }

        int optval = 1;
        s = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
        if (s == -1) {
            continue;
        }

        s = bind(skt, addr->ai_addr, addr->ai_addrlen);
        if (s == -1) {
            continue;
        }

        s = listen(skt, 20);
        if (s == -1) {
            continue;
        }

        this->closed = false;
        this->skt = skt;
        return;
    }

    int saved_errno = errno;

    if (skt != -1)
        ::close(skt);

    throw LibError(saved_errno, "socket construction failed (listen on %s)",
                   (servname ? servname : ""));
}

Socket::Socket(Socket&& other) {
    this->skt = other.skt;
    this->closed = other.closed;

    other.skt = -1;
    other.closed = true;
}

Socket& Socket::operator=(Socket&& other) {

    if (this == &other)
        return *this;

    if (not this->closed) {
        ::shutdown(this->skt, 2);
        ::close(this->skt);
    }

    this->skt = other.skt;
    this->closed = other.closed;
    other.skt = -1;
    other.closed = true;

    return *this;
}

int Socket::recvall(void* data, unsigned int sz, bool* was_closed) {
    chk_skt_or_fail();
    *was_closed = false;

    uint8_t received = 0;

    while (received < sz) {

        uint8_t received_actual = recv(this->skt, (char*)data + received, sz - received, 0);

        if (received_actual == 0) {
            *was_closed = true;
            return received;

        } else if (received_actual == -1) {
            throw LibError(errno, "socket recv failed");
        } else {
            received += received_actual;
            continue;
        }
    }
    return received;
}

int Socket::sendall(const void* data, unsigned int sz, bool* was_closed) {
    chk_skt_or_fail();
    *was_closed = false;

    uint8_t sent = 0;

    while (sent < sz) {

        uint8_t sent_actual = send(this->skt, (char*)data + sent, sz - sent, MSG_NOSIGNAL);
        if (sent_actual == -1) {
            if (errno == EPIPE) {
                *was_closed = true;
                return sent;
            }
            *was_closed = true;
            throw LibError(errno, "socket send failed");

        } else {
            sent += sent_actual;
            continue;
        }
    }

    return sent;
}

Socket::Socket(int skt) {
    this->skt = skt;
    this->closed = false;
}

Socket Socket::accept() {
    chk_skt_or_fail();

    int peer_skt = ::accept(this->skt, nullptr, nullptr);
    if (peer_skt == -1)
        throw LibError(errno, "socket accept failed");

    return Socket(peer_skt);
}

void Socket::shutdown(int how) {
    chk_skt_or_fail();
    if (::shutdown(this->skt, how) == -1) {
        throw LibError(errno, "socket shutdown failed");
    }
    //::shutdown(this->skt, how);
    this->closed = true;
}

int Socket::close() {
    chk_skt_or_fail();
    this->closed = true;
    return ::close(this->skt);
}

Socket::~Socket() {
    if (not this->closed) {
        ::shutdown(this->skt, 2);
        ::close(this->skt);
        //} else {
        //  ::close(this->skt);
    }
}

void Socket::chk_skt_or_fail() const {
    if (skt == -1) {
        throw std::runtime_error("socket with invalid file descriptor (-1), "
                                 "perhaps you are using a *previously moved* "
                                 "socket (and therefore invalid).");
    }
}
