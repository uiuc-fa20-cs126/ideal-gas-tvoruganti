#pragma once

#include "Histogram.h"
#include "ParticleContainer.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace ideal_gas {

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
  void keyDown(app::KeyEvent event) override;

  /**
   * Detects a mouse press and executes events if in the right place
   * @param event
   */
  void mouseDown(app::MouseEvent event) override;

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
  const size_t kNumStartingParticles = 20; //how many particles simulation should start with
  const size_t kVariety = 6;// number of different types of particles
  const size_t kHistoSpace = 400;// horizontal space for histogram
  vector<ci::Color> const kColors = {"orange", "blue", "red", "teal", "magenta", "purple", "cyan", "green", "gray"}; //different colors of particles
  size_t highlighted_particle_ = 0; //the current selected particle to highlight and add

private:
  ParticleContainer particle_container_; //container itself
  size_t speed_multiplier; //speed of the simulation
  Histogram histograms_; //histograms for each different set of particles
};

}  // namespace visualizer

}  // namespace naivebayes
