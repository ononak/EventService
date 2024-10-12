#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include "Event.hpp"
#include "EventService.hpp"
#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

namespace es {
class Subscriber {
private:
  std::queue<std::shared_ptr<Event>> _messages;
  std::mutex _mutex;
  std::condition_variable _condition;
  std::atomic<bool> _shutdown;
  std::thread _thread;

protected:
  std::string name;
  Token subscriptionToken;
  std::shared_ptr<EventService> service;

public:
  Subscriber(std::string description = "");
  virtual ~Subscriber();
  void onEvent(const std::shared_ptr<Event> &event);
  virtual void process(const std::shared_ptr<Event> &event) = 0;
  void subscribe();
  void unsubscribe();

private:
  void dataLoop();
};
} // namespace es
#endif