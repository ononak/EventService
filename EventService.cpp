#include "EventService.hpp"
#include "Event.hpp"
#include <thread>
#include <utility>

std::shared_ptr<EventService> EventService::instance = nullptr;

std::shared_ptr<EventService> EventService::get() {
  if (instance == nullptr) {
    instance = std::shared_ptr<EventService>(new EventService());
  }
  return instance;
}

EventService::~EventService() {
  std::cout << "EventService destructor" << std::endl;
  notifier.disconnect_all_slots();
}
EventService::EventService() {}

void EventService::publish(std::shared_ptr<Event> message) {
  std::lock_guard<std::mutex> lock(eventLoopMutex);
  std::thread eventLoopThread([&]() { notifier(message); });
  eventLoopThread.join();
}

Token EventService::subscribe(const EventHandler &handler) {
  Token subscriptionToken = notifier.connect(handler);
  subscribers.insert(std::make_pair(subscriptionToken, handler));
  return subscriptionToken;
}

void EventService::unsubscribe(Token token) {
  notifier.disconnect(token);
  subscribers.erase(token);
}