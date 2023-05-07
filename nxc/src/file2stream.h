#ifndef NXC_FILE_TO_STREAM_H
#define NXC_FILE_TO_STREAM_H

#include <nxc/stream.h>
#include "file.h"

namespace nxc {

ReadStreamPtr create_read_stream(FilePtr file, bool auto_close_file);

WriteStreamPtr create_write_stream(FilePtr file, bool auto_close_file);

} // namespace nxc

#endif