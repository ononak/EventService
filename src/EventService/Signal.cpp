#include "Signal.hpp"

namespace es {

bool operator==(const Token &a, const Token &b) {
  return (a._identifier == b._identifier) && (a._keyword == b._keyword);
}
bool operator<(const Token &a, const Token &b) {
  return (a._identifier < b._identifier);
}
} // namespace service