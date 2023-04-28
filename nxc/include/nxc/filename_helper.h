#ifndef NXC_FILENAME_HELPER_H
#define NXC_FILENAME_HELPER_H

#include <nxc/api.h>
#include <nxc/utils.h>

namespace nxc {
	class NXC_API FilenameHelper {
	public:
		static String executable(const String& name);
	};
}

#endif