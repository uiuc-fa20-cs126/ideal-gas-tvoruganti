//
// Created by Tarun Voruganti on 11/1/20.
//

#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

#include <glm/vec2.hpp>
namespace idealgas{

namespace visualizer{

class Particle{


public:
  Particle() = default;
  Particle(glm::vec2 pos, glm::vec2 vel);
  glm::vec2 GetPosition() const;
  glm::vec2 GetVelocity() const;
  void Move();

private:
  glm::vec2 position_;
  glm::vec2 velocity_;


};



}


}

#endif // IDEAL_GAS_PARTICLE_H
