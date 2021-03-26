#include "regexp-parser.h"
#include "parser/parser-expr.h"
#include "scratch-buffers.h"

#include <string.h>
#include <stdio.h>

typedef struct _REGEXParser
{
  LogParser super;
  gchar *prefix;
  gchar *pattern;
  gint prefix_len;
  NVHandle value_handle;
  LogMatcherOptions matcher_options;
  LogMatcher *matcher;
} REGEXParser;

void
regexp_parser_set_prefix(LogParser *s, const gchar *prefix)
{
  REGEXParser *self = (REGEXParser *) s;

  g_free(self->prefix);
  if (prefix)
    {
      self->prefix = g_strdup(prefix);
      self->prefix_len = strlen(prefix);
    }
  else
    {
      self->prefix = NULL;
      self->prefix_len = 0;
    }
}

void
regexp_parser_set_pattern(LogParser *s, const gchar *pattern)
{
  REGEXParser *self = (REGEXParser *) s;

  g_free(self->pattern);
  if (pattern)
    {
      self->pattern = g_strdup(pattern);
    }
  else
    {
      self->pattern = NULL;
    }
  GError *error = NULL;
  log_matcher_compile(self->matcher, self->pattern, &error);
}

static const gchar *
_get_formatted_key_with_prefix(REGEXParser *self, const gchar *key, GString *formatted_key)
{
  if (formatted_key->len > 0)
    g_string_truncate(formatted_key, self->prefix_len);
  else
    g_string_assign(formatted_key, self->prefix);
  g_string_append(formatted_key, key);
  return formatted_key->str;
}

static const gchar *
_get_formatted_key(REGEXParser *self, const gchar *key, GString *formatted_key)
{
  if (!self->prefix)
    return key;
  return _get_formatted_key_with_prefix(self, key, formatted_key);
}

static gboolean
regexp_parser_process(LogParser *s, LogMessage **pmsg, const LogPathOptions *path_options, const gchar *input,
                      gsize input_len)
{
  REGEXParser *self = (REGEXParser *) s;
  GString *formatted_key = scratch_buffers_alloc();

  log_msg_make_writable(pmsg, path_options);
  msg_trace("regexp-parser message processing started",
            evt_tag_str ("input", input),
            evt_tag_str ("prefix", self->prefix),
            evt_tag_str ("pattern", self->pattern),
            evt_tag_printf("msg", "%p", *pmsg));
  
  self->matcher->prefix = self->prefix;
  log_matcher_match(self->matcher, *pmsg, self->value_handle, input, input_len);

  return TRUE;
  
}

static void
regexp_parser_free(LogPipe *s)
{
  REGEXParser *self = (REGEXParser *) s;

  g_free(self->prefix);
  g_free(self->pattern);
  log_parser_free_method(s);

  log_matcher_unref(self->matcher);
  log_matcher_options_destroy(&self->matcher_options);
}

static LogPipe *
regexp_parser_clone(LogPipe *s)
{
  REGEXParser *self = (REGEXParser *)s;
  LogParser *cloned;

  cloned = regexp_parser_new(s->cfg);
  regexp_parser_set_prefix(&cloned->super, self->prefix);
  regexp_parser_set_pattern(&cloned->super, self->pattern);
  log_parser_set_template(cloned, log_template_ref(self->super.template));

  return &cloned->super;
}


LogParser* 
regexp_parser_new(GlobalConfig *cfg)
{
  REGEXParser *self = g_new0(REGEXParser, 1);

  log_parser_init_instance(&self->super, cfg);
  self->super.super.free_fn = regexp_parser_free;
  self->super.super.clone = regexp_parser_clone;
  self->super.process = regexp_parser_process;
  log_matcher_options_defaults(&self->matcher_options);
  self->value_handle = LM_V_SOURCE;
  log_matcher_options_init(&self->matcher_options);
  self->matcher_options.flags |= LMF_STORE_MATCHES;
  self->matcher = log_matcher_new(&self->matcher_options);

  return &self->super;
}
