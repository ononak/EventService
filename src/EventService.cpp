#include "EventService.hpp"
#include "Event.hpp"
#include <iostream>
#include <utility>

namespace es {
std::shared_ptr<EventService> EventService::instance = nullptr;

std::shared_ptr<EventService> EventService::get() {
  if (instance == nullptr) {
    instance = std::shared_ptr<EventService>(new EventService());
  }
  return instance;
}

EventService::~EventService() { notifier.unsubscribe_all(); }

EventService::EventService() {}

void EventService::publish(const std::shared_ptr<Event> &message) {
  notifier.publish(message);
}

Token EventService::subscribe(const EventHandler &handler) {
  Token subscriptionToken = notifier.subscribe(handler);
  subscribers.insert(std::make_pair(subscriptionToken, handler));
  return subscriptionToken;
}

void EventService::unsubscribe(Token token) {
  notifier.unsubscribe(token);
  subscribers.erase(token);
}

void EventService::run() {
  while (true)
    std::cin.get();
}
} // namespace es