#include <nxc/lua.h>

#include <cstdint>
#include <cstddef>

namespace nxc {

enum class PseudoIndices : int32_t {
    REGISTRY = -10000,
    ENVIRON = -10001,
    GLOBALS = -10002,
};

static int32_t upvalueindex(int32_t i)
{
    return (int32_t)PseudoIndices::GLOBALS - i;
}

enum class ThreadStatus {
    YIELD = 1,
    ERRRUN = 2,
    ERRSYNTAX = 3,
    ERRMEM = 4,
    ERRERR = 5,
};

enum class Type : int8_t {
    NONE = -1,
    NIL = 0,
    BOOLEAN,
    LIGHT_USER_DATA,
    NUMBER,
    STRING,
    TABLE,
    FUNCTION,
    USER_DATA,
    THREAD,
};

static const int MIN_STACK = 20;
static const int WHITE0BIT = 0;
static const int WHITE1BIT = 1;

enum class Bits {
    WHITE_0 = 0,
    WHITE_1,
    BLACK,
    FINALIZED,
    KEY_WEAK,
    VALUE_WEAK,
    FIXED,
    SFIXED,
};

static const uint8_t WhiteMask = bit2mask();

union GCObject;
struct State;
struct GlobalState;

using CFunction = int (*)(State* S);
using Reader = const char* (*)(State* S, void* ud, size_t* sz);
using Writer = int (*)(State* S, const void* p, size_t sz, void* ud);
using Alloc = void* (*)(void* ud, void* ptr, size_t osize, size_t nsize);

using Number = double;
using Integer = int32_t;

#define CommonHeader                                                           \
    GCObject* next;                                                            \
    Type tt;                                                                   \
    uint8_t marked

struct GCheader {
    CommonHeader;
};

static State* State_new(Alloc f, void* ud);

union Value {
    GCObject* gc;
    void* p;
    Number n;
    int b;
};

#define TValuefields                                                           \
    Value value;                                                               \
    int tt

struct TValue {
    TValuefields;
};

using StkId = TValue*;

struct GlobalState {
    uint8_t current_white;
};

struct State {
    CommonHeader;
    uint8_t status;
    StkId top;
    StkId base;
    GlobalState g;
};

struct LG {
    State s;
    GlobalState g;
};

State* State_new(Alloc f, void* ud)
{
    int i;
    State* S;
    GlobalState* g;
    auto* lg = (LG*)(*f)(ud, NULL, 0, sizeof(LG));
    if (lg == NULL)
        return NULL;
    S = &(lg->s);
    g = &(lg->g);
    S->next = NULL;
    S->tt = Type::THREAD;
    g->current_white = bit2mask(WHITE0BIT, FIXEDBIT);
    S->marked = luaC_white(g);
    set2bits(S->marked, FIXEDBIT, SFIXEDBIT);
    preinit_state(S, g);
    g->frealloc = f;
    g->ud = ud;
    g->mainthread = S;
    g->uvhead.u.l.prev = &g->uvhead;
    g->uvhead.u.l.next = &g->uvhead;
    g->GCthreshold = 0; /* mark it as unfinished state */
    g->strt.size = 0;
    g->strt.nuse = 0;
    g->strt.hash = NULL;
    setnilvalue(registry(S));
    luaZ_initbuffer(S, &g->buff);
    g->panic = NULL;
    g->gcstate = GCSpause;
    g->rootgc = obj2gco(S);
    g->sweepstrgc = 0;
    g->sweepgc = &g->rootgc;
    g->gray = NULL;
    g->grayagain = NULL;
    g->weak = NULL;
    g->tmudata = NULL;
    g->totalbytes = sizeof(LG);
    g->gcpause = LUAI_GCPAUSE;
    g->gcstepmul = LUAI_GCMUL;
    g->gcdept = 0;
    for (i = 0; i < NUM_TAGS; i++)
        g->mt[i] = NULL;
    if (luaD_rawrunprotected(S, f_luaopen, NULL) != 0) {
        close_state(S);
        S = NULL;
    } else
        luai_userstateopen(S);
    return S;
}

} // namespace nxc