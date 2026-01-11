#ifndef ZAPPY_PLAYER_HXX
#define ZAPPY_PLAYER_HXX

#include <cstddef>
#include <cstdint>
#include <tuple>
#include <vector>

#include "entity.hxx"
#include "team.hxx"

namespace zappy {

using InventorySlot = std::tuple<std::size_t, Entity>;

constexpr std::size_t PLAYER_MAX_LEVEL = 6;

struct Player {
  Team & team;
  std::size_t pos;

  std::uint8_t level;
  std::vector<InventorySlot> inventory;
};

} // namespace zappy

#endif // !ZAPPY_PLAYER_HXX
