//
// Created by satoshi on 25/08/2025.
//

#include "ylex.h"
#include <unordered_map>

static const std::vector<std::string_view> listOfKeywords = {
    "fn", "return", "var", "final", "i32"
};

static const std::unordered_map<char, YKindOfTokens> listOfSingleSymbols {
    { ';', YKindOfTokens::YTK_Semicolon},
    { '{', YKindOfTokens::YTK_LeftBrace},
    { '}', YKindOfTokens::YTK_RightBrace },
    { '(', YKindOfTokens::YTK_LeftParenthesis},
    { ')', YKindOfTokens::YTK_RightParenthesis},
    { '=', YKindOfTokens::YTK_Equal},
    { ',', YKindOfTokens::YTK_Comma},
};

std::vector<YToken> Tokenizer(std::string_view input_file) {
    std::vector<YToken> tokens;
    unsigned int index = 0;

    for (index; index < input_file.size(); index++) {
        YToken currentToken;
        // Read line characters
        for (const auto& keyword : input_file) {
            // Create tokens
        }
    }

    return  tokens;
}


