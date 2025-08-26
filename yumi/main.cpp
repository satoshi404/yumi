#include "ylex.h"

#include <iostream>

auto main(int argc, char *argv[]) -> int  {
    constexpr  std::string_view input_file = "fn main() -> i32 { return 0; }\n";\
    const auto tokens = Tokenizer(input_file);
    printf("size: %lu\n", tokens.size());
    for (const auto &token : tokens) {
        if (token.GetKind() == YKindOfTokens::YTK_Identifier) {
            printf("Kind: %s, Pos: ( line = %i,  column = %i), Data = %s \n", token.KindToString().data(), token.GetPos().line, token.GetPos().column, token.GetIdentifier().data());
        } else if (token.GetKind() == YKindOfTokens::YTK_LiteralInteger) {
            printf("Kind: %s, Pos: ( line = %i,  column = %i), Data = %i \n", token.KindToString().data(), token.GetPos().line, token.GetPos().column, token.GetLiteralInteger());
        } else {
            printf("Kind: %s, Pos: ( line = %i,  column = %i)\n", token.KindToString().data(), token.GetPos().line, token.GetPos().column);
        }
    }
    return EXIT_SUCCESS;
}