#ifndef NXC_PIPE_H
#define NXC_PIPE_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/result.h>
#include <nxc/stream.h>

namespace nxc {

NXC_API Result<size_t> pipe(ReadStream*, WriteStream*);

}

#endif