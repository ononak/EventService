#ifndef EVENT_HPP
#define EVENT_HPP

#include <memory>
#include <tuple>

namespace es {
typedef std::tuple<std::shared_ptr<char[]>, unsigned int> EventData;

/**
 * @brief
 *
 */
class Event {

public:
  Event(const char *data, unsigned int length);

  Event();

  virtual ~Event();

  Event(const Event &event) = default;

  Event &operator=(const Event &event) = default;

  const EventData &get_event_data() const;

private:
  EventData _event_data;
};
} // namespace es
#endif
