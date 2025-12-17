#include <arpa/inet.h>
#include <unistd.h>

#include <tcp-server.hxx>
#include <tcp-server/client.hxx>

namespace net {

TcpServer::TcpServer(
    int const socket, sockaddr_in const addr, std::size_t const maxConn
) noexcept
    : _socket(socket), _addr(addr), _maxConn(maxConn) {}

TcpServer::~TcpServer() noexcept {
  close(_socket);
  for (auto const & [fd, _] : _clients) {
    close(fd);
  }
}

} // namespace net
