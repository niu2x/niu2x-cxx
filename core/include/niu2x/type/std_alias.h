#ifndef NIU2X_TYPE_STD_ALIAS_H
#define NIU2X_TYPE_STD_ALIAS_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <sstream>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <atomic>

namespace niu2x {

using String = std::string;
using StringBuf = std::stringstream;
using Exception = std::exception;
using RuntimeError = std::runtime_error;

template <class T>
using SharedPtr = std::shared_ptr<T>;

template <class T>
using Vector = std::vector<T>;

using std::make_shared;
using std::max;
using std::min;

} // namespace niu2x

#endif