#include <visualizer/sketchpad.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;

Sketchpad::Sketchpad(const vec2& top_left_corner, double sketchpad_size)
    :top_left_margin_(top_left_corner), pixel_side_length_(sketchpad_size)
  {
  vec2 yuh(200,200);
  part = yuh;
  temp = Particle(yuh,yuh);
  }

void Sketchpad::Draw() const {

  ci::gl::color(ci::Color("white"));
  vec2 bottom_right_margin = top_left_margin_ + vec2(pixel_side_length_, pixel_side_length_);
  ci::Rectf margin_bounding_box(top_left_margin_, bottom_right_margin);
  ci::gl::drawSolidRect(margin_bounding_box);

  vec2 bruh = temp.GetPosition();

  ci::gl::color(ci::Color("orange"));
  ci::gl::drawSolidCircle(bruh, 20);

}

void Sketchpad::update(){

}

}  // namespace visualizer

}  // namespace naivebayes
