/** Copyright 2015 Daniel Santos
 *  @file     guitar_hero.cpp
 *  @author   Daniel Santos (dsantos)
 *  @date     03/27/2016
 *  @version  1.0
 *
 *  @brief    This is the guitar hero
 *  implementation from the Priceton
 *  University's project in C++. In here
 *  I used the guitar string object
 *  implemented to simulate the sound of
 *  a string.
 * */

#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <cmath>
#include "guitar_string_class.hpp"

#define SAMPLES_PER_SEC 44100
#define CONCERT_A 440

/**
 *  @brief  Construct a std::map with the Enum
 *  from SFML Keys to an ordered form.
 * */
std::map<int, unsigned int> constructKeysMap();
/**
 *  @brief  Return the index of the piano given
 *  a keyboard key
 *
 *  @param  sf::Keyboard::Key
 *
 *  @return unsigned int
 * */
unsigned int indexOfKey(sf::Keyboard::Key);
/**
 *  @brief  Calculate the frequency of a note
 *  given its index.
 *
 *  @param  int
 *
 *  @return double
 * */
double calc_freq(int ith);
/**
 *  @brief  Constructs the samples needed for
 *  37 notes.
 *
 *  @param  std::vector<std::vector<sf::Int16> >&
 * */

void construct_samples(std::vector<std::vector<sf::Int16> >& vector);
/**
 *  @brief  Constructs one sample at a time. This is a helper function
 *  of construct_samples. This use the method from the guitar string
 *  class to create a sample.
 *
 *  @param  GuitarHero::GuitarString
 *
 *  @retun  std::vector<sf::Int16>
 * */
std::vector<sf::Int16> construct_a_sample(GuitarHero::GuitarString &string);
/**
 *  @brief  Construct the vector of sound buffers.
 *
 *  @param  std::vector<std::vector<sf::Int16> >&,
 *  std::vector<sf::SoundBuffer>&
 * */
void construct_sound_buffer(std::vector<std::vector<sf::Int16> >& samples,
                            std::vector<sf::SoundBuffer>& buffers);
/**
 *  @brief  Construct a vector of sounds.
 *  @param  std::vector<sf::SoundBuffer>&, std::vector<sf::Sound>&
 * */
void construct_sounds(std::vector<sf::SoundBuffer>& sound_buffer,
                      std::vector<sf::Sound>& sounds);

int main() {
  // Define a vector of sf::Int16 Vectors
  std::vector<std::vector<sf::Int16> > samples;
  construct_samples(samples);

  // Define a vector of sound buffers
  std::vector<sf::SoundBuffer> sound_buffers;
  construct_sound_buffer(samples, sound_buffers);

  // Define define a vector of sounds
  std::vector<sf::Sound> sounds;
  construct_sounds(sound_buffers, sounds);

  // Define the Window
  sf::Window window(sf::VideoMode(800, 600), "Instrument");

  // Define the indexFromKeyBoard that will hold the
  // value of the key from the keyboard.
  std::size_t indexFromKeyboard;

  // Windows loop
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed) {
        // Try to catch a out_of_range exeception
        // Incase that a invalid key is pressed.
        try {
          // Get the index of the key from the std::map
          indexFromKeyboard = indexOfKey(event.key.code);
          // Play the sound at a given key
          sounds.at(indexFromKeyboard).play();
        } catch (std::out_of_range) {
          std::cout << "Invalid key, nothing happen" << std::endl;
        }
      }
    }
  }
  return 0;
}
void construct_sounds(std::vector<sf::SoundBuffer> &sound_buffer,
                       std::vector<sf::Sound> &sounds) {
  // Go through all of the sound buffers an create a
  // sound out of it and push it to the vector
  for (std::size_t j = 0; j < sound_buffer.size(); j++) {
    sf::Sound sound;
    sound.setBuffer(sound_buffer.at(j));
    sounds.push_back(sound);
  }
}
void construct_sound_buffer(std::vector<std::vector<sf::Int16> > &samples,
                            std::vector<sf::SoundBuffer> &buffers) {
  // Go through all the samples and create a sound buffer
  // and push it to the vector
  for (std::size_t j = 0; j < samples.size(); j++) {
    sf::SoundBuffer soundBuffer;
    if (!soundBuffer.loadFromSamples(&(samples.at(j))[0], samples.at(0).size(),
                                     2, SAMPLES_PER_SEC))
      throw std::runtime_error("sf::SoundBuffer: could be loaded");
    buffers.push_back(soundBuffer);
  }
}
void construct_samples(std::vector<std::vector<sf::Int16> > &vector) {
  // Create 37 GuitarString at a different frequency calculated
  // by the calc_freq(0 function. The string is given to the
  // construct_a_sample() function and push back the sample that it
  // returns.
  for (int i = 0; i < 37; i++) {
    double freq = calc_freq(i);
    GuitarHero::GuitarString string(freq);
    vector.push_back(construct_a_sample(string));
  }
}
double calc_freq(int ith) {
  // Formula given by the Princeton website to calculate
  // the frequency of the ith note.
  return CONCERT_A * pow(2, (ith-24.0)/12.0);
}
std::vector<sf::Int16> construct_a_sample(GuitarHero::GuitarString &string) {
  // Algorithm to construct the sample from the guitar
  std::vector<sf::Int16> samples;
  string.pluck();
  // Define the duration of the sample
  int duration = 5;
  // Do (SAMPLES_PER_SEC * duration) calls to tic to
  // generate the samples and push then to the vector
  for (int i = 0 ; i < SAMPLES_PER_SEC * duration ; i++) {
    string.tic();
    samples.push_back(string.sample());
  }
  return samples;
}
unsigned int indexOfKey(sf::Keyboard::Key key) {
  // Returns the key from the map
  return constructKeysMap().find(key)->second;
}
std::map<int, unsigned int> constructKeysMap() {
  // Define the map
  std::map<int, unsigned int> keysMap;

  // Fill the map
  keysMap.insert(std::pair<int, unsigned int>(16, 0));
  keysMap.insert(std::pair<int, unsigned int>(28, 1));
  keysMap.insert(std::pair<int, unsigned int>(22, 2));
  keysMap.insert(std::pair<int, unsigned int>(4,  3));
  keysMap.insert(std::pair<int, unsigned int>(30, 4));
  keysMap.insert(std::pair<int, unsigned int>(17, 5));
  keysMap.insert(std::pair<int, unsigned int>(31, 6));
  keysMap.insert(std::pair<int, unsigned int>(19, 7));
  keysMap.insert(std::pair<int, unsigned int>(24, 8));
  keysMap.insert(std::pair<int, unsigned int>(33, 9));
  keysMap.insert(std::pair<int, unsigned int>(20, 10));
  keysMap.insert(std::pair<int, unsigned int>(34, 11));
  keysMap.insert(std::pair<int, unsigned int>(8,  12));
  keysMap.insert(std::pair<int, unsigned int>(35, 13));
  keysMap.insert(std::pair<int, unsigned int>(14, 14));
  keysMap.insert(std::pair<int, unsigned int>(15, 15));
  keysMap.insert(std::pair<int, unsigned int>(68, 16));
  keysMap.insert(std::pair<int, unsigned int>(46, 17));
  keysMap.insert(std::pair<int, unsigned int>(55, 18));
  keysMap.insert(std::pair<int, unsigned int>(25, 19));
  keysMap.insert(std::pair<int, unsigned int>(23, 20));
  keysMap.insert(std::pair<int, unsigned int>(3,  21));
  keysMap.insert(std::pair<int, unsigned int>(2,  22));
  keysMap.insert(std::pair<int, unsigned int>(5,  23));
  keysMap.insert(std::pair<int, unsigned int>(21, 24));
  keysMap.insert(std::pair<int, unsigned int>(6,  25));
  keysMap.insert(std::pair<int, unsigned int>(1,  26));
  keysMap.insert(std::pair<int, unsigned int>(13, 27));
  keysMap.insert(std::pair<int, unsigned int>(9,  28));
  keysMap.insert(std::pair<int, unsigned int>(12, 29));
  keysMap.insert(std::pair<int, unsigned int>(10, 30));
  keysMap.insert(std::pair<int, unsigned int>(49, 31));
  keysMap.insert(std::pair<int, unsigned int>(50, 32));
  keysMap.insert(std::pair<int, unsigned int>(48, 33));
  keysMap.insert(std::pair<int, unsigned int>(52, 34));
  keysMap.insert(std::pair<int, unsigned int>(51, 35));
  keysMap.insert(std::pair<int, unsigned int>(57, 36));

  return keysMap;
}
