/** Copyright 2015 Daniel Santos
 *  @file     guitar_string_class.cpp
 *  @author   Daniel Santos (dsantos)
 *  @date     03/27/2016
 *  @version  1.0
 *
 *  @brief    This file contains the
 *  namespace GuitarHero, which has
 *  the GuitarString class and more.
 * */

#include <vector>
#include "guitar_string_class.hpp"
/**
 *  @brief namespace for the GuitarHero assigment
 * */
namespace GuitarHero {

/**
 *  @brief This is the class object used in with
 *  ths std::generate function, to generate random
 *  numbers for the ring buffer.
 * */
class RandSeed {
 public:
  /**
   *  @brief Default constructor that initialize the
   *  seed to the current time.
   * */
  RandSeed() {
    seed_ = static_cast<unsigned int>(std::time(0));
  }
  /**
   *  @brief Override the operator() that is used by
   *  the std::generate to generate random numbers.
   *
   *  @return int
   * */
  double operator() () {
    return rand_r(&seed_) % (0-32768) + 65536;
  }
 private:
  unsigned int seed_;  // < Hold the seed for std::time
};

GuitarString::GuitarString(double frequency) {
  // Calculate the size of the buffer
  int n = static_cast<int>(ceil(SAMPLES_PER_SEC / frequency));
  // Initialize the tic counter to 0
  this->tic_counter_ = 0;
  // Allocate the buffer to N capacity
  this->ring_buffer_ = new RingBuffer::ring_buffer<sf::Int16>(n);
  // Initialize the buffer
  for (int i = 0; i < n; i++)
    this->ring_buffer_->push_back(0);
}

GuitarString::GuitarString(const std::vector<sf::Int16> &init_vector) {
  // Allocate the buffer to the size of the given vector
  this->ring_buffer_ = new RingBuffer::ring_buffer<sf::Int16>(
      static_cast<int>(init_vector.size()));
  // Initialize the tic counter to 0
  this->tic_counter_ = 0;
  // Assign the elements in the vector to the buffer
  for (std::size_t i = 0; i < init_vector.size(); i++) {
    this->ring_buffer_->push_back(init_vector.at(i));
  }
}

void GuitarString::pluck() {
  // Create an RandSeed object
  RandSeed randSeed;
  // Generate the ramdon numbers for the buffer
  // using the RandSeed class object defined above.
  std::generate(this->ring_buffer_->begin(),
                this->ring_buffer_->end(), randSeed);
}

void GuitarString::tic() {
  // Instaciate an iterator
  RingBuffer::ring_buffer<sf::Int16>::iterator
      itr = this->ring_buffer_->begin();
  // Initialize temp variables to calculate the new value
  double first = *itr, second;
  // Increment the iterator
  ++itr;
  second = *itr;
  // Delete the front element;
  this->ring_buffer_->pop_front();
  // Calculate the element
  double new_value = DECAY_FACTOR * ((first+second)/2);
  // Add it to the ring buffer
  this->ring_buffer_->push_back((sf::Int16)new_value);
  // Increment the tic counter
  this->tic_counter_++;
}

sf::Int16 GuitarString::sample() {
  // Returns the front of the buffer
  return this->ring_buffer_->front();
}

int GuitarString::time() {
  // Returns the counter
  return tic_counter_;
}
}  // namespace GuitarHero
