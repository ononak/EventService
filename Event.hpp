#ifndef EVENT_HPP
#define EVENT_HPP

#include <boost/signals2.hpp>
#include <memory>
#include <string>
#include <functional>

struct Token : public boost::signals2::connection {

  Token() :boost::signals2::connection(){};
  Token(const boost::signals2::connection& token) : boost::signals2::connection(token) {};
};

struct Event {
  std::string data;
  virtual ~Event() {}
};

using EventHandler = std::function<void(std::shared_ptr<Event>)>;

struct Notifier : public boost::signals2::signal<void(std::shared_ptr<Event>)> {};
#endif