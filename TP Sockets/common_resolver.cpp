
#include "common_resolver.h"

#include <stdexcept>

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "common_liberror.h"
#include "common_resolvererror.h"

Resolver::Resolver(const char* hostname, const char* servname, bool is_passive) {
    struct addrinfo hints;
    this->result = this->_next = nullptr;


    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = is_passive ? AI_PASSIVE : 0;

    int s = getaddrinfo(hostname, servname, &hints, &this->result);


    if (s != 0) {
        if (s == EAI_SYSTEM) {

            throw LibError(errno, "Name resolution failed for hostname '%s' y servname '%s'",
                           (hostname ? hostname : ""), (servname ? servname : ""));

        } else {

            throw ResolverError(s);
        }
    }

    this->_next = this->result;
}

Resolver::Resolver(Resolver&& other) {

    this->result = other.result;
    this->_next = other._next;

    other.result = nullptr;
    other._next = nullptr;
}

Resolver& Resolver::operator=(Resolver&& other) {

    if (this == &other)
        return *this;

    if (this->result)
        freeaddrinfo(this->result);

    this->result = other.result;
    this->_next = other._next;
    other.result = nullptr;
    other._next = nullptr;

    return *this;
}

bool Resolver::has_next() {
    chk_addr_or_fail();
    return this->_next != NULL;
}

struct addrinfo* Resolver::next() {
    chk_addr_or_fail();
    struct addrinfo* ret = this->_next;
    this->_next = ret->ai_next;
    return ret;
}

Resolver::~Resolver() {

    if (this->result)
        freeaddrinfo(this->result);
}


void Resolver::chk_addr_or_fail() const {
    if (result == nullptr) {
        throw std::runtime_error("addresses list is invalid (null), "
                                 "perhaps you are using a *previously moved* "
                                 "resolver (and therefore invalid).");
    }
}
