#include <cstddef>

#include <arpa/inet.h>
#include <unistd.h>

#include <tcp/server.hxx>

namespace tcp::server {

Server::Server(
    int const socket, sockaddr_in const addr, std::size_t const maxConn
) noexcept
    : _socket(socket), _addr(addr), _maxConn(maxConn) {}

Server::~Server() noexcept {
  close(_socket);
  for (auto const & [fd, _] : _clients) {
    close(fd);
  }
}

} // namespace tcp::server
