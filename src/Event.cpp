
#include "Event.hpp"

namespace es {

Event::Event(const char *data, unsigned int length) {
  auto data_ptr = std::shared_ptr<char[]>(new char[length]);
  memcpy(data_ptr.get(), data, length);
  _event_data = std::make_tuple(data_ptr, length);
}

Event::Event() { _event_data = std::make_tuple(nullptr, 0); };

Event::~Event(){};

const EventData &Event::get_event_data() const { return _event_data; }
} // namespace es