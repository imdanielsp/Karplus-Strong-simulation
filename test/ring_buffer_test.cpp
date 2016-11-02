/** Copyright 2015 Daniel Santos
 *  @file     ring_buffer_test.cpp
 *  @author   Daniel Santos (dsantos)
 *  @date     3/2/2016
 *  @version  1.0
 *
 *  @brief    This is a unit test implementation
 *  for the RingBuffer class. Here we test all of
 *  the public methods.
 * */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN Main

#include <boost/test/unit_test.hpp>
#include "ring_buffer_class_dsantos.hpp"

/*
 * Check that the template and the constructor
 * work correctly.
 * */
BOOST_AUTO_TEST_CASE(RBConstructorTest) {
  typedef ring_buffer::RingBuffer<int, 5> RBFive;
  BOOST_REQUIRE_NO_THROW(RBFive rb);

  RBFive foo;
  BOOST_REQUIRE_EQUAL(foo.size(), 0);

  typedef ring_buffer::RingBuffer<int, 0> RingBufferZero;
  BOOST_REQUIRE_THROW(RingBufferZero rb, std::invalid_argument);
}

/*
 * Check that the pusch_back funtion works how is suppose to.
 * We push some values and then check if the front is correct.
 * Then we try to pass the limit of the buffer, to make sure it
 * throws a runtime_error exception.
 * */
BOOST_AUTO_TEST_CASE(PushBackTest) {
  ring_buffer::RingBuffer<int, 3> IntRB;

  BOOST_REQUIRE_NO_THROW(IntRB.push_back(1));
  BOOST_REQUIRE_NO_THROW(IntRB.push_back(2));
  BOOST_REQUIRE_NO_THROW(IntRB.push_back(3));

  BOOST_REQUIRE_EQUAL(IntRB.front(), 1);

  BOOST_REQUIRE_THROW(IntRB.push_back(4), std::runtime_error);
}

/*
 * Check that when the pop_front function is called,
 * an item is removed from the buffer. And also that
 * if the buffer is empty, it must throws a runtime_error.
 * */
BOOST_AUTO_TEST_CASE(PopFrontTest) {
  ring_buffer::RingBuffer<double, 2> DoubleRB;

  DoubleRB.push_back(0.2);
  DoubleRB.push_back(0.4);

  BOOST_REQUIRE_NO_THROW(DoubleRB.pop_front());

  BOOST_REQUIRE_EQUAL(DoubleRB.front(), 0.4);

  BOOST_REQUIRE_NO_THROW(DoubleRB.pop_front());

  BOOST_REQUIRE_THROW(DoubleRB.pop_front(), std::runtime_error);
}

/*
 * Check that the first object pushed, is in
 * front after no matter how many objects were
 * pushed after.
 * */
BOOST_AUTO_TEST_CASE(FrontTest) {
  ring_buffer::RingBuffer<double, 5> DoubleRB;

  DoubleRB.push_back(5.34123);
  DoubleRB.push_back(4.34123);
  DoubleRB.push_back(3.34123);

  BOOST_REQUIRE_EQUAL(DoubleRB.front(), 5.34123);
}

/*
 * Check that when push_back, the size, increases,
 * and if pop_front, the size decreases.
 * */
BOOST_AUTO_TEST_CASE(SizeIncrement) {
  ring_buffer::RingBuffer<int, 3> sizeTest;

  BOOST_CHECK_EQUAL(sizeTest.size(), 0);

  sizeTest.push_back(1);

  BOOST_REQUIRE_EQUAL(sizeTest.size(), 1);

  sizeTest.pop_front();

  BOOST_CHECK_EQUAL(sizeTest.size(), 0);
}

/*
 * Check that the RingBuffer is empty when created,
 * and not empty after pushed. And last, check if
 * the stage goes back to empty after pop the last
 * element.
 * */
BOOST_AUTO_TEST_CASE(EmptyTest) {
  ring_buffer::RingBuffer<int, 3> foo;

  BOOST_REQUIRE_EQUAL(foo.empty(), true);

  foo.push_back(4);
  foo.push_back(5);

  BOOST_REQUIRE_EQUAL(foo.empty(), false);

  foo.pop_front();
  foo.pop_front();

  BOOST_CHECK_EQUAL(foo.empty(), true);
}

/*
 * Check that the [] operator works corectly.
 * For example, that if the client tries to access
 * to an out of range index, an exception is thrown.
 * And that you access to an expect element given the
 * index. Also check that a negative index is invalid.
 * */
BOOST_AUTO_TEST_CASE(IndexOperator) {
  ring_buffer::RingBuffer<int, 3> p;

  p.push_back(5);
  p.push_back(2);
  p.push_back(59);

  BOOST_REQUIRE_EQUAL(p[0], 5);
  BOOST_REQUIRE_EQUAL(p[1], 2);
  BOOST_REQUIRE_EQUAL(p[2], 59);

  BOOST_REQUIRE_THROW(p[3], std::runtime_error);  // Out range
  BOOST_REQUIRE_THROW(p[-1], std::runtime_error);  // Negative index
}
