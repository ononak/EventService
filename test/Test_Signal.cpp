#include "../src/EventService/Signal.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * @brief Construct a new TEST object
 *
 */

/**
 * @brief Functor as a callback function
 * 
 */
class TestFunctor {
public:
  virtual void operator()(const int &data)  { const_cast<int &>(data)++; }
};

class ITestFunctor {
public:
virtual ~ITestFunctor() { }
  virtual void operator()(const int &data)  = 0;
};

class MockFunctor : public ITestFunctor {
  public: 
  MOCK_METHOD(void, functor, (const int& data));
  virtual void operator()(const int &data)  override { functor(data); }
};

/**
 * @brief Lambda expression as a callback function
 * 
 */
auto fnc = [](const int &data) { const_cast<int &>(data)++; };

/**
 * @brief Construct a new TEST object
 * 
 */
TEST(SignalTest, ConnectDisconnectFuction_with_LambdaExp) {

  es::Signal<int > signal;
  std::vector<es::Token> tokens;
  const int N = 5;

  for (auto i = 0; i < N; i++) {
    auto token = signal.connect(fnc);
    tokens.push_back(token);
    EXPECT_EQ(i + 1, signal.size());
  }

  auto noft = N;
  for (auto t : tokens) {
    signal.disconnect(t);
    EXPECT_EQ(noft -= 1, signal.size());
  }
}


/**
 * @brief Construct a new TEST object
 * 
 */
TEST(SignalTest, ConnectDisconnectFuction_with_Functor) {

  es::Signal<int> signal;
  std::vector<es::Token> tokens;
  TestFunctor fnc;
  const int N = 5;

  for (auto i = 0; i < N; i++) {
    auto token = signal.connect(fnc);
    tokens.push_back(token);
    EXPECT_EQ(i + 1, signal.size());
  }

  auto noft = N;
  for (auto t : tokens) {
    signal.disconnect(t);
    EXPECT_EQ(noft -= 1, signal.size());
  }
}