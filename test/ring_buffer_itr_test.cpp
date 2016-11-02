/** Copyright 2015 Daniel Santos
 *  @file     ring_buffer_itr_class.hpp
 *  @author   Daniel Santos (dsantos)
 *  @date     03/11/2016
 *  @version  2.0
 *
 *  @brief    Unit test for the iterator
 * */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN Main

#include <boost/test/unit_test.hpp>
#include "ring_buffer_class_dsantos.hpp"

/**
 *  @brief  This test that if the client
 *  tries to access a null iterator, it throws a
 *  runtime_error exception.
 **/
BOOST_AUTO_TEST_CASE(NullDereference) {
  ring_buffer::RingBuffer<int, 5> ringBuffer;
  ring_buffer::RingBuffer<int, 5>::iterator itr = ringBuffer.begin();

  BOOST_REQUIRE_THROW(*itr, std::runtime_error);
}

/**
 *  @brief  This test that if the client try
 *  to increase a null iterator, it throws a
 *  runtime_error exception.
 **/
BOOST_AUTO_TEST_CASE(IncrementingNull) {
  ring_buffer::RingBuffer<int, 5> ringBuffer;
  ring_buffer::RingBuffer<int, 5>::iterator itr = ringBuffer.begin();

  BOOST_REQUIRE_THROW(++itr, std::runtime_error);
}
/**
 *  @brief  This test the increment operator.
 * */
BOOST_AUTO_TEST_CASE(IncrementOperator) {
  ring_buffer::RingBuffer<int, 5> ringBuffer;
  ringBuffer.push_back(1);
  ringBuffer.push_back(2);
  ringBuffer.push_back(3);
  ringBuffer.push_back(4);
  ringBuffer.push_back(5);

  ring_buffer::RingBufferIterator<int, 5> itr = ringBuffer.begin();

  BOOST_REQUIRE_EQUAL(*itr, ringBuffer[0]);
  BOOST_CHECK_NO_THROW(++itr);
  BOOST_REQUIRE_EQUAL(*itr, ringBuffer[1]);
  BOOST_CHECK_NO_THROW(++itr);
  BOOST_REQUIRE_EQUAL(*itr, ringBuffer[2]);
  BOOST_CHECK_NO_THROW(++itr);
  BOOST_REQUIRE_EQUAL(*itr, ringBuffer[3]);
  BOOST_CHECK_NO_THROW(++itr);
  BOOST_REQUIRE_EQUAL(*itr, ringBuffer[4]);
}

/**
 *  @brief This test that the end method return
 * the end of the container.
 * */
BOOST_AUTO_TEST_CASE(EndIterator) {
  ring_buffer::RingBuffer<int, 5> ringBuffer;
  ringBuffer.push_back(2);
  ringBuffer.push_back(5);
  ringBuffer.push_back(3);

  ring_buffer::RingBuffer<int, 5>::iterator iterator1 = ringBuffer.end();

  BOOST_REQUIRE_EQUAL(*iterator1, 3);
}

