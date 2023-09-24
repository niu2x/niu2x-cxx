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
#include <optional>

namespace niu2x {

/**
 * @brief       String
 */
using String = std::string;
using StringBuf = std::stringstream;
using Exception = std::exception;

/**
 * @brief       RuntimeError
 */
using RuntimeError = std::runtime_error;

/**
 * @brief       SharedPtr
 */
template <class T>
using SharedPtr = std::shared_ptr<T>;

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

} // namespace niu2x

#endif