#ifndef NIU2X_FS_PATH_H
#define NIU2X_FS_PATH_H

#include <niu2x/type.h>

namespace niu2x::fs {

class NXAPI Path : public String {
public:
    Path();
    Path(const String&);
    ~Path();
};

}; // namespace niu2x::fs

#endif