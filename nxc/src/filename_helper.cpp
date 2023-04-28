#include <nxc/filename_helper.h>



namespace nxc {
String FilenameHelper::executable(const String& name) {
	#if defined(_WIN32)
	return name + ".exe";
	#else
	return name;
	#endif
}
}

