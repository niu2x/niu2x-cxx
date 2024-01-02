#ifndef NIU2X_UV_HELPER_H
#define NIU2X_UV_HELPER_H

#define UV_TYPE(T, ptr)    reinterpret_cast<T>((ptr))
#define UV_IS_CLOSING(ptr) uv_is_closing((uv_handle_t*)(ptr))
#define UV_IS_ACTIVE(ptr)  uv_is_active((uv_handle_t*)(ptr))
#define UV_CLOSE(ptr)      uv_close((uv_handle_t*)(ptr), uv_close_cb)
#define UV_STOP(ptr, stop) stop((ptr))

#define UV_FETCH_WRAPPER(type, ptr, target_var)                                \
    auto uv_obj = reinterpret_cast<uv_handle_t*>((ptr));                       \
    auto target_var = reinterpret_cast<type*>(uv_obj->data);

#define UV_ENSURE_STOP(ptr, stop)                                              \
    if (UV_IS_ACTIVE((ptr))) {                                                 \
        UV_STOP((ptr), stop);                                                  \
    }

#define UV_ENSURE_CLOSE(ptr, loop_)                                            \
    if (!UV_IS_CLOSING((ptr))) {                                               \
        UV_CLOSE((ptr));                                                       \
        (loop_)->run_once();                                                   \
    }

namespace niu2x::uv {
inline void uv_close_cb(uv_handle_t*) { }
} // namespace niu2x::uv

#endif