#include <cstddef>
#include <cstdint>
#include <system_error>

#include <netinet/in.h>
#include <sys/socket.h>

#include <tcp/server.hxx>

namespace tcp::server {

Server Server::create(std::uint16_t const port, std::size_t const maxConn) {
  int const sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (sockfd == -1) {
    throw std::system_error();
  }

  sockaddr_in const addr = {
      .sin_family = AF_INET,
      .sin_port = htons(port),
      .sin_addr =
          {
              .s_addr = INADDR_ANY,
          },
      .sin_zero = {},
  };

  socklen_t const addr_len = sizeof(addr);

  if (bind(sockfd, reinterpret_cast<sockaddr const *>(&addr), addr_len) == -1) {
    throw std::system_error();
  }

  return Server(sockfd, addr, maxConn);
}

} // namespace tcp::server
