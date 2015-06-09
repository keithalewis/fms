PROJS = include iter math poly prob root

.PHONY: all $(PROJS)

all: $(PROJS)

$(PROJS):
	cd $@ && $(MAKE) $@ && $@
