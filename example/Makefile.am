AUTOMAKE_OPTIONS = foreign

# header files
noinst_HEADERS = 

EXTRA_DIST = demo.cc compile env.sh oe.cfg log.cfg 

exampledir = $(exec_prefix)/example
example_DATA = demo.cc compile env.sh oe.cfg log.cfg

install-data-hook:
	chmod u+x $(exampledir)/compile
