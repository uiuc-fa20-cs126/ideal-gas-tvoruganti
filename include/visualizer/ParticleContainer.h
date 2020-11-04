#pragma once

#include "cinder/gl/gl.h"
#include "core/Particle.h"
#include <glm/vec2.hpp>

using glm::vec2;

namespace idealgas {

namespace visualizer {

class ParticleContainer {

 public:

  /**
   * Creates a Particle Container
   * @param top_left_corner top left point for container
   * @param num_pixels_per_side how long each side is
   * @param rad radius for particles
   */
  ParticleContainer(const vec2& top_left_corner, std::vector<Particle> part_list, size_t num_pixels_per_side, size_t rad);

  ParticleContainer(const vec2& top_left_corner, size_t num_pixels_per_side, size_t rad);

  /**
   * Draws the Container with all its particles
   */
  void Draw() const;

  /**
   * changes positions of particles and checks for collisions
   */
  void update();

  /**
   * Adds a new particle to the simulation
   */
  void AddParticle();

  /**
   * Gets the number of particles
   * @return number of particles in the container
   */
  size_t GetNumParticles();

  /**
   * Gets the particle list, only for testing
   * @return particel list
   */
  std::vector<Particle> GetParticleList() const;

 private:
  vec2 margin_; //distance from screen corner to put container
  std::vector<Particle> particle_list_; //list of all particles on screen
  size_t radius; //radius of each particle
  size_t container_side_length_;   // Number of screen pixels in the width/height of one sketchpad pixel
};

}  // namespace visualizer

}  // namespace naivebayes
