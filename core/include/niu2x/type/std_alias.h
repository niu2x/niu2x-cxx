#ifndef NIU2X_TYPE_STD_ALIAS_H
#define NIU2X_TYPE_STD_ALIAS_H

#include <stdexcept>
#include <string>

namespace niu2x {

using String = std::string;
using Exception = std::exception;
using RuntimeError = std::runtime_error;

} // namespace niu2x

#endif