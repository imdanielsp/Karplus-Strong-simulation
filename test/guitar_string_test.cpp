/*
  Copyright 2015 Fred Martin, fredm@cs.uml.edu
  Wed Apr  1 09:43:12 2015
  test file for GuitarString class

  compile with
  g++ -c GStest.cpp -lboost_unit_test_framework
  g++ GStest.o GuitarString.o RingBuffer.o -o GStest -lboost_unit_test_framework
*/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <vector>
#include <exception>
#include <stdexcept>

#include "guitar_string_class.hpp"

BOOST_AUTO_TEST_CASE(GS) {
  std::vector<sf::Int16> v;

  v.push_back(0);
  v.push_back(2000);
  v.push_back(4000);
  v.push_back(-10000);

  BOOST_REQUIRE_NO_THROW(GuitarHero::GuitarString gs1(v));

  GuitarHero::GuitarString gs(v);

  // GS is 0 2000 4000 -10000
  BOOST_REQUIRE(gs.sample() == 0);

  gs.tic();
  // it's now 2000 4000 -10000 996
  BOOST_REQUIRE(gs.sample() == 2000);

  gs.tic();
  // it's now 4000 -10000 996 2988
  BOOST_REQUIRE(gs.sample() == 4000);

  gs.tic();
  // it's now -10000 996 2988 -2988
  BOOST_REQUIRE(gs.sample() == -10000);

  gs.tic();
  // it's now 996 2988 -2988 -4483
  BOOST_REQUIRE(gs.sample() == 996);

  gs.tic();
  // it's now 2988 -2988 -4483 1984
  BOOST_REQUIRE(gs.sample() == 2988);

  gs.tic();
  // it's now -2988 -4483 1984 0
  BOOST_REQUIRE(gs.sample() == -2988);

  // a few more times
  gs.tic();
  BOOST_REQUIRE(gs.sample() == -4483);
  gs.tic();
  BOOST_REQUIRE(gs.sample() == 1984);
  gs.tic();
  BOOST_REQUIRE(gs.sample() == 0);
}