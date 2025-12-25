#include <tcp/server.hxx>

namespace tcp::server {

std::size_t Server::maxConn() const noexcept { return _maxConn; }

sockaddr_in Server::addr() const noexcept { return _addr; }

} // namespace tcp::server
