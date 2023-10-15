#ifndef NIU2X_TYPE_STD_ALIAS_H
#define NIU2X_TYPE_STD_ALIAS_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <sstream>
#include <memory>
#include <cmath>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <atomic>
#include <optional>
#include <functional>

namespace niu2x {

/**
 * @brief       String
 */
using String = std::string;
using StringBuf = std::stringstream;
using Exception = std::exception;
using BadAlloc = std::bad_alloc;

/**
 * @brief       RuntimeError
 */
using RuntimeError = std::runtime_error;

/**
 * @brief       SharedPtr
 */
template <class T>
using SharedPtr = std::shared_ptr<T>;

template <class T>
using InitializerList = std::initializer_list<T>;

/**
 * @brief       UniquePtr
 */
template <class T>
using UniquePtr = std::unique_ptr<T>;

/**
 * @brief       Vector
 */
template <class T>
using Vector = std::vector<T>;

/**
 * @brief       Optional
 */
template <class T>
using Maybe = std::optional<T>;

inline const auto maybe_null = std::nullopt;

template <class T>
using Function = std::function<T>;

/**
 * @brief       make_shared
 */
using std::make_shared;

/**
 * @brief       make_unique
 */
using std::make_unique;

/**
 * @brief       maximum of two value
 */
using std::max;

/**
 * @brief       minimum of two value
 */
using std::min;

using std::fmax;
using std::fmin;

using std::swap;
using std::to_string;

inline String to_string(bool b)
{
    if (b)
        return "true";
    else
        return "false";
}

} // namespace niu2x

#endif