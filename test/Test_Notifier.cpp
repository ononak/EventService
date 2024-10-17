
#include "../src/EventService/Notifier.hpp"
#include <gtest/gtest.h>


class TestFunctor {
public:
  void operator()(const int &data) const { const_cast<int &>(data)++; }
};

TEST(NotifierTest, NotifierSubscribeUnsubscribeTest) {
  TestFunctor fnc;
  auto notifier = es::Notifier<int>();
  std::vector<es::Token> tokens;
  const int N = 50;

  for (auto i = 0; i < N; i++) {
    auto token = notifier.subscribe(fnc);
    tokens.push_back(token);
    EXPECT_EQ(i + 1, notifier.nof_subscriber());
  }

  auto noft = N;
  for (auto t : tokens) {
    notifier.unsubscribe(t);
    EXPECT_EQ(noft -= 1, notifier.nof_subscriber());
  }
}
