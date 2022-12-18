#ifndef EVENT_SERVICE_HPP
#define EVENT_SERVICE_HPP
#pragma once

#include "NonCopyable.hpp"
#include <memory>

struct Event;
struct Token;

class EventService : NonCopyable<EventService>{
private:
  EventService();

private:
  static std::shared_ptr<EventService> instance;

public:
  std::shared_ptr<EventService> get();
  virtual ~EventService();
  void publish(const Event &message);
  Token subscribe();
  void unsubscribe(Token token);
};

#endif