extern "C" {
#include "jp-lexer.h"
}

#include <nxc/lexer.h>

NXC_LEXER_DEFINE(TestLexer, jp)

int main(int argc, char* argv[])
{
    auto lexer = NXC_MAKE_PTR(TestLexer);
    // FILE* fp = fopen(argv[1], "rb");
    // lexer->set_input(fp);
    lexer->lex();

    return 0;
}