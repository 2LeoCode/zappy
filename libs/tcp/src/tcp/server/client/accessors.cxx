#include <tcp/server.hxx>

namespace tcp::server {

sockaddr_in Server::Client::addr() const noexcept { return _addr; }

} // namespace tcp::server
