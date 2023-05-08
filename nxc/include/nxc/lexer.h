#ifndef NXC_LEXER_H
#define NXC_LEXER_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/result.h>
#include <nxc/null_file.h>

union YYSTYPE;

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

class NXC_API Parser {
public:
    Parser();
    virtual ~Parser();

    NXC_INLINE Result<bool> parse(int token, YYSTYPE const* pushed_val)
    {
        return _parse(token, pushed_val);
    }

protected:
    virtual Result<bool> _parse(int token, YYSTYPE const* pushed_val) = 0;
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
        virtual void _push_input(FILE* fp) override                            \
        {                                                                      \
            YY_BUFFER_STATE new_buffer                                         \
                = prefix##_create_buffer(fp, YY_BUF_SIZE, scan_);              \
            NXC_ASSERT(new_buffer, "OOM");                                     \
            prefix##push_buffer_state(new_buffer, scan_);                      \
        }                                                                      \
        virtual nxc::Result<int> _lex() override                               \
        {                                                                      \
            return prefix##lex(scan_);                                         \
        }                                                                      \
        virtual void _pop_input() override                                     \
        {                                                                      \
            prefix##pop_buffer_state(scan_);                                   \
        }                                                                      \
                                                                               \
    private:                                                                   \
        yyscan_t scan_;                                                        \
    };

#define NXC_PARSER_DEFINE(NAME, prefix)                                        \
    class NAME : public nxc::Parser {                                          \
    public:                                                                    \
        NAME()                                                                 \
        {                                                                      \
            state_ = prefix##pstate_new();                                     \
            NXC_ASSERT(state_, "OOM");                                         \
        }                                                                      \
        virtual ~NAME() { prefix##pstate_delete(state_); }                     \
                                                                               \
    protected:                                                                 \
        virtual Result<bool> _parse(                                           \
            int token, YYSTYPE const* pushed_val) override                     \
        {                                                                      \
            return false;                                                      \
        }                                                                      \
                                                                               \
    private:                                                                   \
        jppstate* state_;                                                      \
    };

#endif