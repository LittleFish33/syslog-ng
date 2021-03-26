#ifndef REGEXP_PARSER_H_INCLUDED
#define REGEXP_PARSER_H_INCLUDED

#include "parser/parser-expr.h"
#include "logmatcher.h"

LogParser* regexp_parser_new(GlobalConfig *cfg);
void regexp_parser_set_prefix(LogParser *s, const gchar *prefix);
void regexp_parser_set_pattern(LogParser *s, const gchar *prefix);

#endif