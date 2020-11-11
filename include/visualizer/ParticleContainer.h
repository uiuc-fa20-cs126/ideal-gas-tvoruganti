#pragma once

#include "cinder/gl/gl.h"
#include "core/Particle.h"
#include <glm/vec2.hpp>

using glm::vec2;
using namespace ci;
using std::vector;

namespace ideal_gas {

namespace visualizer {

class ParticleContainer {

 public:

  /**
   * Creates a Particle Container
   * @param top_left_corner top left point for container
   * @param num_pixels_per_side how long each side is
   * @param rad radius for particles
   */
  ParticleContainer(const vec2& top_left_corner, vector<Particle> part_list, size_t num_pixels_per_side, size_t variety);

  ParticleContainer(const vec2& top_left_corner, size_t num_pixels_per_side, size_t variety, vector<ci::Color>  col);

  /**
   * Draws the Container with all its particles
   */
  void Draw() const;

  /**
   * changes positions of particles and checks for collisions
   */
  void update();

  /**
   * Adds a particle to the simulation
   * @param pos which particle to add
   */
  void AddParticle(size_t pos);

  /**
   * Gets the number of particles
   * @return number of particles in the container
   */
  size_t GetNumParticles();

  /**
   * Gets the particle list, only for testing
   * @return particel list
   */
  vector<Particle> GetParticleList() const;

 private:
  vec2 margin_; //distance from screen corner to put container
  vector<Particle> particle_list_; // list of all particles on screen
  size_t container_side_length_;   // Number of screen pixels in the width/height of one sketchpad pixel
  vector<vec2> particle_variety_; // holds radius and mass of all different particles
  vector<ci::Color> const kColors; // different colors of particles
};

}  // namespace visualizer

}  // namespace naivebayes
