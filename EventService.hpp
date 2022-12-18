#include <memory>

struct Event;
struct Token;

class EventService {
private:
  EventService();

private:
  static std::shared_ptr<EventService> instance;

public:
  std::shared_ptr<EventService> get();
  virtual ~EventService();
  void publish(const Event &message);
  long subscribe();
  void unsubscribe(Token token);
};