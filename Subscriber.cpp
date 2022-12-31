#include "Subscriber.hpp"
#include "EventService.hpp"

Subscriber::Subscriber(std::string description) {
  name = description;
  service = EventService::get();
  subscribe();
}

Subscriber::~Subscriber() { unsubscribe(); }

void Subscriber::subscribe() {
  auto handler = std::bind(&Subscriber::onEvent, this, std::placeholders::_1);
  this->subscriptionToken = service->subscribe(handler);
}

void Subscriber::unsubscribe() {
  service->unsubscribe(this->subscriptionToken);
}