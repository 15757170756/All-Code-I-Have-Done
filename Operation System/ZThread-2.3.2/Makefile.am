## Copyright (c) 2005, Eric Crahen
##
## Permission is hereby granted, free of charge, to any person obtaining a copy
## of this software and associated documentation files (the "Software"), to deal
## in the Software without restriction, including without limitation the rights
## to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
## copies of the Software, and to permit persons to whom the Software is furnished
## to do so, subject to the following conditions:
## 
## The above copyright notice and this permission notice shall be included in all
## copies or substantial portions of the Software.
## 
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
## WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
## CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## extra files
EXTRA_DIST = \
BUILDING \
LICENSE \
MIT.TXT \
depcomp


## install the config script
install-exec-hook:
	$(mkinstalldirs) $(bindir)
	$(INSTALL_PROGRAM) $(top_srcdir)/share/zthread-config $(bindir)

## install the config script & m4 macros
install-data-hook:
	$(mkinstalldirs) $(datadir)/aclocal
	$(INSTALL_DATA) $(top_srcdir)/share/zthread.m4 $(datadir)/aclocal
	$(INSTALL_DATA) $(top_srcdir)/share/pthread.m4 $(datadir)/aclocal
	mkdir -p $(DESTDIR)$(includedir)/zthread
	cp -pR $(top_srcdir)/include/zthread $(DESTDIR)$(includedir)/

## uninstall the config script & m4 macros
uninstall-local:
	-rm -rf $(datadir)/aclocal/pthread.m4
	-rm -rf $(datadir)/aclocal/zthread.m4

distclean-local: 
	-rm -rf $(top_srcdir)/$(PACKAGE)-$(VERSION).tar.gz
	-rm -rf $(top_srcdir)/autom4te.cache


## include the doc & share directories in the distribution
dist-hook: distclean-local
	cp -pR $(top_srcdir)/doc     	$(distdir)
	cp -pR $(top_srcdir)/share   	$(distdir)
	cp -pR $(top_srcdir)/include   	$(distdir)
	(find src -type d -name '[a-z,A-Z,0-9]*' -print0) | xargs -0 mkdir -p
	(find src -type f -name \*h -print0 -o -name \*cxx -print0) | xargs -0 tar cf - | tar Cx $(distdir) 
	find $(distdir)/doc     -type f -exec chmod --reference=README {} \;
	find $(distdir)/include -type f -exec chmod --reference=README {} \;
	find $(distdir)/src     -type f -exec chmod --reference=README {} \;
	find $(distdir)/        -type d -exec chmod a+rx {} \;
	find $(distdir)/ -type f -path \*CVS\* -print0 | xargs -0 rm -rf
	find $(distdir)/ -type f -name \*~ -print0 | xargs -0 rm -rf
	find $(distdir)/ -type f -name \*.bak -print0 | xargs -0 rm -rf
	find $(distdir)/ -type f -name \*.log -print0 | xargs -0 rm -rf
	find $(distdir)/ -type f -name \*.obj -print0 | xargs -0 rm -rf

## RPM from the distribution rule
rpm: dist
	rpm -ta $(PACKAGE)-$(VERSION).tar.gz
	mv -f /usr/src/redhat/SRPMS/$(PACKAGE)-$(VERSION)-*.rpm .
	mv -f /usr/src/redhat/RPMS/*/$(PACKAGE)-$(VERSION)-*.rpm .
	mv -f /usr/src/redhat/RPMS/*/$(PACKAGE)-devel-$(VERSION)-*.rpm .
	mv -f /usr/src/redhat/RPMS/*/$(PACKAGE)-doc-$(VERSION)-*.rpm .

## Build the documentation
docs: 
	if test x$(DOXYGEN) != x; then\
	-rm -f $(top_srcdir)/doc/html/*; \
	$(DOXYGEN) $(top_srcdir)/doc/zthread.doxygen; \
	cp $(top_srcdir)/doc/documentation.html $(top_srcdir)/doc/html/index.html; \
	cp $(top_srcdir)/doc/zthread.css $(top_srcdir)/doc/html/zthread.css; \
	cp $(top_srcdir)/doc/bugs.js $(top_srcdir)/doc/html/bugs.js; \
	else \
	echo; \
	echo "This configuration requires Doxygen, by Dimitri van Heesch."; \
	echo "Visit www.stack.nl/~dimitri/doxygen/ for information about how to"; \
	echo "obtain a copy. If you already have Doxygen and it was not detected"; \
	echo "you should try the --with-doxygen option."; \
	echo; \
	fi; 


