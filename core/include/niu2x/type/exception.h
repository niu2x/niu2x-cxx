#ifndef NIU2X_TYPE_EXCEPTION_H
#define NIU2X_TYPE_EXCEPTION_H

#include <niu2x/api.h>
#include <niu2x/type/std_alias.h>

namespace niu2x {

NXAPI void throw_os_err();
NXAPI void throw_runtime_err(const String& err);
};

#endif