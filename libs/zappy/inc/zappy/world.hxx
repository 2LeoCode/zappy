#ifndef ZAPPY_WORLD_HXX
#define ZAPPY_WORLD_HXX

#include <vector>

#include "entity.hxx"
#include "team.hxx"

namespace zappy {

struct World {
  std::vector<Team> teams;

  std::size_t x, y;
  std::vector<Entity> data;

  Entity & entityAt(std::size_t x, std::size_t y);
  Entity const & entityAt(std::size_t x, std::size_t y) const;
};

World randomWorld(std::size_t teamCount, size_t x, size_t y);

} // namespace zappy

#endif // !ZAPPY_WORLD_HXX
