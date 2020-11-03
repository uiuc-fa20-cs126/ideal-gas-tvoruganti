//
// Created by Tarun Voruganti on 11/3/20.
//
#pragma once

#include "cinder/gl/gl.h"
#include <glm/vec2.hpp>

using glm::vec2;

namespace idealgas{

class NewParticle{

public:
  NewParticle();
  NewParticle(vec2 pos, vec2 vel);
  void Move();
  void CollideHorizontalWall();
  void CollideVerticalWall();
  void CollideParticle(NewParticle& other);
  vec2 GetPos() const;
  vec2 GetVel() const;


private:
  vec2 position_;
  vec2 velocity_;

};





}


