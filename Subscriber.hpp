#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include "EventService.hpp"

class Subscriber {

protected:
  std::string name;
  Token subscriptionToken;
  std::shared_ptr<EventService> service;

public:
  Subscriber(std::string description = "");
  virtual ~Subscriber();
  virtual void onEvent(std::shared_ptr<Event> event) = 0;

protected:
  void subscribe();
  void unsubscribe();
};

#endif