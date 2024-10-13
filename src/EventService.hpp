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

class EventService : public Notifier<std::shared_ptr<Event>> {
private:
  EventService();

private:
  static std::shared_ptr<EventService> instance;
public:
  static std::shared_ptr<EventService> get();
  virtual ~EventService();
  void run();
};

} // namespace es
#endif