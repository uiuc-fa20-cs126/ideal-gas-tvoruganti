//
// Created by Tarun Voruganti on 11/1/20.
//

#include "visualizer/Particle.h"

namespace idealgas {

namespace visualizer {

Particle::Particle(glm::vec2 pos, glm::vec2 vel)
    : position_(pos), velocity_(vel) {}

glm::vec2 Particle::GetPosition() const{ return position_; }

glm::vec2 Particle::GetVelocity() const{ return velocity_; }

void Particle::Move() { position_ += velocity_; }

} // namespace visualizer

} // namespace idealgas
