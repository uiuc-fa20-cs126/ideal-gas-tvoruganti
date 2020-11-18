
#include <visualizer/ideal_gas_app.h>

namespace ideal_gas {

namespace visualizer {

IdealGasApp::IdealGasApp()
    : particle_container_(vec2(kMargin, kMargin),kWindowSize - 2 * kMargin, kVariety, kColors),
      histograms_(kVariety, particle_container_.GetParticleList(), vec2(kWindowSize - kMargin/2, kMargin/10), vec2(kWindowSize + kHistoSpace - kMargin/2, kWindowSize - kMargin), kColors){
  app::setWindowSize((int)(kWindowSize + kHistoSpace), (int)(kWindowSize + kHistoSpace/3));
  speed_multiplier = 1;
}

void IdealGasApp::draw() {
  //sets background color
  Color8u background_color(0, 0, 0);
  gl::clear(background_color);

  particle_container_.Draw();
  histograms_.Draw();

  //draws text
  gl::drawStringCentered(
      "Ideal Gas Simulator",
      vec2(kWindowSize / 2, kMargin / 2), Color(255,0,0));

  gl::drawString(
      "Number of Particles: " + std::to_string(particle_container_.GetNumParticles()),
      vec2(kMargin, kWindowSize - kMargin/3), Color(0,255,0));

  gl::drawString(
      "Current Speed: " + std::to_string(speed_multiplier) + "x",
      vec2(kMargin, kWindowSize - 2*kMargin/3), Color(0,255,255));

  //draws interface to add particles
  for (size_t i = 0; i < kVariety; ++i) {
    Color stroke_color = i == highlighted_particle_ ? "yellow" : "white";

    gl::color(Color(stroke_color));
    vec2 bottom_right_corner(kWindowSize - kMargin - 55*i, kWindowSize - kMargin/2 + 22.5);
    vec2 top_left_corner = bottom_right_corner - vec2(45,45);
    Rectf margin_bounding_box(top_left_corner, bottom_right_corner);
    gl::drawStrokedRect(margin_bounding_box);

    gl::color(Color(kColors[i]));
    vec2 center = (bottom_right_corner + top_left_corner)/vec2(2,2);
    gl::drawSolidCircle(center, 18/kVariety*(i+1)+2);
  }
}

void IdealGasApp::update() {
  //runs the loop multiple times to speed up or slow down simulation
  for(size_t i = 0; i < speed_multiplier; i++){
    particle_container_.update();
  }
  //have to send the updated particles to the histogram every frame
  histograms_.update(particle_container_.GetParticleList());
}

void IdealGasApp::setup() {
  //creates a certain amount of starting particles
  for (size_t i = 0; i < kNumStartingParticles; ++i) {
    particle_container_.AddParticle(rand() % kVariety);
  }
}

void IdealGasApp::keyDown(app::KeyEvent event) {
  switch (event.getCode()) {
    case app::KeyEvent::KEY_RETURN:
      particle_container_.AddParticle(highlighted_particle_);
      break;
    case app::KeyEvent::KEY_DOWN:
      if (speed_multiplier > 0) //speed can't be negative
      speed_multiplier--;
      break;
    case app::KeyEvent::KEY_UP:
      speed_multiplier++;
      break;
  }
}

void IdealGasApp::mouseDown(app::MouseEvent event) {
  //highlights the selected particle box
  vec2 pos = event.getPos();
  for(size_t i = 0; i < kVariety; i++){
    vec2 bottom_right_corner(kWindowSize - kMargin - 55*i, kWindowSize - kMargin/2 + 22.5);
    vec2 top_left_corner = bottom_right_corner - vec2(45,45);
    if (pos.x < bottom_right_corner.x && pos.x > top_left_corner.x && pos.y < bottom_right_corner.y && pos.y > top_left_corner.y)
      highlighted_particle_ = i;
  }

}

}  // namespace visualizer

}  // namespace naivebayes
