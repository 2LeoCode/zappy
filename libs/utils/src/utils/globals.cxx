#include <random>

namespace utils {

auto rng = std::default_random_engine{std::random_device{"/dev/urandom"}()};

}
