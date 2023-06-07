#ifndef NXC_LEXER_H
#define NXC_LEXER_H

#include <nxc/api.h>
#include <nxc/utils.h>
#include <nxc/result.h>

namespace nxc {

struct NXC_API Token {
    int type;
    void* value;
};

// reference
class NXC_API Lexer {
public:
    Lexer();
    virtual ~Lexer();

    NXC_INLINE void push_input(FILE* fp) { _push_input(fp); }
    NXC_INLINE void pop_input() { _pop_input(); }
    NXC_INLINE Token lex() { return _lex(); }

protected:
    virtual void _push_input(FILE* fp) = 0;
    virtual void _pop_input() = 0;

    virtual Token _lex() = 0;
};

class NXC_API Parser {
public:
    Parser();
    virtual ~Parser();

    NXC_INLINE Result<void> parse(const nxc::Token& token, void* userdata)
    {
        return _parse(token, userdata);
    }

protected:
    virtual Result<void> _parse(const nxc::Token&, void* userdata) = 0;
};

} // namespace nxc

#define NXC_LEXER_DEFINE(NAME, prefix)                                         \
    class NAME : public nxc::Lexer {                                           \
    public:                                                                    \
        NAME()                                                                 \
        {                                                                      \
            auto ret = prefix##lex_init_extra(&token_value_, &scan_);          \
            if (ret != 0) {                                                    \
                NXC_ABORT(#prefix                                              \
                    "lex_init_extra failed with error code: %d\n",             \
                    ret);                                                      \
            }                                                                  \
            prefix##set_in(nullptr, scan_);                                    \
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
        virtual nxc::Token _lex() override                                     \
        {                                                                      \
            return { .type = prefix##lex(scan_), .value = &token_value_ };     \
        }                                                                      \
        virtual void _pop_input() override                                     \
        {                                                                      \
            prefix##pop_buffer_state(scan_);                                   \
        }                                                                      \
                                                                               \
    private:                                                                   \
        yyscan_t scan_;                                                        \
        YYSTYPE token_value_;                                                  \
    };

#define NXC_PARSER_DEFINE(NAME, prefix)                                        \
    extern "C" {                                                               \
    extern void prefix##error(void* p, void*, const char*);                    \
    }                                                                          \
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
        virtual nxc::Result<void> _parse(                                      \
            const nxc::Token& token, void* userdata) override                  \
        {                                                                      \
            error_msg_ = "";                                                   \
            auto ret = prefix##push_parse(                                     \
                state_, token.type, (YYSTYPE*)token.value, this, userdata);    \
            if (error_msg_.size() > 0) {                                       \
                return nxc::Result<void>(nxc::E::PARSER, error_msg_);          \
            }                                                                  \
            if (ret == 1)                                                      \
                return nxc::E::PARSER;                                         \
            return nxc::E::OK;                                                 \
        }                                                                      \
                                                                               \
    private:                                                                   \
        void error(const char* msg) { error_msg_ += msg; }                     \
        prefix##pstate* state_;                                                \
        std::string error_msg_;                                                \
        friend void prefix##error(void* p, void*, const char*);                \
    };                                                                         \
    extern "C" {                                                               \
    void prefix##error(void* p, void*, const char* msg)                        \
    {                                                                          \
        auto parser = (NAME*)(p);                                              \
        parser->error(msg);                                                    \
    }                                                                          \
    }

#endif