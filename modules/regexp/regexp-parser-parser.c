#include "regexp-parser.h"
#include "cfg-parser.h"
#include "regexp-parser-grammar.h"

extern int regexp_parser_debug;

int regexp_parser_parse(CfgLexer *lexer, LogParser **instance, gpointer arg);

static CfgLexerKeyword regexp_parser_keywords[] = 
{
    {"regexp_parser", KW_REGEXP_PARSER},
    {"prefix", KW_PREFIX},
    {"pattern", KW_PATTERN},
    {NULL}
};

CfgParser regexp_parser_parser = 
{
#if SYSLOG_NG_ENABLE_DEBUG
  .debug_flag = &regexp_parser_debug,
#endif
  .name = "regexp-parser",
  .keywords = regexp_parser_keywords,
  .parse = (gint (*)(CfgLexer *, gpointer *, gpointer)) regexp_parser_parse,
  .cleanup = (void (*)(gpointer)) log_pipe_unref,
};

CFG_PARSER_IMPLEMENT_LEXER_BINDING(regexp_parser_, REGEXP_PARSER_, LogParser **)
