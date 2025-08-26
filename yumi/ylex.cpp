#include "ylex.h"
#include <iostream>
#include <string>
#include <unordered_map>

static const std::unordered_map<std::string_view, YKindOfTokens> listOfKeywords = {
    { "fn", YKindOfTokens::YTK_Function},
    { "return", YKindOfTokens::YTK_Return},
    { "var", YKindOfTokens::YTK_Var},
    { "final", YKindOfTokens::YTK_Final},
    { "i32", YKindOfTokens::YTK_TI32},
    { "f32", YKindOfTokens::YTK_TF32},
    { "string", YKindOfTokens::YTK_TString},
    { "struct", YKindOfTokens::YTK_TStruct}
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
    {'!', YKindOfTokens::YTK_Not},
    { '<', YKindOfTokens::YTK_LessThan},
    { '>', YKindOfTokens::YTK_GreaterThan},
};

static const std::unordered_map<std::string, YKindOfTokens> listOfDoubleSymbols = {
    { "->", YKindOfTokens::YTK_Arrow},
    { "<=", YKindOfTokens::YTK_LessThanEqual},
    { ">=", YKindOfTokens::YTK_GreaterThanEqual},
    { "!=", YKindOfTokens::YTK_NotEqual},
    { "+=", YKindOfTokens::YTK_PlusEqual},
    { "-=", YKindOfTokens::YTK_MinusEqual},
    { "*=", YKindOfTokens::YTK_MultiplyEqual},
    { "/=", YKindOfTokens::YTK_DivEqual},
};

static bool isWhiteSpace(const char& c) {
    return std::isspace(static_cast<unsigned char>(c));
}

static bool isAlphaNumeric(const char& c) {
    return (c >= 'A' && c <= 'Z') || 
           (c >= 'a' && c <= 'z') || 
           (c >= '0' && c <= '9') ||
           c == '_';
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

        if (i + 1 < input_file.size()) {
            std::string two_chars{character, input_file[i+1]};
            if (listOfDoubleSymbols.contains(two_chars)) {
                tokens.emplace_back(listOfDoubleSymbols.at(two_chars), Position(line, column));
                i++; // consume the second char
                column += 2;
                continue; // <-
            }
        }


        // Lexer single symbol
        if (listOfSingleSymbols.contains(character)) {
            printf("character %c\n", character);
            tokens.emplace_back( listOfSingleSymbols.at(character), Position(line, column));
            column++;
            continue;
        }


        if (auto buffer = bufferChar(&i, input_file); !buffer.empty()) {
            i--; // compensar o for
            if (listOfKeywords.contains(buffer)) {
                tokens.emplace_back(listOfKeywords.at(buffer),buffer ,Position(line, column));
            } else {
                tokens.emplace_back(YKindOfTokens::YTK_Identifier,buffer, Position(line, column));
            }
            column += buffer.size();
            continue;
        }

    }

    tokens.emplace_back(YKindOfTokens::Eof, Position(line, column));

    return  tokens;
}


