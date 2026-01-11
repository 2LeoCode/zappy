#ifndef ZAPPY_ENTITY_HXX
#define ZAPPY_ENTITY_HXX

#include <cstdint>

namespace zappy {

enum class Entity : std::uint8_t {
  air,
  nourriture,
  linemate,
  deraumere,
  sibur,
  mendiane,
  phiras,
  thystame,
};

constexpr auto ENTITY_MIN = static_cast<std::uint8_t>(Entity::air);
constexpr auto ENTITY_MAX = static_cast<std::uint8_t>(Entity::thystame);

} // namespace zappy

#endif // !ZAPPY_ENTITY_HXX
