
#include <catch2/catch.hpp>
#include "visualizer/ParticleContainer.h"

using ideal_gas::Particle;

TEST_CASE("Check Particle Container Class") {

  std::vector<ideal_gas::Particle> p_list;
  p_list.emplace_back(vec2(200,200), vec2(1,1), 5, 1);
  p_list.emplace_back(vec2(400,140), vec2(-4,2), 5,2);
  p_list.emplace_back(vec2(600,330), vec2(-5,-9), 5, 3);

  p_list.emplace_back(vec2(600,100), vec2(-5,-9), 5, 3); //test top wall collision
  p_list.emplace_back(vec2(600,1100), vec2(-5,9), 5, 3); //test bottom wall collision
  p_list.emplace_back(vec2(100,300), vec2(-5,4), 5, 3); //test left wall collision
  p_list.emplace_back(vec2(1100,200), vec2(5,8), 5, 3); //test right wall collision

  ideal_gas::visualizer::ParticleContainer particle_container(vec2(100,100), p_list, 1000, 5);

  SECTION("Update"){
    SECTION("Movement"){
      particle_container.update();
      std::vector<ideal_gas::Particle> updated_p_list = particle_container.GetParticleList();

      ideal_gas::Particle part1 = updated_p_list[0];
      ideal_gas::Particle part2 = updated_p_list[1];
      ideal_gas::Particle part3 = updated_p_list[2];

      REQUIRE(part1.GetPos().x == 201);
      REQUIRE(part1.GetPos().y == 201);
      REQUIRE(part2.GetPos().x == 396);
      REQUIRE(part2.GetPos().y == 142);
      REQUIRE(part3.GetPos().x == 595);
      REQUIRE(part3.GetPos().y == 321);
    }
    SECTION("Wall Collisions"){
      particle_container.update();
      std::vector<ideal_gas::Particle> updated_p_list = particle_container.GetParticleList();

      ideal_gas::Particle part1 = updated_p_list[3];
      ideal_gas::Particle part2 = updated_p_list[4];
      ideal_gas::Particle part3 = updated_p_list[5];
      ideal_gas::Particle part4 = updated_p_list[6];

      REQUIRE(part1.GetVel().x == -5);
      REQUIRE(part1.GetVel().y == 9);
      REQUIRE(part2.GetVel().x == -5);
      REQUIRE(part2.GetVel().y == -9);
      REQUIRE(part3.GetVel().x == 5);
      REQUIRE(part3.GetVel().y == 4);
      REQUIRE(part4.GetVel().x == -5);
      REQUIRE(part4.GetVel().y == 8);
    }
  }
  SECTION("Add Particle"){
    particle_container.AddParticle(0);
    std::vector<ideal_gas::Particle> updated_p_list = particle_container.GetParticleList();
    ideal_gas::Particle part = updated_p_list[7];

    REQUIRE(particle_container.GetNumParticles() == 8);
    REQUIRE(part.GetPos().x > 105);
    REQUIRE(part.GetPos().x < 1095);
    REQUIRE(part.GetPos().y > 105);
    REQUIRE(part.GetPos().y < 1095);
  }
}

