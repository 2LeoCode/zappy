#ifndef TCP_SERVER
#define TCP_SERVER

#include <cstddef>
#include <cstdint>
#include <unordered_map>

#include <netinet/in.h>

namespace net {

class TcpServer {
public:
  class Client;

  static TcpServer create(std::uint16_t port, std::size_t maxConn);

  TcpServer() = delete;
  TcpServer(TcpServer const & other) = delete;
  TcpServer(TcpServer && other) = default;

  ~TcpServer() noexcept;

  std::size_t maxConn() const noexcept;
  sockaddr_in addr() const noexcept;

  void listen();

private:
  TcpServer(int socket, sockaddr_in addr, std::size_t maxConn) noexcept;

  int const _socket;
  sockaddr_in const _addr;
  std::size_t const _maxConn;
  std::unordered_map<int, Client> _clients;

protected:
};

} // namespace net

#endif
