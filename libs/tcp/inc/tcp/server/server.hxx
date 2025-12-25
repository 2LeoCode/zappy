#ifndef TCP_SERVER_SERVER
#define TCP_SERVER_SERVER

#include <cstddef>
#include <cstdint>
#include <unordered_map>

#include <netinet/in.h>

namespace tcp::server {

class Server {
public:
  class Client;

  static Server create(std::uint16_t port, std::size_t maxConn);

  Server() = delete;
  Server(Server const & other) = delete;
  Server(Server && other) = default;

  ~Server() noexcept;

  std::size_t maxConn() const noexcept;
  sockaddr_in addr() const noexcept;

  void listen();

private:
  Server(int socket, sockaddr_in addr, std::size_t maxConn) noexcept;

  int const _socket;
  sockaddr_in const _addr;
  std::size_t const _maxConn;
  std::unordered_map<int, Client> _clients;

protected:
};

} // namespace tcp::server

#endif
