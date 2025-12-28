#ifndef TCP_CLIENT_CLIENT_HXX
#define TCP_CLIENT_CLIENT_HXX

#include <string_view>

#include <netinet/in.h>

namespace tcp::client {

class Client {
public:
  static Client create(std::string_view const & serverAddr);

  Client() = delete;
  Client(Client const &) = delete;
  Client(Client && other) = default;

  sockaddr_in addr() const noexcept;

  void queueMessage(std::string_view const & message) const noexcept;

  std::string unqueueResponse() noexcept;

protected:
private:
  Client(int socket, sockaddr_in addr, sockaddr_in serverAddr);

  int const _socket;
  sockaddr_in _addr;
  sockaddr_in _serverAddr;
};

} // namespace tcp::client

#endif
