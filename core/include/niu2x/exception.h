#ifndef NIU2X_TYPE_EXCEPTION_H
#define NIU2X_TYPE_EXCEPTION_H

#include <niu2x/api.h>
#include <niu2x/std_alias.h>

namespace niu2x {

void throw_os_err();
void throw_runtime_err(const String& err);
}; // namespace niu2x

#endif