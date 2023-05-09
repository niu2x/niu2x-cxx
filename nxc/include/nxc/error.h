#ifndef NXC_ERROR_H
#define NXC_ERROR_H

namespace nxc {

enum class Error {
    OK = 0,
    END_OF_FILE,
    FULL_OF_FILE,
    OS_ERROR,
    ZIP_LIB_ERROR,
    NO_EXIST,
    PARSER,
    TODO,
};

using E = Error;

} // namespace nxc

#endif