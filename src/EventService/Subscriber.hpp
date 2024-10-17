#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include "Event.hpp"
#include "EventService.hpp"
#include "../core/ActiveObject.hpp"
#include <memory>
#include <queue>


namespace es {
class Subscriber : public core::ActiveObject<Event> {
private:
  std::queue<std::shared_ptr<Event>> _messages;

protected:
  std::string name;
  Token subscriptionToken;
  std::shared_ptr<EventService> service;

public:
  Subscriber(std::string description = "");
  virtual ~Subscriber();
  virtual void process(const std::shared_ptr<Event> &event) override;
  void subscribe();
  void unsubscribe();
};
} // namespace es
#endif