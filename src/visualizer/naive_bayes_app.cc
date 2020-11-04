
#include <visualizer/naive_bayes_app.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp()
    : particle_container_(glm::vec2(kMargin, kMargin),kWindowSize - 2 * kMargin, 5) {
  ci::app::setWindowSize((int)kWindowSize, (int)kWindowSize);
  speed_multiplier = 1;
}

void IdealGasApp::draw() {
  //sets background color
  ci::Color8u background_color(0, 0, 0);
  ci::gl::clear(background_color);

  particle_container_.Draw();

  //draws text
  ci::gl::drawStringCentered(
      "Ideal Gas Simulator",
      glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color(255,0,0));

  ci::gl::drawStringCentered(
      "Number of Particles: " + std::to_string(particle_container_.GetNumParticles()),
      glm::vec2(kWindowSize/2, kWindowSize - 4*kMargin/5), ci::Color(0,255,0));

  ci::gl::drawStringCentered(
      "Current Speed: " + std::to_string(speed_multiplier) + "x",
      glm::vec2(kWindowSize / 2, kWindowSize - 3*kMargin/5), ci::Color(0,255,255));
}

void IdealGasApp::update() {
  //runs the loop multiple times to speed up or slow down simulation
  for(size_t i = 0; i < speed_multiplier; i++){
    particle_container_.update();
  }
}

void IdealGasApp::setup() {
  //creates a certain amount of starting particles
  for (size_t i = 0; i < kNumStartingParticles; ++i) {
    particle_container_.AddParticle();
  }
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN:
      particle_container_.AddParticle();
      break;
    case ci::app::KeyEvent::KEY_DOWN:
      if (speed_multiplier > 0) //speed can't be negative
      speed_multiplier--;
      break;
    case ci::app::KeyEvent::KEY_UP:
      speed_multiplier++;
      break;
  }
}

}  // namespace visualizer

}  // namespace naivebayes
