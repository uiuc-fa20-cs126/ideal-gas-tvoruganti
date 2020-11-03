#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "sketchpad.h"

namespace idealgas {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;
  void update() override;
  void setup() override;


  // provided that you can see the entire UI on your screen.
  const int kWindowSize = 800;
  const int kMargin = 100;

 private:
  Sketchpad sketchpad_;
  size_t speed_multiplier;
};

}  // namespace visualizer

}  // namespace naivebayes
