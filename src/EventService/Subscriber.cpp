#include "Subscriber.hpp"
#include "EventService.hpp"
#include <sys/socket.h>
#include <unistd.h>

namespace es {
/**
 * @brief Construct a new Subscriber:: Subscriber object
 *
 * @param description
 */
Subscriber::Subscriber(std::string description)
    : name(description), core::ActiveObject<Event>(description) {
  service = EventService::get();
}

/**
 * @brief Destroy the Subscriber:: Subscriber object
 *
 */
Subscriber::~Subscriber() { unsubscribe(); }

void Subscriber::process(const std::shared_ptr<Event> &event) {
  throw std::logic_error("prcocess function is not implemented");
}
/**
 * @brief
 *
 */
void Subscriber::subscribe() {
  auto handler = std::bind(&Subscriber::onData, this, std::placeholders::_1);
  this->subscriptionToken = service->subscribe(handler);
  this->run();
}

/**
 * @brief
 *
 */
void Subscriber::unsubscribe() {
  service->unsubscribe(this->subscriptionToken);
}

} // namespace es