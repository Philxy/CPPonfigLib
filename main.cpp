#include <iostream>

namespace constants {
constexpr double pi(3.14159);
constexpr double avogadro(6.0221413e23);
constexpr double earthAcceleration(9.81);
constexpr double moonAcceleration(1.62);
} // namespace constants

namespace physics {
double calculateForce(double mass, double acceleration) {
  return mass * acceleration;
}

} // namespace physics

int main() { constants::pi; }
