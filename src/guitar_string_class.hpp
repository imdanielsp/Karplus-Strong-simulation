/** Copyright 2015 Daniel Santos
 *  @file     guitar_string_class.cpp
 *  @author   Daniel Santos (dsantos)
 *  @date     03/27/2016
 *  @version  1.0
 *
 *  @brief    This file contains the
 *  interface of the namespace
 *  GuitarHero, which has the GuitarString
 * */

#ifndef PS3A_GUITAR_STRING_CLASS_H
#define PS3A_GUITAR_STRING_CLASS_H
#define SAMPLES_PER_SEC 44100
#define DECAY_FACTOR 0.996

#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "ring_buffer_class.hpp"

/**
 * @brief namespace for the whole assignment
 */
namespace GuitarHero {

/**
 *  @brief  Interface of the GuitarString class
 *  that models a guitar string.
 * */
class GuitarString {
 public:
  /**
   *  @brief  Creates a guitar string of the given frequency,
   *  using a sampling rate of 44,100.
   *
   *  @param  double
   * */
  explicit GuitarString(double frequency);
  /**
   *  @brief  Creates a guitar string whose size and initial
   *  are geiven by a vector of sf::Int16.
   *
   *  @param std::vector<sf::int16>&
   * */
  explicit GuitarString(const std::vector<sf::Int16>& init_vector);
  /**
   *  @brief  Pluck the guitar string by replacing the buffer
   *  white noise.
   * */
  void pluck();
  /**
   *  @brief Advance the simulatino one time step.
   * */
  void tic();
  /**
   *  @brief Returns the current sample in the ring buffer.
   *
   *  @return sf::Int16
   * */
  sf::Int16 sample();
  /**
   *  @brief  Returns the number of times tic was called.
   * */
  int time();

 private:
  RingBuffer::ring_buffer<sf::Int16> *ring_buffer_;  // < The ring buffer
  int tic_counter_;  // < Counter for the tic
};
}  // namespace GuitarHero

#endif  // PS3A_GUITAR_STRING_CLASS_H
