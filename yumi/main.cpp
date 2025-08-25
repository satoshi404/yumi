#include "ylex.h"

#include <iostream>

auto main(int argc, char *argv[]) -> int  {
    constexpr  std::string_view input_file = "Hello,World    ;;\n*";
    auto tokens = Tokenizer(input_file);
    printf("size: %lu\n", tokens.size());
    for (const auto &token : tokens) {
        printf("Kind: %s, Pos: ( line = %i,  column = %i)\n", token.ToString().data(), token.GetPos().line, token.GetPos().column);
    }
    return EXIT_SUCCESS;
}