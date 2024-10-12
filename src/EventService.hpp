#ifndef EVENT_SERVICE_HPP
#define EVENT_SERVICE_HPP
#pragma once

#include "Notifier.hpp"
#include "Event.hpp"
#include <map>
#include <memory>

namespace es {

using EventHandler = Notifier<std::shared_ptr<Event>>::subscriber_function;

typedef std::string EventChannel;

class EventService {
private:
  EventService();

private:
  static std::shared_ptr<EventService> instance;
  std::map<Token, EventHandler> subscribers;
  Notifier<std::shared_ptr<Event>> notifier;
  std::mutex eventLoopMutex;

public:
  static std::shared_ptr<EventService> get();
  virtual ~EventService();
  void publish(const std::shared_ptr<Event>& message);
  Token subscribe(const EventHandler &handler);
  void unsubscribe(Token token);
  void run();
};

} // namespace es
#endif