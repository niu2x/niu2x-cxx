#ifndef NXC_LEXER_H
#define NXC_LEXER_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/result.h>
#include <nxc/null_file.h>

namespace nxc {
// reference
class NXC_API Lexer {
public:
    Lexer();
    virtual ~Lexer();

    NXC_INLINE void push_input(FILE* fp) { _push_input(fp); }
    NXC_INLINE void pop_input() { _pop_input(); }

    NXC_INLINE Result<int> lex() { return _lex(); }

protected:
    virtual void _push_input(FILE* fp) = 0;
    virtual void _pop_input() = 0;

    virtual Result<int> _lex() = 0;
};
} // namespace nxc

#define NXC_LEXER_DEFINE(NAME, prefix)                                         \
    class NAME : public nxc::Lexer {                                           \
    public:                                                                    \
        NAME()                                                                 \
        {                                                                      \
            auto ret = prefix##lex_init_extra(this, &scan_);                   \
            if (ret != 0) {                                                    \
                NXC_ABORT(                                                     \
                    #prefix "lex_init_extra failed with error code: %d\n");    \
            }                                                                  \
            prefix##set_in(nxc::NullFile::get()->c_file(), scan_);             \
        }                                                                      \
        virtual ~NAME() { prefix##lex_destroy(scan_); }                        \
                                                                               \
    protected:                                                                 \
        virtual void _push_input(FILE* fp) override { }                        \
        virtual nxc::Result<int> _lex() override                               \
        {                                                                      \
            return prefix##lex(scan_);                                         \
        }                                                                      \
                                                                               \
    private:                                                                   \
        yyscan_t scan_;                                                        \
    };

#endif