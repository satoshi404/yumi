#include "ylex.h"
#include <iostream>
#include <string>
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

static bool isAlphaNumeric(const char& c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static std::string bufferChar(size_t* i, const std::string_view input_file) {
    std::string buffer;
    while (*i < input_file.size() && isAlphaNumeric(input_file[*i])) {
        buffer += input_file[(*i)++];
    }
    return buffer;
}


std::vector<YToken> Tokenizer(std::string_view input_file) {
    std::vector<YToken> tokens;
    unsigned int line = 1;
    unsigned int column = 1;
    for (size_t i = 0; i < input_file.size(); ++i) {
        char character = input_file[i];

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

        if (i + 1 < input_file.size()) {
            if (auto two_chars = std::string{character, input_file[i+1]}; listOfDoubleSymbols.contains(two_chars)) {
                tokens.emplace_back(listOfDoubleSymbols.at(two_chars), Position(line, column));
                i++; // consume the second char
                column += 2;
                continue;
            }
        }

        if (auto buffer = bufferChar( &i, input_file); !buffer.empty()) {
            if (listOfKeywords.contains(buffer)) {
                tokens.emplace_back(listOfKeywords.at(buffer), Position(line, column));
            } else {
                tokens.emplace_back(YKindOfTokens::YTK_Identifier, Position(line, column));
            }
            column += buffer.size();
            continue;
        }

        column++;
    }

    return  tokens;
}


