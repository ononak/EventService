#include "EventService.hpp"
#include <iostream>


namespace es {
std::shared_ptr<EventService> EventService::instance = nullptr;

std::shared_ptr<EventService> EventService::get() {
  if (instance == nullptr) {
    instance = std::shared_ptr<EventService>(new EventService());
  }
  return instance;
}

EventService::~EventService() {}

EventService::EventService() {}

void EventService::run() {
  while (true)
    std::cin.get();
}
} // namespace es