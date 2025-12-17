#include <tcp-server.hxx>
#include <tcp-server/client.hxx>

namespace net {

sockaddr_in TcpServer::Client::addr() const noexcept { return _addr; }

} // namespace net
