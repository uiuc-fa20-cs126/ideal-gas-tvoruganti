#pragma once

#include "cinder/gl/gl.h"
#include <glm/vec2.hpp>
#include "core/NewParticle.h"

using glm::vec2;

namespace idealgas {

namespace visualizer {


class Sketchpad {

  struct Particle {
    Particle(){
      pos = vec2();
      vel = vec2();
    }
    Particle(const vec2& position, const vec2& velocity){
      pos = position;
      vel = velocity;
    }
    void Move(){
      pos += vel;
    }
    void CollideHorizontalWall(){
      vel = vec2(-vel.x, vel.y);
    }
    void CollideVerticalWall(){
      vel = vec2(vel.x, -vel.y);
    }
    void CollideParticle(Particle& other){
      vec2 vel_dif = vel - other.vel;
      vec2 pos_dif = pos - other.pos;

      float dot_product = glm::dot(pos_dif, vel_dif);

      float pos_magnitude = pow(glm::length(pos_dif), 2) ;

      float this_scalar = dot_product/pos_magnitude;

      vel = vel - pos_dif*this_scalar;

      other.vel = other.vel + pos_dif*this_scalar;
    }

    vec2 pos;
    vec2 vel;
  };

 public:

  Sketchpad(const glm::vec2& top_left_corner, double num_pixels_per_side, size_t rad);

  void Draw() const;
  void update();
  void AddParticle();
  size_t GetNumParticles();

 private:
  glm::vec2 margin_;
  std::vector<Particle> particle_list_;
  size_t radius;
  NewParticle temp;


  /** Number of screen pixels in the width/height of one sketchpad pixel */
  size_t container_side_length_;

};

}  // namespace visualizer

}  // namespace naivebayes
