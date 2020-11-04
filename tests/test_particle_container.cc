
#include <catch2/catch.hpp>
#include "visualizer/ParticleContainer.h"

TEST_CASE("Check Particle Container Class") {

  std::vector<idealgas::Particle> p_list;
  p_list.emplace_back(vec2(200,200), vec2(1,1), 5);
  p_list.emplace_back(vec2(400,140), vec2(-4,2), 5);
  p_list.emplace_back(vec2(600,330), vec2(-5,-9), 5);

  idealgas::visualizer::ParticleContainer particle_container(vec2(100,100), p_list, 1000, 5);

  SECTION("Update"){
    particle_container.update();
    std::vector<idealgas::Particle> updated_p_list = particle_container.GetParticleList();

    idealgas::Particle part1 = updated_p_list[0];
    idealgas::Particle part2 = updated_p_list[1];
    idealgas::Particle part3 = updated_p_list[2];

    REQUIRE(part1.GetPos().x == 201);
    REQUIRE(part1.GetPos().y == 201);
    REQUIRE(part2.GetPos().x == 396);
    REQUIRE(part2.GetPos().y == 142);
    REQUIRE(part3.GetPos().x == 595);
    REQUIRE(part3.GetPos().y == 321);
  }
  SECTION("Add Particle"){
    particle_container.AddParticle();
    std::vector<idealgas::Particle> updated_p_list = particle_container.GetParticleList();
    idealgas::Particle part4 = updated_p_list[3];

    REQUIRE(particle_container.GetNumParticles() == 4);
    REQUIRE(part4.GetPos().x > 105);
    REQUIRE(part4.GetPos().x < 1095);
    REQUIRE(part4.GetPos().y > 105);
    REQUIRE(part4.GetPos().y < 1095);
  }
}

