extern "C" {
#include "lisp.h"
#include "lisp-lexer.h"
#include "lisp-parser.h"
}

#include <nxc/lexer.h>

NXC_LEXER_DEFINE(TestLexer, lisp);
NXC_PARSER_DEFINE(TestParser, lisp);

int main(int argc, char* argv[])
{

    lisp_t* lisp = lisp_alloc();

    auto lexer = NXC_MAKE_PTR(TestLexer);
    auto parser = NXC_MAKE_PTR(TestParser);
    lexer->push_input(stdin);
    nxc::Token result;
    do {
        result = lexer->lex();
        // printf("token %d\n", result.type);
        auto parse_ret = parser->parse(result, lisp);
        if (!parse_ret) {
            printf("error: %s\n", parse_ret.error_msg().c_str());
            break;
        }
    } while (result.type != T_EOF);
    lexer->pop_input();

    lisp_free(lisp);

    return 0;
}