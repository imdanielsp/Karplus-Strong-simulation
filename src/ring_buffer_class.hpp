/**
 * @file ring_buffer_class.hpp
 * @copyright Ayat Hatem 2016
 * @author Ayat Hatem
 * @date 3/18/2016
 * @version 1.0
 *
 * @brief a ring buffer class declaration and
 * its iterator
 * 
 * This is a class that implement a ring buffer
 * a ring buffer acts like a queue: you read 
 * the front and add to the back of the queue
 * the main difference is that all elements get 
 * shifted in a queue but not the same for a 
 * ring buffer
 *
 */

#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

/**
 * @brief namespace for the whole assignment
 */
namespace RingBuffer {

// forward declaration for the iterator
template <typename T> class ring_buffer_itr;

/**
 * @brief Class Ring Buffer
 */
template <typename T>
class ring_buffer {
 public:
  friend class ring_buffer_itr<T>;
  typedef ring_buffer_itr<T> iterator;

  /**
   * @brief constructor 
   * @param capacity is the capacity for the ring buffer
   */
  explicit ring_buffer(int capacity);
  /**
   *@brief destructor
   */
  ~ring_buffer();
  /**
   * @brief adding one element to the end 
   * of the ring buffer
   * @param element is the element to add
   * @return void
   */
  void push_back(T element);
  /**
   * @brief Removing one element for the 
   * front of the ring buffer
   * @param N/A
   * @return void
   */
  void pop_front();
  /**
     @brief Shows the element in the front
     @param N/A
     @return a reference to the element
   */
  T& front() const;
  /**
   * @brief Gets the current number of elements
   * inside the ring buffer
   * @param N/A
   * @return the current size
   */
  int size() const;
  /**
   * @brief Checks if the buffer is empty or not
   * @param N/A
   * @return True or False
   */
  bool empty() const;
  /**
   * @brief Returns an iterator that points to the 
   * front element of the buffer
   * @param N/A
   * @return an iterator pointing to the front
   */
  iterator begin() {return iterator(*this, 0);}
  /**
   * @brief Returns an iterator that points to the 
   * end of the end of the buffer
   * @param N/A
   * @return an iterator pointing to the end
   */
  iterator end() {return iterator(*this, size_);}

 private:
  const int capacity_;  ///< the maximum number of elements to hold
  int size_;  ///< no of elements inside the buffer
  int begin_;  ///< index of the front element
  T* buffer_;  ///< an array of T to hold the elements
};

/**
 * @brief Class iterator to the RingBuffer class
*/
template <typename T>
class ring_buffer_itr {
 public:
  friend class ring_buffer<T>;
  /**
   * @brief preincrement operator
   * @param N/A
   * @return a reference to a ring buffer iterator
   */
  ring_buffer_itr<T> & operator++();
  /**
   * @brief overloading the not equal operator
   * @param other is a const ring buffer iter object to 
   * compare against
   * @return True or False depending if the two objects are 
   * equal or not
   */
  bool operator!=(const ring_buffer_itr<T> & other);
  /**
   * @brief overloading the equality operator
   * @param other is a const ring buffer iter object to 
   * compar against
   * @return True of False depending if the two objects 
   * are equal or not
   */
  bool operator==(const ring_buffer_itr<T> & other);
  /**
   * @brief overloading the dereferencing operator
   * @param N/A
   * @return a reference to the element the iterator 
   * is pointing to
   */
  T & operator*();

 private:
  /**
   * @brief A private constructor. Only Friend classes can 
   * make an iterator object
   * @param buffer is a const reference to buffer object
   * @param offset tells where the iterator is standing at
   */
  ring_buffer_itr(const ring_buffer<T> & buffer, int offset);
  const ring_buffer<T> & buffer_;  ///< a const reference to a ring buffer
  int offset_;  ///< an offset indicating where the iterator is standing at
};
}  // namespace RingBuffer

#include "ring_buffer_class.cpp"

#endif  // RING_BUFFER_HPP
