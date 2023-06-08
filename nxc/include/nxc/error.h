#ifndef NXC_ERROR_H
#define NXC_ERROR_H

namespace nxc {

enum class Error {
    OK = 0,
    END_OF_FILE,
    FULL_OF_FILE,
    WAIT_IO,
    OS_ERROR,
    ZIP_LIB_ERROR,
    NO_EXIST,
    PARSER,
    TODO,
    NAME_TOO_LONG,
    ERROR,
};

using E = Error;

} // namespace nxc

#endif