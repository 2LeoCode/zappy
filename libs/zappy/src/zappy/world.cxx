#include <memory>
#include <random>
#include <set>

#include <utils.hxx>
#include <zappy/player.hxx>
#include <zappy/world.hxx>

#include "zappy/entity.hxx"

namespace zappy {

Entity & World::entityAt(std::size_t const x, std::size_t const y) {
  return this->data[y * this->x + x];
}

Entity const & World::entityAt(std::size_t const x, std::size_t const y) const {
  return this->data[y * this->x + x];
}

World randomWorld(std::size_t const teamCount, std::size_t x, std::size_t y) {
  auto result = World{
      .teams{teamCount},
      .x = x,
      .y = y,
      .data{},
  };

  auto const worldSize = x * y;

  result.data.reserve(worldSize);

  auto playerPositions = std::set<std::size_t>();

  auto distributePosition =
      std::uniform_int_distribution<std::size_t>(worldSize);
  auto distributeLevel =
      std::uniform_int_distribution<std::uint8_t>(1, PLAYER_MAX_LEVEL + 1);
  auto distributeEntity =
      std::uniform_int_distribution<std::uint8_t>(ENTITY_MAX + 1);

  for (std::size_t i = 0; i < teamCount; ++i) {
    result.teams.push_back({});

    for (size_t j = 0; j < zappy::PLAYERS_PER_TEAM; ++j) {
      size_t pos;
      do {
        pos = distributePosition(utils::rng);
      } while (playerPositions.contains(pos));

      result.teams[i][j] = std::make_unique<Player>(Player{
          .team = result.teams[i],
          .pos = pos,
          .level = distributeLevel(utils::rng),
          .inventory{},
      });
    }
  }

  for (size_t i = 0; i < worldSize; ++i) {
    result.data.push_back(static_cast<Entity>(distributeEntity(utils::rng)));
  }

  return result;
}

} // namespace zappy
//
