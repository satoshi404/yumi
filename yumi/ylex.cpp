#include "ylex.h"
#include <iostream>
#include <unordered_map>

static const std::unordered_map<std::string_view, YKindOfTokens> listOfKeywords = {
    { "fn", YKindOfTokens::YTK_Function},
    { "return", YKindOfTokens::YTK_Return},
    { "var", YKindOfTokens::YTK_Var},
    { "final", YKindOfTokens::YTK_Final},
    { "i32", YKindOfTokens::YTK_I32},
};

static const std::unordered_map<char, YKindOfTokens> listOfSingleSymbols {
    { ';', YKindOfTokens::YTK_Semicolon},
    { '{', YKindOfTokens::YTK_LeftBrace},
    { '}', YKindOfTokens::YTK_RightBrace },
    { '(', YKindOfTokens::YTK_LeftParenthesis},
    { ')', YKindOfTokens::YTK_RightParenthesis},
    { '*', YKindOfTokens::YTK_Multiply },
    { '=', YKindOfTokens::YTK_Equal},
    { ',', YKindOfTokens::YTK_Comma},
};

static const std::unordered_map<std::string, YKindOfTokens> listOfDoubleSymbols = {
    { "->", YKindOfTokens::YTK_Arrow},
    { "<=", YKindOfTokens::YTK_LessThanEqual}
};

static bool isWhiteSpace(const char& c) {
    return c == ' ' || c == '\t';
}

std::vector<YToken> Tokenizer(std::string_view input_file) {
    std::vector<YToken> tokens;
    unsigned int line = 1;
    unsigned int column = 1;
    for (char character : input_file) {
        // Read line characters
        if (character == '\n') {
            line++;
            column = 1;
            continue;
        }

        #if !TOKENIZER_WITH_WITHSPACE
        if (isWhiteSpace(character)) { column++; continue; }
        #endif

        // Lexer single symbol
        if (listOfSingleSymbols.contains(character)) {
            tokens.emplace_back( listOfSingleSymbols.at(character), Position(line, column));
        }
        column++;
    }

    return  tokens;
}


