#include "ylex.h"

#include <iostream>

auto main(int argc, char *argv[]) -> int  {
    constexpr  std::string_view input_file = "i32Hello ,World->;;var\n*";\
    const auto tokens = Tokenizer(input_file);
    printf("size: %lu\n", tokens.size());
    for (const auto &token : tokens) {
        if (token.GetKind() == YKindOfTokens::YTK_Identifier) {
            const auto identifier = token.GetIdentifier();
            printf("Kind: %s, Pos: ( line = %i,  column = %i), Data = %s \n", token.KindToString().data(), token.GetPos().line, token.GetPos().column, token.GetIdentifier().data());
        } else {
            printf("Kind: %s, Pos: ( line = %i,  column = %i)\n", token.KindToString().data(), token.GetPos().line, token.GetPos().column);
        }
    }
    return EXIT_SUCCESS;
}