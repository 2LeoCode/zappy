#include <tcp-server.hxx>

namespace net {

std::size_t TcpServer::maxConn() const noexcept { return _maxConn; }

sockaddr_in TcpServer::addr() const noexcept { return _addr; }

} // namespace net
