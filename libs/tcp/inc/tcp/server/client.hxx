#include <exception>
#include <string_view>
#include <system_error>
#include <vector>

#include <utils/result.hxx>

#include "server.hxx"

namespace tcp::server {

class Server::Client {
public:
  friend class Server;

  Client() = delete;
  Client(Client const &) = delete;
  Client(Client && other) = default;

  Client & operator=(Client const &) = delete;

  sockaddr_in addr() const noexcept;

  void queueMessage(std::string_view const & msg) noexcept;

  utils::Result<std::string, std::system_error> unqueueResponse() noexcept;

private:
  Client(sockaddr_in addr) noexcept;

  sockaddr_in const _addr;

  std::vector<std::uint8_t> _inputBuffer;
  std::vector<std::uint8_t> _outputBuffer;

protected:
};

} // namespace tcp::server
