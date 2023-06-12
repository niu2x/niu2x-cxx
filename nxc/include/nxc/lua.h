#ifndef NXC_LUA_H
#define NXC_LUA_H

namespace nxc {

union GCObject;
#define CommonHeader                                                           \
    GCObject* next;                                                            \
    uint8_t tt;                                                                \
    uint8_t marked

struct GCheader {
    CommonHeader;
};

} // namespace nxc

#endif