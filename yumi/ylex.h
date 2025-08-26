#pragma once

#define DEBUG_LEX_WITH_WITHSPACE 0 // 0 : False

#include <expected>
#include <string_view>
#include <string>
#include <utility>
#include <vector>

enum class YKindOfTokens {
    // Literals and identifier
    YTK_Identifier,
    YTK_LiteralInteger,
    YTK_LiteralFloat,
    YTK_LiteralString,
    YTK_LiteralChar,
    YTK_LiteralTrue,
    YTK_LiteralFalse,
    YTK_LiteralArray,
    // Symbols
    YTK_LeftParenthesis,
    YTK_RightParenthesis,
    YTK_LeftBracket,
    YTK_RightBracket,
    YTK_LeftBrace,
    YTK_RightBrace,
    YTK_Equal,
    YTK_NotEqual,
    YTK_Not,
    YTK_GreaterThan,
    YTK_LessThan,
    YTK_GreaterThanEqual,
    YTK_LessThanEqual,
    YTK_PlusEqual,
    YTK_MinusEqual,
    YTK_MultiplyEqual,
    YTK_DivEqual,
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
    YTK_TI32,
    YTK_TString,
    YTK_TBool,
    YTK_TChar,
    YTK_TF32,
    YTK_TArray,
    YTK_TStruct,
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
    std::string id;

    Position selfPos;

    public:
      YToken(
          const YKindOfTokens kind = YKindOfTokens::YTK_Unknown,
          const Position pos = Position())
            : selfKind(kind), selfPos(pos) {};

      YToken(
          const YKindOfTokens kind = YKindOfTokens::YTK_Unknown,
          std::string identifier = {},
          const Position pos = Position())
            : selfKind(kind), id(std::move(identifier)),selfPos(pos) {};


      [[nodiscard]] auto GetKind() const -> YKindOfTokens {return selfKind; };
      [[nodiscard]] auto GetPos() const -> Position { return selfPos; }
      [[nodiscard]] auto GetIdentifier() const -> std::string_view { return {id.data(), id.size()}; };

      void SetPos(const unsigned int line, const unsigned int column) {
          selfPos.line = line;
          selfPos.column = column;
      }
      [[nodiscard]] std::string_view KindToString() const {
          switch (selfKind) {
              // ==========================================================================
              case YKindOfTokens::YTK_Identifier:       return " Identifier";
              case YKindOfTokens::YTK_LiteralInteger:   return " (Literal) Integer";
              case YKindOfTokens::YTK_LiteralFloat:     return " (Literal) Float";
              case YKindOfTokens::YTK_LiteralTrue:      return " (Literal) True";
              case YKindOfTokens::YTK_LiteralFalse:     return " (Literal) False";
              case YKindOfTokens::YTK_LiteralChar:      return " (Literal) Char";
              case YKindOfTokens::YTK_LiteralArray:     return " (Literal) Array";
              case YKindOfTokens::YTK_LiteralString:    return " (Literal) String";
              // ===========================================================================
              case YKindOfTokens::YTK_LeftParenthesis:  return " (Symbol '(') LeftParenthesis";
              case YKindOfTokens::YTK_RightParenthesis: return " (Symbol ')') RightParenthesis";
              case YKindOfTokens::YTK_LeftBrace:        return " (Symbol '{') LeftBrace";
              case YKindOfTokens::YTK_RightBrace:       return " (Symbol '}') RightBrace";
              case YKindOfTokens::YTK_LeftBracket:      return " (Symbol '[') LeftBracket";
              case YKindOfTokens::YTK_RightBracket:     return " (Symbol ']') RightBracket";
              //case YKindOfTokens::YTK_Quote:            return "quote";
              case YKindOfTokens::YTK_Equal:            return " (Symbol '=') Equal";
              case YKindOfTokens::YTK_NotEqual:         return " (Symbol '!=') NotEqual";
              case YKindOfTokens::YTK_PlusEqual:        return " (Symbol '+=') PlusEqual";
              case YKindOfTokens::YTK_MinusEqual:       return " (Symbol '-=') MinusEqual";
              case YKindOfTokens::YTK_MultiplyEqual:    return " (Symbol '*=') MultiplyEqual";
              case YKindOfTokens::YTK_DivEqual:         return " (Symbol '/=') DivideEqual";
              case YKindOfTokens::YTK_Not:              return " (Symbol '!') Not";
              case YKindOfTokens::YTK_GreaterThan:      return " (Symbol '>') GreaterThan";
              case YKindOfTokens::YTK_LessThan:         return " (Symbol '<') LessThan";
              case YKindOfTokens::YTK_LessThanEqual:    return " (Symbol '<=') LessThanEqual";
              case YKindOfTokens::YTK_GreaterThanEqual: return " (Symbol '>=') GreaterThanEqual";
              case YKindOfTokens::YTK_Semicolon:        return " (Symbol ';') Semicolon";
              case YKindOfTokens::YTK_Comma:            return " (Symbol ',') Comma";
              case YKindOfTokens::YTK_Arrow:            return " (Symbol '->') Arrow";
              case YKindOfTokens::YTK_Dot:              return " (Symbol '.') Dot";
              case YKindOfTokens::YTK_Slash:            return " (Symbol '/') Slash";
              case YKindOfTokens::YTK_Plus:             return " (Symbol '+') Plus";
              case YKindOfTokens::YTK_Minus:            return " (Symbol '-') Minus";
              case YKindOfTokens::YTK_Multiply:         return " (Symbol '*') Multiply";
              case YKindOfTokens::YTK_Module:           return " (Symbol '%') Module";
              // ===========================================================================
              case YKindOfTokens::YTK_Function:         return " (Keyword) Function";
              case YKindOfTokens::YTK_TStruct:          return " (Type) Struct";
              case YKindOfTokens::YTK_TI32:             return " (Type) Integer";
              case YKindOfTokens::YTK_TString:          return " (Type) String";
              case YKindOfTokens::YTK_TF32:             return " (Type) Float";
              case YKindOfTokens::YTK_TBool:            return " (Type) Boolean";
              case YKindOfTokens::YTK_TChar:            return " (Type) Char";
              case YKindOfTokens::YTK_Final:            return " (Keyword) Final";
              case YKindOfTokens::YTK_Var:              return " (Keyword) Var";
              case YKindOfTokens::YTK_Return:           return " (Keyword) Return";
              case YKindOfTokens::YTK_Unknown:          return " (Unknown_";
              case YKindOfTokens::Eof:                  return "-- ( EOF ) ---";
              default: std::unexpected("Stranger: This not possible");
          }
          return {};
      };
};

std::vector<YToken> Tokenizer(std::string_view input_file);
