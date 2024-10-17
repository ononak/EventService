
#ifndef NOTIFIER_HPP
#define NOTIFIER_HPP

#include "Signal.hpp"
#include <memory>

namespace es {

/**
 * @brief Notification class
 * Delivers published data to the subscribers
 *
 * @tparam T
 */
template <typename T> class Notifier : protected Signal<T> {
public:
  using subscriber_function = typename Signal<T>::function_type;

public:
  Notifier() : Signal<T>() {}

  /**
   * @brief Subscribe to notifications
   *
   * @param on_signal
   * @return const Token&
   */
  const Token subscribe(subscriber_function on_signal) {
    return this->connect(on_signal, "");
  }

  /**
   * @brief Unsubscribe
   *
   * @param token
   */
  void unsubscribe(const Token &token) { return this->disconnect(token); }

  /**
   * @brief Unsubscribe
   *
   * @param token
   */
  void unsubscribe_all() { return this->disconnect_all(); }

  /**
   * @brief Publish data
   *
   * @param data
   */
  void publish(const T &data) { this->operator()(data); }

  /**
   * @brief returns the number of subscribers
   *
   * @return int
   */
  int nof_subscriber() { return this->size(); }

private:
  static std::shared_ptr<Notifier> _instance;
};

} // namespace es

#endif