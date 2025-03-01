#pragma once

#include <ios>
#include <mutex>

namespace lc::detail {

inline void configureStreamsIfNeeded() {
  static std::once_flag flag;
  std::call_once(flag, [] { std::ios_base::sync_with_stdio(false); });
}

} // namespace lc::detail
