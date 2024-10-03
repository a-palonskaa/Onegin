SUBDIR_COMMON = common
SUBDIRS_HEADER_SORT = common header_sort
SUBDIRS_ONEGIN = common onegin
SUBDIRS_UTF8 = common utf8
SUBDIRS = common header_sort onegin utf8

all: osort hsort rus lib

hsort:
	@for dir in $(SUBDIRS_HEADER_SORT); do \
		$(MAKE) -C $$dir all;              \
	done

osort:
	@for dir in $(SUBDIRS_ONEGIN); do \
		$(MAKE) -C $$dir all;         \
	done

rus:
	@for dir in $(SUBDIRS_UTF8); do \
		$(MAKE) -C $$dir all;       \
	done

lib:
	@$(MAKE) -C $(SUBDIR_COMMON) all;

clean:
	@for dir in $(SUBDIRS); do   \
		$(MAKE) -C $$dir clean; \
	done
