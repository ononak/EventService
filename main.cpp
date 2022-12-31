
#include "DummySubscriber.hpp"

int main(int, char **) {

  auto es = EventService::get();
  DummySubscriber subs1("Dummy 1");
  DummySubscriber subs2("Dummy 2");
  DummySubscriber subs3("Dummy 3");
  DummySubscriber subs4("Dummy 4");


  std::shared_ptr<Event> ev = std::shared_ptr<Event>(new Event());
  ev->data = "Dummy event data";
  es->publish(ev);
}
