#include <string.h>
#include <stdbool.h>

#include "picotest.h"
#include "petithttpescaper.h"

void ok_escape (const char *src, const char *expected);

void chars (void);
void mixed (void);

int main (void) {
  subtest("chars", chars);
  subtest("mixed", mixed);
  return done_testing();
}

void ok_escape (const char *src, const char *expected) {
  char *got = phe_escape_html(src, strlen(src));
  bool pass = strncmp(got, expected, strlen(expected)) == 0;
  ok(pass);
  free(got);
}

void chars (void) {
  ok_escape("&",  "&amp;");
  ok_escape(">",  "&gt;");
  ok_escape("<",  "&lt;");
  ok_escape("\"", "&quot;");
  ok_escape("'",  "&#39;");
  ok_escape("`",  "&#96;");
  ok_escape("{",  "&#123;");
  ok_escape("}",  "&#125;");
  ok_escape("no included html special chars", "no included html special chars");
}

void mixed (void) {
  ok_escape(
    "'`><script type=\"text/javascript\">{{alert(1)}}</script>&",
    "&#39;&#96;&gt;&lt;script type=&quot;text/javascript&quot;&gt;&#123;&#123;alert(1)&#125;&#125;&lt;/script&gt;&amp;"
  );
}

