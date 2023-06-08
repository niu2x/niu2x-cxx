#include <nxc/os.h>
#include <nxc/config.h>
#include <nxc/utils.h>

#if defined(NXC_USE_POSIX)
    #include <fcntl.h>
    #include <unistd.h>
    #include <errno.h>
    #include <limits.h>
    #include <sys/types.h>
    #include <sys/stat.h>
#endif

namespace nxc {

Result<void> OS::error()
{
#if defined(NXC_USE_POSIX)
    char buf[256];
    if (strerror_r(errno, buf, 256)) {
        snprintf(buf, 256, "strerror_r fail(%d)", errno);
    }
    Result<void> r(E::OS_ERROR, buf);
    return r;
#else
    return E::OS_ERROR;
#endif
}

Result<void> OS::make_dir(const char* dirname)
{
    NXC_LOG("OS::make_dir %s", dirname);
#if defined(NXC_USE_POSIX)
    if (!mkdir(dirname, 0777))
        return E::OK;
    return error();
#else
    return E::TODO;
#endif
}

Result<void> OS::make_dirs(const char* path)
{
    char tmp[PATH_MAX];
    auto path_len = strlen(path);
    if (*path == '/') {
        if (strlen(path) + 1 > PATH_MAX)
            return E::NAME_TOO_LONG;
        strcpy(tmp, path);
    } else {
        if (!getcwd(tmp, PATH_MAX))
            return E::NAME_TOO_LONG;
        auto tmp_len = strlen(tmp);

        if (tmp[tmp_len - 1] != '/') {
            if (tmp_len + 1 + 1 > PATH_MAX)
                return E::NAME_TOO_LONG;
            tmp_len++;
            tmp[tmp_len] = 0;
            tmp[tmp_len - 1] = '/';
        }

        if (path_len + 1 + tmp_len > PATH_MAX)
            return E::NAME_TOO_LONG;
        strcat(tmp, path);
    }

    char* it = tmp;
    if (*tmp == '/')
        it++;
    char* end = tmp + strlen(tmp);

    Result<void> ret = E::OK;

    do {
        char* it_end = strchrnul(it, path_sep);

        auto backup = *it_end;
        *it_end = 0;

        if (!is_dir(tmp)) {
            if (!(ret = make_dir(tmp))) {
                break;
            }
        }

        *it_end = backup;

        it = it_end + 1;
    } while (it < end);

    return ret;
}

bool OS::exist(const char* path)
{
#if defined(NXC_USE_POSIX)
    return access(path, F_OK) == 0;
#else
    return false;
#endif
}

bool OS::is_dir(const char* path)
{
#if defined(NXC_USE_POSIX)
    struct stat buf;
    if (stat(path, &buf) == 0) {
        return S_ISDIR(buf.st_mode);
    }
    return false;
#else
    return false;
#endif
}

const char OS::path_sep =
#if defined(NXC_USE_POSIX)
    '/'
#else
    '/'
#endif
    ;

} // namespace nxc