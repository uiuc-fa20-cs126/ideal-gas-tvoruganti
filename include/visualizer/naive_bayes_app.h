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

  // provided that you can see the entire UI on your screen.
  const double kWindowSize = 1000;
  const double kMargin = 100;

 private:
  Sketchpad sketchpad_;
};

}  // namespace visualizer

}  // namespace naivebayes
