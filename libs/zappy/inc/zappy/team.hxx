#ifndef ZAPPY_TEAM_HXX
#define ZAPPY_TEAM_HXX

#include <array>
#include <memory>

namespace zappy {

struct Player;

constexpr std::size_t PLAYERS_PER_TEAM = 6;

using Team = std::array<std::unique_ptr<Player>, PLAYERS_PER_TEAM>;

} // namespace zappy

#endif // !ZAPPY_TEAM_HXX
