//
// Created by Tarun Voruganti on 11/3/20.
//
#pragma once

#include "cinder/gl/gl.h"
#include <glm/vec2.hpp>

using glm::vec2;

namespace idealgas{

class Particle {

public:
  /**
   * Default Constructor
   */
  Particle();

  /**
   * Basic Constructor that creates a Particle
   * @param pos position vector
   * @param vel velocity vector
   * @param rad radius
   */
  Particle(const vec2& pos, const vec2& vel, size_t rad);

  /**
   * Moves the particle by adding velocity to position
   */
  void Move();

  /**
   * Negates velocity in the x-direction
   */
  void CollideHorizontalWall();

  /**
   * Negates velocity in the y-direction
   */
  void CollideVerticalWall();

  /**
   * Changes velocity of 2 particles that collide
   */
  void CollideParticle(Particle & other);

  /**
   * Gets the position
   * @return current position vector
   */
  vec2 GetPos() const;

  /**
   * Gets velocity
   * @return current velocity vector
   */
  vec2 GetVel() const;

  /**
   * Gets radius
   * @return radius of the particle
   */
  size_t GetRadius() const;

private:
  vec2 position_; //holds the position
  vec2 velocity_; //holds the velocity
  size_t radius_; //holds the radius of the particle
};
}


