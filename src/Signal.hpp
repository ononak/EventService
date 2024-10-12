#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <string>

namespace es {

/**
 * @brief
 *
 */
class Token {
  template <typename T> friend class Signal;
  friend bool operator==(const Token &a, const Token &b);
  friend bool operator<(const Token &a, const Token &b);

public:
  Token(){};
  /**
   * @brief Destroy the Token object
   *
   */
  virtual ~Token(){};

  /**
   * @brief Construct a new Token object
   *
   */
  Token(const Token &) = default;

private:
  int _identifier;
  std::string _keyword;

  /**
   * @brief Construct a new Token object
   *
   * @param id
   * @param key
   */
  Token(int id, const std::string &key) : _identifier(id), _keyword(key){};
};

/**
 * @brief Interface definition for Signaling
 *
 * @tparam T
 */
template <typename T> class ISignal {
public:
  typedef std::function<void(const T &)> function_type;
  typedef std::map<Token, function_type> function_container_type;

public:
  virtual ~ISignal() {}
  virtual const Token connect(function_type slot,
                              const std::string &keyword = "") noexcept = 0;
  virtual void disconnect(const Token &Token) noexcept = 0;
  virtual void disconnect_all() noexcept = 0;
  virtual void operator()(const T &value) = 0;
  virtual size_t size() = 0;
};

/**
 * @brief Allow registering functions that could be invoked when data become
 * available
 *
 * @tparam T
 */
template <typename T> class Signal : public ISignal<T> {

public:
  /**
   * @brief Construct a new Signal object
   *
   */
  Signal() {}

  /**
   * @brief Destroy the Signal object
   *
   */
  virtual ~Signal() {
    std::lock_guard<std::mutex> lock(_mutex);
    _slots.clear();
  }

  /**
   * @brief
   *
   * @param slot
   * @param keyword
   * @return const Token
   */
  virtual const Token
  connect(typename ISignal<T>::function_type slot,
          const std::string &keyword = "") noexcept override {
    std::lock_guard<std::mutex> lock(_mutex);
    auto key = Token(_counter++, keyword);
    _slots.insert({key, slot});
    return key;
  }

  /**
   * @brief
   *
   * @param Token
   */
  virtual void disconnect(const Token &Token) noexcept override {
    std::lock_guard<std::mutex> lock(_mutex);
    _slots.erase(Token);
  }

  /**
   * @brief
   *
   */
  virtual void disconnect_all() noexcept override {
    std::lock_guard<std::mutex> lock(_mutex);
    for (auto [token, subs] : _slots)
      _slots.erase(token);
  }

  /**
   * @brief
   *
   * @param value
   */
  virtual void operator()(const T &value) override {
    std::lock_guard<std::mutex> lock(_mutex);
    for (auto sl : _slots) {
      sl.second.operator()(value);
    }
  }

  /**
   * @brief
   *
   * @return size_t
   */
  virtual size_t size() override {
    std::lock_guard<std::mutex> lock(_mutex);
    return _slots.size();
  }

private:
  static int _counter;
  std::mutex _mutex;
  typename ISignal<T>::function_container_type _slots;

  Signal(const Signal &) = delete;
  Signal(const Signal &&) = delete;
  Signal &operator=(const Signal &) = delete;
};

template <typename T> int Signal<T>::_counter = 0;

} // namespace es

#endif //
