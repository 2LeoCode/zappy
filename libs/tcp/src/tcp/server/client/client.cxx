#include <tcp/server.hxx>

namespace tcp::server {

Server::Client::Client(sockaddr_in addr) noexcept : _addr(addr) {}

} // namespace tcp::server
