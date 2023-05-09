extern "C" {
#include "jp-lexer.h"
#include "jp-parser.h"
}

#include <nxc/lexer.h>

NXC_LEXER_DEFINE(TestLexer, jp);
NXC_PARSER_DEFINE(TestParser, jp);

int main(int argc, char* argv[])
{
    auto lexer = NXC_MAKE_PTR(TestLexer);
    auto parser = NXC_MAKE_PTR(TestParser);
    // FILE* fp = fopen(argv[1], "rb");
    // lexer->set_input(fp);
    lexer->push_input(stdin);
    nxc::Token result;
    do {
        result = lexer->lex();
        printf("token %d\n", result.type);
        auto parse_ret = parser->parse(result);
        if (!parse_ret) {
            printf("error: %s\n", parse_ret.error_msg().c_str());
            break;
        }
    } while (result.type != T_EOF);
    lexer->pop_input();
    return 0;
}