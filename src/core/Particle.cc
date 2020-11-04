//
// Created by Tarun Voruganti on 11/3/20.
//

#include "core/Particle.h"

namespace idealgas {

Particle::Particle() : position_(vec2()), velocity_(vec2()), radius_(0) {}

Particle::Particle(const vec2& pos, const vec2& vel, size_t rad) : position_(pos), velocity_(vel), radius_(rad) {}

void Particle::Move() { position_ += velocity_; }

void Particle::CollideHorizontalWall() {
  velocity_ = vec2(-velocity_.x, velocity_.y);
}

void Particle::CollideVerticalWall() {
  velocity_ = vec2(velocity_.x, -velocity_.y);
}

void Particle::CollideParticle(Particle &other) {
  vec2 vel_dif = velocity_ - other.velocity_; //difference in velocities
  vec2 pos_dif = position_ - other.position_; //difference in positions

  float dot_product = glm::dot(pos_dif, vel_dif); //dot product of diff. vectors

  float pos_magnitude = pow(glm::length(pos_dif), 2); //length of pos. vector squared

  float scalar = dot_product / pos_magnitude; //creates scalar

  velocity_ = velocity_ - pos_dif * scalar; //sets new velocity

  other.velocity_ = other.velocity_ + pos_dif * scalar; //sets other velocity
}

vec2 Particle::GetPos() const { return position_; }

vec2 Particle::GetVel() const { return velocity_; }

size_t Particle::GetRadius() const { return radius_; }

} // namespace idealgas