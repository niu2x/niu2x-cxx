#include <niu2x/fs.h>
#include <filesystem>
#include "build_time/build_config.h"

namespace niu2x::fs {

bool exists(const Path& path)
{
	return std::filesystem::exists(path);
}

} // namespace niu2x::fs