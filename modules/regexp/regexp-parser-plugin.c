#include "cfg-parser.h"
#include "regexp-parser.h"
#include "plugin.h"
#include "plugin-types.h"

extern CfgParser regexp_parser_parser;

static Plugin regexp_parser_plugins[] = 
{
  {
    .type = LL_CONTEXT_PARSER,
    .name = "regexp-parser",
    .parser = &regexp_parser_parser,
  },
};

gboolean
regexp_parser_module_init(PluginContext *context, CfgArgs* args)
{
  plugin_register(context, regexp_parser_plugins, G_N_ELEMENTS(regexp_parser_plugins));
  return TRUE;
}

const ModuleInfo module_info = 
{
  .canonical_name = "regexp-parser",
  .version = SYSLOG_NG_VERSION,
  .description = "The regexp module provides regular expression parsing supports for syslog-ng.",
  .core_revision = SYSLOG_NG_SOURCE_REVISION,
  .plugins = regexp_parser_plugins,
  .plugins_len = G_N_ELEMENTS(regexp_parser_plugins),
};


