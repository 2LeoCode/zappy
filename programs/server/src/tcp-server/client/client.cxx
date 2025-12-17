#include <tcp-server.hxx>
#include <tcp-server/client.hxx>

namespace net {

TcpServer::Client::Client(sockaddr_in addr) noexcept : _addr(addr) {}

} // namespace net
