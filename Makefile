PROJS = include iter math poly prob range root

.PHONY: all $(PROJS)

all: $(PROJS)

$(PROJS):
	cd $@ && $(MAKE) $@
