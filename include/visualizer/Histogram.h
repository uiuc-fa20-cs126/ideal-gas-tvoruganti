//
// Created by Tarun Voruganti on 11/7/20.
//

#pragma once

#include "cinder/gl/gl.h"
#include <glm/vec2.hpp>
#include "core/Particle.h"

using glm::vec2;

namespace ideal_gas{

namespace visualizer {

class Histogram {

public:
  Histogram() = default;

  /**
   * Contructor to create histograms
   * @param var number of different particles
   * @param p_list list of particles the simulation starts with
   * @param tl_corner top left corner
   * @param br_corner bottom right corner
   * @param col vector of colors to use
   */
  Histogram(size_t var, const std::vector<Particle>& p_list, const vec2& tl_corner, const vec2& br_corner, std::vector<ci::Color>  col);

  /**
   * Draws the histogram
   */
  void Draw() const;

  /**
   * Updates histogram every frame
   * @param p_list
   */
  void update(const std::vector<Particle>& p_list);

  /**
   * Sorts all the particles of a specific type by their speed within the passed bounds
   * @param lower_bound lower threshold for speed
   * @param upper_bound higher threshold for speed
   * @param part_type which vector of particles to look for in the sorted list
   * @return number of particles that are in the interval
   */
  size_t NumParticlesInRange(size_t lower_bound, size_t upper_bound, size_t part_type) const;

  /**
   * Sorts a list of particles into their different types
   * @param p_list list of particles to sort
   */
  void sort(const std::vector<Particle>& p_list);

private:
  size_t variety_; //amount of different particles
  size_t kNumRects = 10; //number of intervals on x-axis
  vec2 top_left_corner_; //top left corner of given histogram space
  vec2 bottom_right_corner_; // bottom right corner of given histogram space
  std::vector<std::vector<Particle>> sorted_particles_; // particles sorted by type
  std::vector<ci::Color> const kColors; //colors for histogram

};



}

}

