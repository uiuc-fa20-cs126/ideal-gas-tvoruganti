#pragma once

#include "ParticleContainer.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class IdealGasApp : public ci::app::App {

 public:

  /**
   * Creates the App
   */
  IdealGasApp();

  /**
   * Draws the App
   */
  void draw() override;

  /**
   * Checks if any keys have been pressed and executes events for certain presses
   * @param event key that is pressed
   */
  void keyDown(ci::app::KeyEvent event) override;

  /**
   * updates the app
   */
  void update() override;

  /**
   * Initial conditions
   */
  void setup() override;


  // provided that you can see the entire UI on your screen.
  const size_t kWindowSize = 800; //window size
  const size_t kMargin = 100; //margin between window and container
  const size_t kNumStartingParticles = 25; //how many particles simulation should start with

 private:
  ParticleContainer particle_container_; //container itself
  size_t speed_multiplier; //speed of the simulation
};

}  // namespace visualizer

}  // namespace naivebayes
