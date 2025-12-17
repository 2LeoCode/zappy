#ifndef TCP_SERVER_CLIENT_HXX
#define TCP_SERVER_CLIENT_HXX

#include <vector>

#include <netinet/in.h>
#include <sys/epoll.h>

#include <tcp-server.hxx>

namespace net {

class TcpServer::Client {
public:
  friend class TcpServer;

  Client() = delete;
  Client(Client const &) = delete;
  Client(Client && other) = default;

  Client & operator=(Client const &) = delete;

  sockaddr_in addr() const noexcept;

private:
  Client(sockaddr_in addr) noexcept;

  sockaddr_in const _addr;

  std::vector<std::uint8_t> _inputBuffer;
  std::vector<std::uint8_t> _outputBuffer;

protected:
};

} // namespace net

#endif
