#ifndef EVENT_SERVICE_HPP
#define EVENT_SERVICE_HPP
#pragma once

#include "Event.hpp"
#include <map>
#include <memory>


struct Event;
struct Token;
struct Notifier;

typedef std::string EventChannel;

class EventService{
private:
  EventService();

private:
  static std::shared_ptr<EventService> instance;
  std::map<Token, EventHandler> subscribers;
  Notifier notifier; 
  std::mutex eventLoopMutex;

public:
  static std::shared_ptr<EventService> get();
  virtual ~EventService();
  void publish(std::shared_ptr<Event> message);
  Token subscribe(const EventHandler& handler );
  void unsubscribe(Token token);
};

#endif