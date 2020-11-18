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

    //draws axis lines
    ci::gl::color(ci::Color("white"));
    ci::gl::drawLine(hist_top_left, origin);
    ci::gl::drawLine(origin, hist_top_left + space_per_hist);

    //draws axes labels and 0
    ci::gl::drawStringCentered(
        "Speed (pixels/update)", hist_top_left + vec2(space_per_hist.x/2, space_per_hist.y + 150/variety_), ci::Color("white"));
    ci::gl::drawStringRight(
        "0", origin + vec2(-2, 10), ci::Color("white"));

    //Draws the vertical label and rotates it 90 degrees so it's sideways
    ci::gl::translate(hist_top_left + vec2(-30, space_per_hist.y/2));
    ci::gl::rotate(-M_PI/2);
    ci::gl::drawStringCentered(
        "Number of Particles", vec2(0,0) , ci::Color("white"));
    ci::gl::rotate(M_PI/2);
    ci::gl::translate(-hist_top_left - vec2(-30, space_per_hist.y/2));

    //The number of labels is the minimum of the amount of particles or distance/20, I found these numbers make the display aesthetically pleasing
    //can't divide by 0 so I check for if the list of particles is empty
    size_t num_vert_labels = sorted_particles_[j].empty() ? 1:std::min(sorted_particles_[j].size(), (size_t)(glm::distance(origin, hist_top_left)/25));

    //number of intervals on x-axis, if list is empty set num_rects to 1 to avoid divide by 0 error
    size_t num_rects = 10;
    float horiz_inc = GetMaxSpeed(j)/num_rects + .1f;

    size_t rect_width = glm::distance(origin, hist_top_left + space_per_hist)/num_rects; //horizontal width of each bar
    float_t vert_label_inc = (float_t)sorted_particles_[j].size()/num_vert_labels; //increment between each vertical label
    float_t label_width_inc = glm::distance(origin, hist_top_left)/num_vert_labels; //space between each vertical label
    float_t length_per_particle = glm::distance(origin, hist_top_left)/sorted_particles_[j].size(); //height of bar for 1 particle

    //draws vertical labels
    for (size_t i = 0; i < num_vert_labels; ++i) {
      ci::gl::drawStringRight(
          std::to_string(lround(vert_label_inc*(i+1.0f))), hist_top_left + vec2(-2, space_per_hist.y - label_width_inc*(i+1.0f)), ci::Color("white"));
    }

    //draws each bar in the histogram
    for (size_t i = 0; i < num_rects; ++i) {
      size_t num_parts_in_range = NumParticlesInRange(horiz_inc*i, horiz_inc*(i+1.0f), j);

      //only draws the rectangle if there are particles within this speed distribution
      if (num_parts_in_range != 0){
        ci::gl::color(kColors[j]); //sets the color of each bar
        vec2 bottom_left = origin + vec2(i*rect_width, -1); //bottom left coordinate of the bar
        vec2 top_right = origin + vec2((i+1)*rect_width, -length_per_particle * num_parts_in_range); //top right coordinate of the bar
        ci::Rectf margin_bounding_box(bottom_left, top_right); //box for bar
        ci::gl::drawSolidRect(margin_bounding_box);
        ci::gl::drawStringCentered(
            std::to_string(num_parts_in_range), vec2((bottom_left.x + top_right.x)/2,top_right.y - 10), ci::Color("white"));
      }

      //draws the horizontal labels
      std::string horiz_label = std::to_string(horiz_inc*(i+1));
      horiz_label = horiz_label.substr(0, horiz_label.find('.') + 3);
      ci::gl::drawStringCentered(
          horiz_label, origin + vec2((i+1)*rect_width, 10), ci::Color("white"));
    }
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

float_t Histogram::GetMaxSpeed(size_t position) const{
  float_t max_speed = -1; //keeps track of maximum speed

  //loops through list and finds particle with max speed
  for(auto & part : sorted_particles_[position]) {
    float_t part_speed = glm::length(part.GetVel());
    if (part_speed > max_speed)
      max_speed = part_speed;
  }
  return max_speed;
}

}

}