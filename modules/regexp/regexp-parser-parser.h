#ifndef REGEXP_PARSER_PARSER_H_INCLUDED
#define REGEXP_PARSER_PARSER_H_INCLUDED

#include "cfg-parser.h"
#include "parser/parser-expr-parser.h"

extern CfgParser regexp_parser_parser;

CFG_PARSER_DECLARE_LEXER_BINDING(regexp_parser_, REGEXP_PARSER_, LogParser **)

#endif