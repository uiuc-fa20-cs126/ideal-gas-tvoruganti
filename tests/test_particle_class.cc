
#include <catch2/catch.hpp>
#include "core/Particle.h"

TEST_CASE("Check Particle Class") {
  ideal_gas::Particle part1(vec2(200,300),vec2(1,-2), 5, 1);
  ideal_gas::Particle part2(vec2(203,302),vec2(-2,-5), 5, 2);

  SECTION("Move"){
    part1.Move();
    REQUIRE(part1.GetPos().x == 201);
    REQUIRE(part1.GetPos().y == 298);
  }

  SECTION("Collide Horizontal"){
    part1.CollideHorizontalWall();
    REQUIRE(part1.GetVel().x == -1);
    REQUIRE(part1.GetVel().y == -2);
  }
  SECTION("Collide Vertical"){
    part1.CollideVerticalWall();
    REQUIRE(part1.GetVel().x == 1);
    REQUIRE(part1.GetVel().y == 2);
  }
  SECTION("Collide Particle"){
    part2.CollideParticle(part1);

    Approx targetp1x = Approx(-3.62).epsilon(0.01);
    Approx targetp1y = Approx(-5.08).epsilon(0.01);
    Approx targetp2x = Approx(.308).epsilon(0.01);
    Approx targetp2y = Approx(-3.46).epsilon(0.01);

    REQUIRE(part1.GetVel().x == targetp1x);
    REQUIRE(part1.GetVel().y == targetp1y);
    REQUIRE(part2.GetVel().x == targetp2x);
    REQUIRE(part2.GetVel().y == targetp2y);
  }
}

