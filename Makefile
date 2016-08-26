################################################################
## Fia-Net C++ commons 
## (c) Fia-Net 2008 - 2016
################################################################

DIRS = src

TARGETS = $(DIRS)

all:
	@for dir in $(DIRS); do cd $$dir ; $(MAKE) all || exit $? ; cd .. ; done

install:
	@for dir in $(DIRS); do cd $$dir ; $(MAKE) install || exit $? ; cd .. ; done

tests: all
	@for dir in $(DIRS); do cd $$dir ; $(MAKE) tests || exit $? ; cd .. ; done

clean:
	@for dir in $(DIRS); do cd $$dir ; $(MAKE) clean ; cd .. ; done

distclean:
	@for dir in $(DIRS); do cd $$dir ; $(MAKE) distclean ; cd .. ; done

