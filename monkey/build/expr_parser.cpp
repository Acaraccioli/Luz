// A Bison parser, made by GNU Bison 3.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.



// First part of user prologue.
#line 20 "../expr_parser.y"

    #include <stdio.h>
    #include <iostream>
    #include "expr_ast.h"

    #include "parser.h"

    #define yylex(arg) lexer.getNextToken(arg)

    namespace Expr{
        void Parser::error(const std::string& msg){
            std::cerr << msg << "\n";
        }

   

    }

    extern int yylineno;


#line 62 "expr_parser.cpp"


#include "expr_tokens.h"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 9 "../expr_parser.y"
namespace Expr {
#line 143 "expr_parser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (ExprLexer& lexer_yyarg, YYNODESTATE& state_yyarg, ASTNode*& stmtList_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg),
      state (state_yyarg),
      stmtList (stmtList_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
  {
    switch (this->type_get ())
    {
      case 33: // stmt_list
      case 34: // stmt
      case 35: // if_stmt
      case 36: // else_block
      case 37: // expr
      case 38: // term
      case 39: // factor
        value.move< ASTNode* > (std::move (that.value));
        break;

      case 3: // NUMBER
        value.move< int > (std::move (that.value));
        break;

      case 4: // IDENT
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->type_get ())
    {
      case 33: // stmt_list
      case 34: // stmt
      case 35: // if_stmt
      case 36: // else_block
      case 37: // expr
      case 38: // term
      case 39: // factor
        value.copy< ASTNode* > (YY_MOVE (that.value));
        break;

      case 3: // NUMBER
        value.copy< int > (YY_MOVE (that.value));
        break;

      case 4: // IDENT
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 33: // stmt_list
      case 34: // stmt
      case 35: // if_stmt
      case 36: // else_block
      case 37: // expr
      case 38: // term
      case 39: // factor
        value.move< ASTNode* > (YY_MOVE (s.value));
        break;

      case 3: // NUMBER
        value.move< int > (YY_MOVE (s.value));
        break;

      case 4: // IDENT
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_type.
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  Parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  Parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_number_type
  Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.type_get ())
    {
      case 33: // stmt_list
      case 34: // stmt
      case 35: // if_stmt
      case 36: // else_block
      case 37: // expr
      case 38: // term
      case 39: // factor
        value.YY_MOVE_OR_COPY< ASTNode* > (YY_MOVE (that.value));
        break;

      case 3: // NUMBER
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 4: // IDENT
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.type_get ())
    {
      case 33: // stmt_list
      case 34: // stmt
      case 35: // if_stmt
      case 36: // else_block
      case 37: // expr
      case 38: // term
      case 39: // factor
        value.move< ASTNode* > (YY_MOVE (that.value));
        break;

      case 3: // NUMBER
        value.move< int > (YY_MOVE (that.value));
        break;

      case 4: // IDENT
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 33: // stmt_list
      case 34: // stmt
      case 35: // if_stmt
      case 36: // else_block
      case 37: // expr
      case 38: // term
      case 39: // factor
        value.move< ASTNode* > (that.value);
        break;

      case 3: // NUMBER
        value.move< int > (that.value);
        break;

      case 4: // IDENT
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 33: // stmt_list
      case 34: // stmt
      case 35: // if_stmt
      case 36: // else_block
      case 37: // expr
      case 38: // term
      case 39: // factor
        yylhs.value.emplace< ASTNode* > ();
        break;

      case 3: // NUMBER
        yylhs.value.emplace< int > ();
        break;

      case 4: // IDENT
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 58 "../expr_parser.y"
    { stmtList = yystack_[1].value.as < ASTNode* > (); }
#line 760 "expr_parser.cpp"
    break;

  case 5:
#line 65 "../expr_parser.y"
    { 
        yylhs.value.as < ASTNode* > () = state.blockStmtCreate(yystack_[2].value.as < ASTNode* > (),yystack_[0].value.as < ASTNode* > ());
    }
#line 768 "expr_parser.cpp"
    break;

  case 6:
#line 68 "../expr_parser.y"
    { yystack_[0].value.as < ASTNode* > ()->eval(); }
#line 774 "expr_parser.cpp"
    break;

  case 7:
#line 71 "../expr_parser.y"
    {yylhs.value.as < ASTNode* > () = state.assignCreate(yystack_[2].value.as < std::string > (),yystack_[0].value.as < ASTNode* > ()); }
#line 780 "expr_parser.cpp"
    break;

  case 8:
#line 72 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.printCreate(yystack_[0].value.as < ASTNode* > ()); }
#line 786 "expr_parser.cpp"
    break;

  case 9:
#line 73 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.whileStmtCreate(yystack_[6].value.as < ASTNode* > (),yystack_[2].value.as < ASTNode* > ()); }
#line 792 "expr_parser.cpp"
    break;

  case 10:
#line 74 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = yystack_[0].value.as < ASTNode* > (); }
#line 798 "expr_parser.cpp"
    break;

  case 11:
#line 77 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.ifStmtCreate(yystack_[6].value.as < ASTNode* > (),yystack_[3].value.as < ASTNode* > (),yystack_[1].value.as < ASTNode* > ()); }
#line 804 "expr_parser.cpp"
    break;

  case 12:
#line 80 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = yystack_[1].value.as < ASTNode* > (); }
#line 810 "expr_parser.cpp"
    break;

  case 13:
#line 83 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.equalCreate(yystack_[2].value.as < ASTNode* > (),yystack_[0].value.as < ASTNode* > ()); }
#line 816 "expr_parser.cpp"
    break;

  case 14:
#line 84 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.notequalCreate(yystack_[2].value.as < ASTNode* > (),yystack_[0].value.as < ASTNode* > ()); }
#line 822 "expr_parser.cpp"
    break;

  case 15:
#line 85 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.lessthanCreate(yystack_[2].value.as < ASTNode* > (),yystack_[0].value.as < ASTNode* > ()); }
#line 828 "expr_parser.cpp"
    break;

  case 16:
#line 86 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.greaterthanCreate(yystack_[2].value.as < ASTNode* > (),yystack_[0].value.as < ASTNode* > ()); }
#line 834 "expr_parser.cpp"
    break;

  case 17:
#line 87 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.lessthanorequalCreate(yystack_[2].value.as < ASTNode* > (),yystack_[0].value.as < ASTNode* > ()); }
#line 840 "expr_parser.cpp"
    break;

  case 18:
#line 88 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.greaterthanorequalCreate(yystack_[2].value.as < ASTNode* > (),yystack_[0].value.as < ASTNode* > ()); }
#line 846 "expr_parser.cpp"
    break;

  case 19:
#line 89 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.plusCreate(yystack_[2].value.as < ASTNode* > (),yystack_[0].value.as < ASTNode* > ()); }
#line 852 "expr_parser.cpp"
    break;

  case 20:
#line 90 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.minusCreate(yystack_[2].value.as < ASTNode* > (),yystack_[0].value.as < ASTNode* > ()); }
#line 858 "expr_parser.cpp"
    break;

  case 21:
#line 91 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = yystack_[0].value.as < ASTNode* > (); }
#line 864 "expr_parser.cpp"
    break;

  case 22:
#line 94 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.multiplyCreate(yystack_[2].value.as < ASTNode* > (),yystack_[0].value.as < ASTNode* > ()); }
#line 870 "expr_parser.cpp"
    break;

  case 23:
#line 95 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.divideCreate(yystack_[2].value.as < ASTNode* > (),yystack_[0].value.as < ASTNode* > ()); }
#line 876 "expr_parser.cpp"
    break;

  case 24:
#line 96 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.powerCreate(yystack_[2].value.as < ASTNode* > (),yystack_[0].value.as < ASTNode* > ()); }
#line 882 "expr_parser.cpp"
    break;

  case 25:
#line 97 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = yystack_[0].value.as < ASTNode* > (); }
#line 888 "expr_parser.cpp"
    break;

  case 26:
#line 100 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.intnumCreate(yystack_[0].value.as < int > ()); }
#line 894 "expr_parser.cpp"
    break;

  case 27:
#line 101 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = state.identifierCreate(yystack_[0].value.as < std::string > ()); }
#line 900 "expr_parser.cpp"
    break;

  case 28:
#line 102 "../expr_parser.y"
    { yylhs.value.as < ASTNode* > () = yystack_[1].value.as < ASTNode* > (); }
#line 906 "expr_parser.cpp"
    break;


#line 910 "expr_parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -20;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
      61,    -9,     3,     3,     3,     8,   -18,   -20,   -20,     3,
     -20,   -20,     3,    44,     7,   -20,    21,    -4,   -20,    61,
     -20,    44,    30,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,   -12,   -10,   -20,   -20,     7,     7,
       7,     7,     7,     7,     7,     7,   -20,   -20,   -20,    61,
      -5,     2,    61,    60,     9,    11,    14,    37,    61,   -20,
     -20,    13,   -20
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     4,     6,    10,     0,
      26,    27,     0,     8,    21,    25,     0,     0,     1,     3,
       2,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,    28,    19,    20,
      13,    14,    15,    16,    17,    18,    22,    23,    24,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
       9,     0,    12
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -20,   -20,   -20,    10,   -19,   -20,   -20,     0,    58,    -3
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     5,    20,     6,     7,     8,    56,    13,    14,    15
  };

  const unsigned char
  Parser::yytable_[] =
  {
      36,    23,    24,    16,    17,     9,    10,    11,    18,    21,
      50,    19,    22,    12,    31,    32,    33,    49,    25,    26,
      27,    28,    29,    30,    52,    35,    23,    24,    46,    47,
      48,    53,    59,    54,    36,    23,    24,    34,    57,    61,
      58,    37,    62,    25,    26,    27,    28,    29,    30,    23,
      24,     0,    25,    26,    27,    28,    29,    30,    60,    51,
       0,     0,     0,     0,     1,     1,    25,    26,    27,    28,
      29,    30,     2,     2,     0,     3,     3,    55,     0,     4,
       4,    38,    39,    40,    41,    42,    43,    44,    45
  };

  const signed char
  Parser::yycheck_[] =
  {
      19,     5,     6,     3,     4,    14,     3,     4,     0,     9,
      20,    29,    12,    10,     7,     8,     9,    29,    22,    23,
      24,    25,    26,    27,    29,    29,     5,     6,    31,    32,
      33,    29,    18,    52,    53,     5,     6,    16,    29,    58,
      29,    11,    29,    22,    23,    24,    25,    26,    27,     5,
       6,    -1,    22,    23,    24,    25,    26,    27,    21,    49,
      -1,    -1,    -1,    -1,     4,     4,    22,    23,    24,    25,
      26,    27,    12,    12,    -1,    15,    15,    17,    -1,    19,
      19,    23,    24,    25,    26,    27,    28,    29,    30
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     4,    12,    15,    19,    31,    33,    34,    35,    14,
       3,     4,    10,    37,    38,    39,    37,    37,     0,    29,
      32,    37,    37,     5,     6,    22,    23,    24,    25,    26,
      27,     7,     8,     9,    16,    29,    34,    11,    38,    38,
      38,    38,    38,    38,    38,    38,    39,    39,    39,    29,
      20,    33,    29,    29,    34,    17,    36,    29,    29,    18,
      21,    34,    29
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    30,    31,    32,    32,    33,    33,    34,    34,    34,
      34,    35,    36,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    38,    38,    38,    38,    39,    39,    39
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     0,     3,     1,     3,     2,     8,
       1,     8,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     3,     1,     1,     1,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "NUMBER", "IDENT", "SUMA", "RESTA",
  "MULT", "DIV", "POWER", "LEFTPAR", "RIGHTPAR", "ESCRIBA", "SEMICOLON",
  "ASIGNACION", "RW_SI", "RW_ENTONCES", "RW_SINO", "RW_FINSI",
  "RW_MIENTRAS", "RW_HAGA", "RW_FINMIENTRAS", "IGUALDAD", "NOIGUAL",
  "MENORQUE", "MAYORQUE", "MENORQUEOIGUAL", "MAYORQUEOIGUAL", "ERROR",
  "EOL", "$accept", "input", "eol", "stmt_list", "stmt", "if_stmt",
  "else_block", "expr", "term", "factor", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,    58,    58,    61,    62,    65,    68,    71,    72,    73,
      74,    77,    80,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    94,    95,    96,    97,   100,   101,   102
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29
    };
    const unsigned user_token_number_max_ = 284;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 9 "../expr_parser.y"
} // Expr
#line 1379 "expr_parser.cpp"

#line 106 "../expr_parser.y"

