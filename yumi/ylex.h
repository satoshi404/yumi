#ifndef YUMI_YLEX_H
#define YUMI_YLEX_H

#include <string_view>
#include <iostream>
#include <vector>

enum class YKindOfTokens {
    // Literals and identifier
    YTK_Identifier,
    YTK_LiteralInteger,
    YTK_LiteralFloat,
    YTK_LiteralString,
    YTK_LiteralChar,
    YTK_LiteralBool,
    YTK_LiteralArray,
    YTK_LiteralStruct,
    // Symbols
    YTK_LeftParenthesis,
    YTK_RightParenthesis,
    YTK_LeftBracket,
    YTK_RightBracket,
    YTK_LeftBrace,
    YTK_RightBrace,
    YTK_Quote,
    YTK_Equal,
    YTK_NotEqual,
    YTK_GreaterThan,
    YTK_LessThan,
    YTK_GreaterThanEqual,
    YTK_LessThanEqual,
    YTK_Semicolon,
    YTK_Comma,
    YTK_Arrow,
    YTK_Dot,
    YTK_Slash,
    YTK_Plus,
    YTK_Minus,
    YTK_Multiply,
    YTK_Module,

    // Keywords
    YTK_Function,
    YTK_I32,
    YTK_Final,
    YTK_Var,
    YTK_Return,

    // ...
    YTK_Unknown,
    Eof,
};

class YToken {
    // __PRIVATE__
    YKindOfTokens selfKind;
    struct selfPos { unsigned int line = 0; unsigned int column = 0; };
    public:
      YToken(const YKindOfTokens kind = YKindOfTokens::YTK_Unknown) : selfKind(kind), selfPos(nullptr) {};
      [[nodiscard]]
      auto GetKind() const -> YKindOfTokens;
      void SetPos(unsigned int line, unsigned int column) {

      }


};

std::vector<YToken> Tokenizer(std::string_view input_file);

#endif // YUMI_YLEX_H
