#include <system_error>

#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <tcp/server.hxx>

constexpr std::size_t MAX_EVENTS = 32;
constexpr std::size_t BUF_SIZE = 4096;

namespace tcp::server {
void Server::listen() {
  if (::listen(_socket, SOMAXCONN) == -1) {
    throw std::system_error();
  }

  int const pfd = epoll_create1(0);

  epoll_event ev[MAX_EVENTS] = {};

  epoll_event serverEv = {
      .events = EPOLLIN,
      .data = {
          .fd = _socket,
      }
  };

  if (epoll_ctl(pfd, EPOLL_CTL_ADD, _socket, &serverEv) == -1) {
    throw std::system_error();
  }

  uint8_t buffer[BUF_SIZE];

  bool stopped = false;

  while (!stopped) {
    int const nfds = epoll_wait(pfd, ev, MAX_EVENTS, -1);

    if (nfds == -1) {
      // TODO: handle error more gracefully
      throw std::system_error();
    }

    for (int i = 0; i < nfds; ++i) {
      if (ev[i].data.fd == _socket) {

        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        int clientSocket = accept(
            _socket, reinterpret_cast<sockaddr *>(&clientAddr), &clientAddrLen
        );

        if (clientSocket == -1) {
          continue;
        }

        if (_clients.size() == _maxConn) {
          close(clientSocket);
          continue;
        }

        epoll_event clientEv = {
            .events = EPOLLIN | EPOLLOUT,
            .data = {
                .fd = _socket,
            }
        };

        if (epoll_ctl(pfd, EPOLL_CTL_ADD, clientSocket, &clientEv) == -1) {
          close(clientSocket);
          continue;
        }

        _clients.emplace(clientSocket, Client(clientAddr));
      } else {
        if (ev[i].events & EPOLLIN) {
          int const fd = ev[i].data.fd;
          ssize_t bytesRead;

          do {
            bytesRead = recv(fd, buffer, BUF_SIZE, 0);
            if (bytesRead == -1) {
              _clients.erase(fd);

              epoll_ctl(pfd, EPOLL_CTL_DEL, fd, nullptr);
              close(fd);
            } else {
              auto & client = _clients.at(fd);

              client._inputBuffer.insert(
                  client._inputBuffer.end(), buffer, buffer + bytesRead
              );
            }
          } while (bytesRead > 0);
        }

        if (ev[i].events & EPOLLOUT) {
          int const fd = ev[i].data.fd;
          auto & client = _clients.at(fd);

          if (!client._outputBuffer.empty()) {
            auto const bytesWrote = send(
                fd, client._outputBuffer.data(), client._outputBuffer.size(), 0
            );

            if (bytesWrote == -1) {
              _clients.erase(fd);

              epoll_ctl(pfd, EPOLL_CTL_DEL, fd, nullptr);
              close(fd);
            } else {
              client._outputBuffer.erase(
                  client._outputBuffer.begin(),
                  client._outputBuffer.begin() + bytesWrote
              );
            }
          }
        }
      }
    }
  }
}

} // namespace tcp::server
