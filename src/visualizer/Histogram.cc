//
// Created by Tarun Voruganti on 11/7/20.
//

#include "visualizer/Histogram.h"

#include <utility>

namespace ideal_gas{

namespace visualizer {

Histogram::Histogram(size_t var, const std::vector<Particle>& p_list, const vec2& xmar, const vec2& ymar, std::vector<ci::Color> col)
    : variety_(var), top_left_corner_(xmar), bottom_right_corner_(ymar), kColors(std::move(col)){
  sorted_particles_ = std::vector<std::vector<Particle>>(variety_);
  sort(p_list); //sorts the incoming particle list
}

void Histogram::Draw() const {
  vec2 space_per_hist = (bottom_right_corner_ - top_left_corner_)/vec2(1, variety_); //amount of space each histogram takes up
  //creates each histogram
  for (size_t j = 0; j < variety_; ++j) {
    vec2 hist_top_left = top_left_corner_ + vec2(0, j*(space_per_hist.y + 200/variety_)); //top left corner for each histogram

    vec2 origin = hist_top_left + vec2(0, space_per_hist.y); //the (0,0) point for each histogram

    //draws axes labels and 0
    ci::gl::drawStringCentered(
        "Speed (pixels/frame)", hist_top_left + vec2(space_per_hist.x/2, space_per_hist.y + 100/variety_), ci::Color("white"));

    ci::gl::drawStringCentered(
        "NOP", hist_top_left + vec2(-30, space_per_hist.y/2), ci::Color("white"));

    ci::gl::drawStringRight(
        "0", origin + vec2(-2, 10), ci::Color("white"));

    size_t rect_width = glm::distance(origin, hist_top_left + space_per_hist)/kNumRects; //horizontal width of each bar
    float_t vert_label_inc = (float_t)sorted_particles_[j].size()/kNumRects; //increment between each vertical label
    float_t label_width_inc = glm::distance(origin, hist_top_left)/kNumRects; //space between each vertical label
    float_t length_per_particle = glm::distance(origin, hist_top_left)/sorted_particles_[j].size(); //height of bar for 1 particle

    //draws each bar in the histogram
    for (size_t i = 0; i < kNumRects; ++i) {
      ci::gl::color(kColors[j]); //sets the color of each bar
      vec2 bottom_left = origin + vec2(i*rect_width, -1); //bottom left coordinate of the bar
      vec2 top_right = origin + vec2((i+1)*rect_width, -length_per_particle * NumParticlesInRange(i, (i+1), j)); //top right coordinate of the bar
      ci::Rectf margin_bounding_box(bottom_left, top_right); //box for bar
      ci::gl::drawStrokedRect(margin_bounding_box);

      //draws the horizontal and vertical labels
      ci::gl::drawStringCentered(
          std::to_string((i+1)), origin + vec2((i+1)*rect_width, 10), ci::Color("white"));

      ci::gl::drawStringRight(
          std::to_string((size_t)(vert_label_inc*(i+1))), hist_top_left + vec2(-2, space_per_hist.y - label_width_inc*(i+1)), ci::Color("white"));
    }

    //draws axis lines
    ci::gl::color(ci::Color("white"));
    ci::gl::drawLine(hist_top_left, origin);
    ci::gl::drawLine(origin, hist_top_left + space_per_hist);
  }
}

void Histogram::update(const std::vector<Particle>& p_list) {
  sorted_particles_.clear(); //clears current list of particles
  sorted_particles_ = std::vector<std::vector<Particle>>(variety_);
  sort(p_list); //updates list with new velocities
}

size_t Histogram::NumParticlesInRange(size_t lower_bound, size_t upper_bound, size_t part_type) const{
  if (upper_bound < lower_bound) //throws error if bounds are reversed
    throw std::runtime_error("lower bound greater than upper bound");

  size_t count = 0; //keeps track of number of particles between bounds
  //loops through each particle and checks their speed
  for (auto & part : sorted_particles_[part_type]){
    float_t speed = glm::length(part.GetVel());
    if (speed > lower_bound && speed < upper_bound)
      count++;
  }
  return count;
}

void Histogram::sort(const std::vector<Particle>& p_list) {
  //sorts the list of particles using their radius
  for (size_t i = 0; i < variety_; i++){
    for (auto & part : p_list){
      if (part.GetRadius() == 18/variety_*(i+1)+2)
        sorted_particles_[i].push_back(part);
    }
  }
}


}

}