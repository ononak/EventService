
// #include "DummySubscriber.hpp"
// #include <memory>

#include "../src/EventService.hpp"
#include "../src/Subscriber.hpp"
#include <__fwd/get.h>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

  std::mutex mymutex;
class MySubscriber : public es::Subscriber {


public:
  MySubscriber(const std::string name) : es::Subscriber(name) {}
  void process(const std::shared_ptr<es::Event> &event) {
    std::lock_guard<std::mutex> lock(mymutex);
    auto data = event.get()->get_event_data();

    std::cout << "Subscriber  " << this->name <<" received data" << std::get<0>(data) << std::endl;
  }
};

int main(int, char **) {

  auto eventService = es::EventService::get();
  MySubscriber ms1("ms1");
  ms1.subscribe();
  MySubscriber ms2("ms2");
  ms2.subscribe();
  MySubscriber ms3("ms3");
  ms3.subscribe();
  MySubscriber ms4("ms4");
  ms4.subscribe();
  MySubscriber ms5("ms5");
  ms5.subscribe();

  srand(time(NULL));

  for (auto i = 0; i < 18810; i++) {
    int iSecret = rand() % 1000 + 1;
    std::stringstream ss;
    ss << iSecret;

    auto ev = std::shared_ptr<es::Event>(new es::Event(ss.str().c_str(), 3));
    eventService->publish(ev);
  }

  eventService->run();
}
