#include "builtin.h"
#include "parse-options.h"
#include "refs.h"

static char const * const pack_refs_usage[] = {
	N_("git pack-refs [options]"),
	NULL
};

int cmd_pack_refs(int argc, const char **argv, const char *prefix)
{
	unsigned int flags = PACK_REFS_PRUNE;
	struct strbuf err = STRBUF_INIT;
	struct option opts[] = {
		OPT_BIT(0, "all",   &flags, N_("pack everything"), PACK_REFS_ALL),
		OPT_BIT(0, "prune", &flags, N_("prune loose refs (default)"), PACK_REFS_PRUNE),
		OPT_END(),
	};
	if (parse_options(argc, argv, prefix, opts, pack_refs_usage, 0))
		usage_with_options(pack_refs_usage, opts);
	if (pack_refs(flags, &err)) {
		error("%s", err.buf);
		strbuf_release(&err);
		return -1;
	}
	return 0;
}
