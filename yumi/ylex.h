#pragma once

#define DEBUG_LEX_WITH_WITHSPACE 0 // 0 : False

#include <expected>
#include <string_view>
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
struct Position  {
    unsigned int line;
    unsigned int column;

    constexpr Position() : line(0), column(0) {}
    constexpr Position(const unsigned int l, const unsigned int c) : line(l), column(c) {}
};

class YToken {
    // __PRIVATE__
    YKindOfTokens selfKind;


    Position selfPos;

    public:
      YToken(const YKindOfTokens kind = YKindOfTokens::YTK_Unknown,
      const Position pos = Position()) : selfKind(kind), selfPos(pos) {};

      [[nodiscard]] auto GetKind() const -> YKindOfTokens {return selfKind; };
      [[nodiscard]] auto GetPos() const -> Position { return selfPos; }

      void SetPos(const unsigned int line, const unsigned int column) {
          selfPos.line = line;
          selfPos.column = column;
      }
      [[nodiscard]] std::string_view ToString() const {
          switch (selfKind) {
              case YKindOfTokens::YTK_Identifier:       return "identifier";
              case YKindOfTokens::YTK_LiteralInteger:   return "literalInteger";
              case YKindOfTokens::YTK_LiteralFloat:     return "literalFloat";
              case YKindOfTokens::YTK_LiteralChar:      return "literalChar";
              case YKindOfTokens::YTK_LiteralBool:      return "literalBool";
              case YKindOfTokens::YTK_LiteralArray:     return "literalArray";
              case YKindOfTokens::YTK_LiteralString:    return "literalString";
              case YKindOfTokens::YTK_LiteralStruct:    return "literalStruct";
              case YKindOfTokens::YTK_LeftParenthesis:  return "leftParenthesis";
              case YKindOfTokens::YTK_RightParenthesis: return "rightParenthesis";
              case YKindOfTokens::YTK_LeftBrace:        return "leftBrace";
              case YKindOfTokens::YTK_LeftBracket:      return "leftBracket";
              case YKindOfTokens::YTK_RightBracket:     return "rightBracket";
              case YKindOfTokens::YTK_RightBrace:       return "rightBrace";
              case YKindOfTokens::YTK_Quote:            return "quote";
              case YKindOfTokens::YTK_Equal:            return "equal";
              case YKindOfTokens::YTK_NotEqual:         return "not equal";
              case YKindOfTokens::YTK_GreaterThan:      return "greaterThan";
              case YKindOfTokens::YTK_Semicolon:        return "semicolon";
              case YKindOfTokens::YTK_Comma:            return "comma";
              case YKindOfTokens::YTK_Arrow:            return "arrow";
              case YKindOfTokens::YTK_Dot:              return "dot";
              case YKindOfTokens::YTK_Slash:            return "slash";
              case YKindOfTokens::YTK_Plus:             return "plus";
              case YKindOfTokens::YTK_Minus:            return "minus";
              case YKindOfTokens::YTK_Multiply:         return "multiply";
              case YKindOfTokens::YTK_Module:           return "module";
              case YKindOfTokens::YTK_Function:         return "function";
              case YKindOfTokens::YTK_I32:              return "i32";
              case YKindOfTokens::YTK_Final:            return "final";
              case YKindOfTokens::YTK_Var:              return "var";
              case YKindOfTokens::YTK_Return:           return "return";
              case YKindOfTokens::YTK_LessThan:         return "lessThan";
              case YKindOfTokens::YTK_Unknown:          return "Unknown";
              case YKindOfTokens::Eof:                  return "eof";
              default: std::unexpected("Stranger: This not possible");
          }
          return {};
      };
};

std::vector<YToken> Tokenizer(std::string_view input_file);
