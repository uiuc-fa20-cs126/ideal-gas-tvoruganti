//
// Created by Tarun Voruganti on 11/3/20.
//

#include "core/NewParticle.h"

namespace idealgas {

NewParticle::NewParticle() : position_(vec2()), velocity_(vec2()) {}

NewParticle::NewParticle(vec2 pos, vec2 vel) : position_(pos), velocity_(vel) {}

void NewParticle::Move() { position_ += velocity_; }

void NewParticle::CollideHorizontalWall() {
  velocity_ = vec2(-velocity_.x, velocity_.y);
}

void NewParticle::CollideVerticalWall() {
  velocity_ = vec2(velocity_.x, -velocity_.y);
}

void NewParticle::CollideParticle(NewParticle &other) {
  vec2 vel_dif = velocity_ - other.velocity_;
  vec2 pos_dif = position_ - other.position_;

  float dot_product = glm::dot(pos_dif, vel_dif);

  float pos_magnitude = pow(glm::length(pos_dif), 2);

  float this_scalar = dot_product / pos_magnitude;

  velocity_ = velocity_ - pos_dif * this_scalar;

  other.velocity_ = other.velocity_ + pos_dif * this_scalar;
}

vec2 NewParticle::GetPos() const { return position_; }

vec2 NewParticle::GetVel() const { return velocity_; }
} // namespace idealgas