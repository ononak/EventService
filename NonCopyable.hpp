#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP
#pragma once

template <class T> class NonCopyable{

  public: 
    NonCopyable (const NonCopyable &) = delete;
    NonCopyable & operator = (const NonCopyable &) = delete;

  protected:
    NonCopyable () = default;
    ~NonCopyable () = default; /// Protected non-virtual destructor


};

#endif