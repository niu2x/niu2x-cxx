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
    lexer->push_input(stdin);

    nxc::Result<int> result;
    do {
        result = lexer->lex();
        printf("TOKEN %d\n", *result);
    } while (result && *result != EOF);

    lexer->pop_input();

    return 0;
}