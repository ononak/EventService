#ifndef DUMMY_SUBSCRIBER_HPP
#define DUMMY_SUBSCRIBER_HPP

#include "Subscriber.hpp"
#include <iostream>

class DummySubscriber : public Subscriber {

public:
  DummySubscriber(std::string name) : Subscriber(name){};

  virtual ~DummySubscriber(){};

  void onEvent(std::shared_ptr<Event> event) override {

    std::cout << name << " onEvent data : " << event->data << std::endl;
  }
};

#endif