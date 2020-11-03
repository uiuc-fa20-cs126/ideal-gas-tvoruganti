#include <visualizer/sketchpad.h>

namespace idealgas {

namespace visualizer {

Sketchpad::Sketchpad(const vec2 &top_left_corner, double sketchpad_size, size_t rad)
    : margin_(top_left_corner), radius(rad), container_side_length_(sketchpad_size){
  particle_list_ = std::vector<Particle>();

  temp = NewParticle(vec2(500,500), vec2(1,1));
}

void Sketchpad::Draw() const {
  ci::gl::color(ci::Color("white"));
  vec2 bottom_right_margin =
      margin_ + vec2(container_side_length_, container_side_length_);
  ci::Rectf margin_bounding_box(margin_, bottom_right_margin);
  ci::gl::drawSolidRect(margin_bounding_box);

  for (const Particle& part : particle_list_) {
    ci::gl::color(ci::Color("orange"));
    ci::gl::drawSolidCircle(part.pos, radius);
  }

  ci::gl::color(ci::Color("blue"));
  ci::gl::drawSolidCircle(temp.GetPos(), radius);

}

void Sketchpad::update() {
  for (size_t i = 0; i < particle_list_.size() - 1; ++i) {
    for (size_t j = i+1; j < particle_list_.size(); ++j) {
      vec2 pos_dif = particle_list_[i].pos -  particle_list_[j].pos;
      vec2 vel_dif = particle_list_[i].vel -  particle_list_[j].vel;
      float dp = glm::dot(pos_dif, vel_dif);
      float part_dist = glm::distance(particle_list_[i].pos, particle_list_[j].pos);

      if (dp < 0 && part_dist <= 2*radius)
        particle_list_[i].CollideParticle(particle_list_[j]);
    }
  }

  for (auto & curr_part : particle_list_) {
    if ((curr_part.pos.x - radius) <= margin_.x || (curr_part.pos.x + radius) >= (margin_.x + container_side_length_)){
      curr_part.CollideHorizontalWall();
    }else if ((curr_part.pos.y - radius) <= margin_.y || (curr_part.pos.y + radius) >= (margin_.y + container_side_length_)){
      curr_part.CollideVerticalWall();
    }
    curr_part.Move();

  }
}

void Sketchpad::AddParticle() {

  size_t possible_x_pos = rand() % (container_side_length_ - 2*radius) + margin_.x + radius;
  size_t possible_y_pos = rand() % (container_side_length_ - 2*radius) + margin_.y + radius;

  int possible_x_vel = rand() % radius/2 + 1;
  int possible_y_vel = rand() % radius/2 + 1;

  if (rand() % 2 == 0)
    possible_x_vel *= -1;

  if (rand() % 2 == 1)
    possible_y_vel *= -1;


  Particle part_to_add(vec2(possible_x_pos, possible_y_pos), vec2(possible_x_vel,possible_y_vel));

  particle_list_.push_back(part_to_add);
}
size_t Sketchpad::GetNumParticles() {
  return particle_list_.size();
}

} // namespace visualizer

} // namespace idealgas
