#ifndef NIU2X_TYPE_STD_ALIAS_H
#define NIU2X_TYPE_STD_ALIAS_H

#include <cstdint>
#include <stdexcept>
#include <variant>
#include <array>
#include <string>
#include <sstream>
#include <memory>
#include <cmath>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <iostream>
#include <variant>
#include <map>
#include <unordered_map>
#include <atomic>
#include <optional>
#include <functional>
#include <chrono>
#include <type_traits>

namespace niu2x {

/**
 * @brief       String
 */
using String = std::string;
using StringBuf = std::stringstream;
using Exception = std::exception;
using BadAlloc = std::bad_alloc;
using OutOfRange = std::out_of_range;

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
using SPtr = SharedPtr<T>;

template <class T>
using InitializerList = std::initializer_list<T>;

/**
 * @brief       UniquePtr
 */
template <class T>
using UniquePtr = std::unique_ptr<T>;

template <class T>
using UPtr = UniquePtr<T>;
/**
 * @brief       Vector
 */
template <class T>
using Vector = std::vector<T>;

template <class Key, class Value>
using Map = std::map<Key, Value>;

template <class Key, class Value>
using HashMap = std::unordered_map<Key, Value>;

template <class... ArgTypes>
using Variant = std::variant<ArgTypes...>;

template <class T, int N>
using Array = std::array<T, N>;

using std::get;

template <class T>
using CR = const T&;

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
using std::move;

using std::fmax;
using std::fmin;

using std::sort;
using std::swap;
using std::to_string;

using std::floor;

inline String to_string(bool b)
{
    if (b)
        return "true";
    else
        return "false";
}

namespace type_pred {

template <class T>
inline constexpr bool is_move_constructible
    = std::is_nothrow_move_constructible_v<T>;

template <class T>
inline constexpr bool is_move_assignable = std::is_nothrow_move_assignable_v<T>;

template <class T>
inline constexpr bool is_movable
    = is_move_constructible<T>&& is_move_assignable<T>;

template <class T>
inline constexpr bool is_copyable
    = std::is_copy_constructible_v<T>&& std::is_copy_assignable_v<T>;

template <class T1, class T2>
inline constexpr bool is_same = std::is_same_v<T1, T2>;
} // namespace type_pred

namespace type_conv {

template <class T>
using decay = std::decay_t<T>;

}

namespace type_pred {
template <class T1, class T2>
inline constexpr bool is_same_decay
    = is_same<type_conv::decay<T1>, type_conv::decay<T2>>;

}

using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
inline TimePoint time_now() { return std::chrono::system_clock::now(); }

using TimeDuration = double;

inline TimeDuration time_diff(const TimePoint& t_old, const TimePoint& t_new)
{
    static double scale = 1.0 / 1000;
    using std_ms = std::chrono::milliseconds;
    return std::chrono::duration_cast<std_ms>(t_new - t_old).count() * scale;
}

inline TimeDuration time_diff(const TimePoint& t_new)
{
    static double scale = 1.0 / 1000;
    using std_ms = std::chrono::milliseconds;
    return std::chrono::duration_cast<std_ms>(t_new.time_since_epoch()).count()
        * scale;
}

template <class T>
inline const T nan = std::numeric_limits<T>::quiet_NaN();

inline bool near_zero(float num)
{
    float epsilon = 1e-8;
    return std::abs(num) < epsilon;
}

} // namespace niu2x

#endif