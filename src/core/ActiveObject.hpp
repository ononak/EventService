#ifndef ACTIVEOBJECT_HPP
#define ACTIVEOBJECT_HPP

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

namespace core {

template <typename T> class ActiveObject {
private:
  std::queue<std::shared_ptr<T>> _data_store;
  std::mutex _mutex;
  std::condition_variable _condition;
  std::atomic<bool> _shutdown;
  std::thread _thread;
  std::string _name;

public:
  ActiveObject(std::string description = "");
  virtual ~ActiveObject();
  virtual void process(const std::shared_ptr<T> &data) = 0;

protected:
  virtual void onData(const std::shared_ptr<T> &data);
  virtual void run();

public:
  virtual void dataLoop();
};

template <typename T>
ActiveObject<T>::ActiveObject(std::string description)
    : _name(description), _shutdown(false){};

template <typename T> ActiveObject<T>::~ActiveObject() {
  _shutdown.store(true);
  _condition.notify_all();
  _thread.join();
};

template <typename T>
void ActiveObject<T>::onData(const std::shared_ptr<T> &data) {
  std::unique_lock<std::mutex> lock(_mutex);
  _data_store.push(data);
  _condition.notify_one();
}

template <typename T> void ActiveObject<T>::run() {
  std::unique_lock<std::mutex> lock(_mutex);
  _thread = std::thread(std::mem_fn(&ActiveObject<T>::dataLoop), this);
}

template <typename T> void ActiveObject<T>::dataLoop() {
  std::unique_lock<std::mutex> lock(_mutex);

  while (_shutdown.load() != true) {
    _condition.wait(lock);
    for (; !_data_store.empty(); _data_store.pop()) {
      auto data = _data_store.front();
      try {
        this->process(data);
      } catch (...) {
        std::cout << "Subscriber " << _name
                  << " -> Unknown exception: " << std::endl;
      }
    }
  }
}

} // namespace core
#endif