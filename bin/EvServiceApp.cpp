

#include "../src/EventService/EventService.hpp"
#include "../src/EventService/Subscriber.hpp"
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

std::mutex mymutex;

int received = 0;
class MySubscriber : public es::Subscriber {

public:
  MySubscriber(const std::string name) : es::Subscriber(name) {}
  void process(const std::shared_ptr<es::Event> &event) override {
    std::lock_guard<std::mutex> lock(mymutex);
    auto data = event.get()->get_event_data();

    std::cout << "Subscriber  " << this->name << " received data " << received++
              << std::endl; // std::get<0>(data) << std::endl;
  }
};

int main(int, char **) {

  std::vector<std::shared_ptr<MySubscriber>> mysubscribers;
  auto eventService = es::EventService::get();
  for (auto i = 0; i < 100; i++) {

    mysubscribers.push_back(
        std::shared_ptr<MySubscriber>(new MySubscriber("My Subscriber")));
        mysubscribers[i]->subscribe();
  }

  srand(time(NULL));

  for (auto i = 0; i < 60; i++) {
    int iSecret = i; // rand() % 1000 + 1;
    std::stringstream ss;
    ss << iSecret;

    auto ev = std::shared_ptr<es::Event>(new es::Event(ss.str().c_str(), 3));
    // std::cout << "pubish " <<i<< std::endl;
    eventService->publish(ev);
  }

  eventService->run();
}
