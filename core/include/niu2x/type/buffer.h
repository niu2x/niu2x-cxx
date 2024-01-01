#ifndef NIU2X_TYPE_BUFFER_H
#define NIU2X_TYPE_BUFFER_H

#include <niu2x/api.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/preprocess.h>

namespace niu2x {

/**
 * @brief       A block of memory */
class NXAPI Buffer {
public:
    /**
     * @brief       constructor
     * @param       size of Buffer's memory*/
    Buffer(size_t size = 0);
    /**
     * @brief      read date from Buffer's memory
     *
     * @param      data    The buffer to receive data
     * @param[in]  offset  The offset
     * @param[in]  size    The size
     */
    void read(void* data, size_t offset, size_t size) const;

    /**
     * @brief       write data into Buffer's memory
     * @param       data    source
     * @param       offset  dest offset in Buffer's memory
     * @param       size    size of data */
    void write(const void* data, size_t offset, size_t size);

    /** @brief       get size of Buffer's memory
     * @return      size of Buffer's memory */
    size_t size() const { return buf_.size(); }

    /**
     * @brief       get const ptr of Buffer's memory
     * @return      const ptr of Buffer's memory  */
    const uint8_t* data() const { return buf_.data(); }

    /**
     * @brief       get ptr of Buffer's memory
     * @return      ptr of Buffer's memory  */
    uint8_t* data() { return buf_.data(); }

    /**
     * @brief       resize Buffer's memory
     * @param       s     new size
     */
    void resize(size_t s) { buf_.resize(s); }

    uint8_t& operator[](Index i) { return buf_[i]; }

    const uint8_t& operator[](Index i) const { return buf_[i]; }
    /**
     * @brief       convert Buffer's momory to String
     * @return      the String */
    String str() const { return String(buf_.begin(), buf_.end()); }

private:
    using MemBlock = Vector<uint8_t>;
    MemBlock buf_;
};

static_assert(type_pred::is_movable<Buffer>);
static_assert(type_pred::is_copyable<Buffer>);

}; // namespace niu2x

#endif