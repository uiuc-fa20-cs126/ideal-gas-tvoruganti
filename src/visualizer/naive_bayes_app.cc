
#include <visualizer/naive_bayes_app.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp()
    : sketchpad_(glm::vec2(kMargin, kMargin),
                 kWindowSize - 2 * kMargin) {
  ci::app::setWindowSize((int)kWindowSize, (int)kWindowSize);
}

void IdealGasApp::draw() {
  ci::Color8u background_color(0, 0, 0);
  ci::gl::clear(background_color);

  sketchpad_.Draw();

  ci::gl::drawStringCentered(
      "Ideal Gas Simulator",
      glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("red"));

  /*
  ci::gl::drawStringCentered(
      "Prediction: " + std::to_string(current_prediction_),
      glm::vec2(kWindowSize / 2, kWindowSize - kMargin / 2), ci::Color("blue"));
      */
}
void IdealGasApp::update() { AppBase::update(); }

void IdealGasApp::mouseDown(ci::app::MouseEvent event) {
}

void IdealGasApp::mouseDrag(ci::app::MouseEvent event) {
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN:

      break;
  }
}

}  // namespace visualizer

}  // namespace naivebayes
