#include "Subscriber.hpp"
#include "EventService.hpp"
#include <iostream>
#include <mutex>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

namespace es {
/**
 * @brief Construct a new Subscriber:: Subscriber object
 *
 * @param description
 */
Subscriber::Subscriber(std::string description)
    : name(description), _shutdown(false) {
  service = EventService::get();
}

/**
 * @brief Destroy the Subscriber:: Subscriber object
 *
 */
Subscriber::~Subscriber() {
  _shutdown.store(true);
  unsubscribe();
  _condition.notify_all();
  _thread.join();
}

/**
 * @brief
 *
 */
void Subscriber::subscribe() {
  auto handler = std::bind(&Subscriber::onEvent, this, std::placeholders::_1);
  this->subscriptionToken = service->subscribe(handler);
  _thread = std::thread(&Subscriber::dataLoop, this);
}

/**
 * @brief
 *
 */
void Subscriber::unsubscribe() {
  std::unique_lock<std::mutex> lock(_mutex);
  service->unsubscribe(this->subscriptionToken);
}

/**
 * @brief
 *
 * @param event
 */
void Subscriber::onEvent(const std::shared_ptr<Event> &event) {
  std::unique_lock<std::mutex> lock(_mutex);
  _messages.push(event);
  _condition.notify_all();
}

/**
 * @brief
 *
 */
void Subscriber::dataLoop() {
  std::unique_lock<std::mutex> lock(_mutex);

  while (_shutdown.load() != true) {
    _condition.wait(lock);
    for (; !_messages.empty(); _messages.pop()) {
      auto data = _messages.front();
      try {
        this->process(data);
      } catch (...) {
        std::cout << "Subscriber " << name
                  << " -> Unknown exception: " << std::endl;
      }
    }
  }
}

} // namespace es