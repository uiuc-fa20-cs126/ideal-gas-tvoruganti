#include <visualizer/ParticleContainer.h>

namespace idealgas {

namespace visualizer {

ParticleContainer::ParticleContainer(const vec2 &top_left_corner, size_t sketchpad_size, size_t rad)
    : margin_(top_left_corner), radius(rad), container_side_length_(sketchpad_size){
  particle_list_ = std::vector<Particle>();
}

void ParticleContainer::Draw() const {

  //creates container for particles
  ci::gl::color(ci::Color("white"));
  vec2 bottom_right_margin = margin_ + vec2(container_side_length_, container_side_length_);
  ci::Rectf margin_bounding_box(margin_, bottom_right_margin);
  ci::gl::drawSolidRect(margin_bounding_box);

  //draws every particle
  for (const Particle & part : particle_list_) {
    ci::gl::color(ci::Color("orange"));
    ci::gl::drawSolidCircle(part.GetPos(), part.GetRadius());
  }
}

void ParticleContainer::update() {

  //These nested for loops check for particle collisions and execute them
  for (size_t i = 0; i < particle_list_.size() - 1; ++i) {
    for (size_t j = i+1; j < particle_list_.size(); ++j) {

      vec2 pos_dif = particle_list_[i].GetPos() -  particle_list_[j].GetPos(); //difference in positions
      vec2 vel_dif = particle_list_[i].GetVel() -  particle_list_[j].GetVel(); //difference in velocities

      float dp = glm::dot(pos_dif, vel_dif); //dot product of diff. vectors
      float part_dist = glm::distance(particle_list_[i].GetPos(), particle_list_[j].GetPos()); //distance between the centers

      if (dp < 0 && part_dist <= particle_list_[i].GetRadius() + particle_list_[j].GetRadius())
        particle_list_[i].CollideParticle(particle_list_[j]);

    }
  }

  //checks for wall collisions and moves each particle
  for (auto & curr_part : particle_list_) {
      //Checks if edge of particle's x-coordinate is the same as the horizontal wall or past it
    if ((curr_part.GetPos().x - radius) <= margin_.x || (curr_part.GetPos().x + radius) >= (margin_.x + container_side_length_)){
      curr_part.CollideHorizontalWall();
      //Checks if edge of particle's y-coordinate is the same as the vertical wall or past it
    }else if ((curr_part.GetPos().y - radius) <= margin_.y || (curr_part.GetPos().y + radius) >= (margin_.y + container_side_length_)){
      curr_part.CollideVerticalWall();
    }
    curr_part.Move();
  }
}

void ParticleContainer::AddParticle() {

  size_t possible_x_pos = rand() % (container_side_length_ - 2*radius) + margin_.x + radius; //gets a random x position within the walls
  size_t possible_y_pos = rand() % (container_side_length_ - 2*radius) + margin_.y + radius; //gets a random y position within the walls

  //intial velocity can be at maximum half the radius + 1 and at minimum 1
  int possible_x_vel = rand() % (size_t)(sqrt(radius)) + 1;
  int possible_y_vel = rand() % (size_t)(sqrt(radius)) + 1;

  //randomly sets the velocities to negative or positive
  if (rand() % 2 == 0)
    possible_x_vel *= -1;
  if (rand() % 2 == 1)
    possible_y_vel *= -1;

  Particle part_to_add(vec2(possible_x_pos, possible_y_pos), vec2(possible_x_vel, possible_y_vel), radius);

  particle_list_.push_back(part_to_add);
}

size_t ParticleContainer::GetNumParticles() {
  return particle_list_.size();
}

} // namespace visualizer

} // namespace idealgas
