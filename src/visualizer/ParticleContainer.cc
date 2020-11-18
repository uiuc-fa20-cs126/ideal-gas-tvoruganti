#include <visualizer/ParticleContainer.h>

#include <utility>

namespace ideal_gas {

namespace visualizer {

ParticleContainer::ParticleContainer(const vec2 &top_left_corner, size_t sketchpad_size, size_t variety, vector<Color>  col)
    : margin_(top_left_corner), container_side_length_(sketchpad_size), kColors(move(col)){
  particle_list_ = vector<Particle>();
  particle_variety_ = vector<vec2>(variety);
  size_t inc_mass = sqrt(container_side_length_)/variety;
  size_t inc_rad = 18/variety;
  for (size_t i = 0; i < variety; ++i) {
    particle_variety_[i] = vec2(inc_mass*(i+1), inc_rad*(i+1)+2);
  }
}

ParticleContainer::ParticleContainer(const vec2 &top_left_corner,
                                    vector<Particle> part_list,
                                    size_t num_pixels_per_side, size_t variety)
    : margin_(top_left_corner), particle_list_(move(part_list)), container_side_length_(num_pixels_per_side){
  particle_variety_ = vector<vec2>(variety);
  size_t inc_mass = sqrt(container_side_length_)/variety;
  size_t inc_rad = 18/variety;
  for (size_t i = 0; i < variety; ++i) {
    particle_variety_[i] = vec2(inc_mass*(i+1), inc_rad*(i+1)+2);
  }
}

void ParticleContainer::Draw() const {
  //creates container for particles
  gl::color(Color("white"));
  vec2 bottom_right_margin = margin_ + vec2(container_side_length_, container_side_length_);
  Rectf margin_bounding_box(margin_, bottom_right_margin);
  gl::drawSolidRect(margin_bounding_box);

  //draws every particle
  for (const Particle & part : particle_list_) {
    size_t count = 0;
    for (const auto & des_vec : particle_variety_) {
      if (part.GetMass() == des_vec.x && part.GetRadius() == des_vec.y){
        gl::color(Color(kColors.at(count)));
        gl::drawSolidCircle(part.GetPos(), part.GetRadius());
        break;
      }
      count++;
    }
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
      //Checks if edge of particle's x-coordinate is the same as a horizontal wall or past it
    if ((curr_part.GetPos().x - curr_part.GetRadius()) <= margin_.x || (curr_part.GetPos().x + curr_part.GetRadius()) >= (margin_.x + container_side_length_)){
      curr_part.CollideHorizontalWall();
      //Checks if edge of particle's y-coordinate is the same as a vertical wall or past it
    }else if ((curr_part.GetPos().y - curr_part.GetRadius()) <= margin_.y || (curr_part.GetPos().y + curr_part.GetRadius()) >= (margin_.y + container_side_length_)){
      curr_part.CollideVerticalWall();
    }
    curr_part.Move();
  }
}

void ParticleContainer::AddParticle(size_t pos) {

  size_t mass = particle_variety_[pos].x;
  size_t radius = particle_variety_[pos].y;

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

  Particle part_to_add(vec2(possible_x_pos, possible_y_pos), vec2(possible_x_vel, possible_y_vel), radius, mass);

  particle_list_.push_back(part_to_add);
}

size_t ParticleContainer::GetNumParticles() {
  return particle_list_.size();
}

vector<Particle> ParticleContainer::GetParticleList() const {
  return particle_list_;
}

} // namespace visualizer

} // namespace idealgas
