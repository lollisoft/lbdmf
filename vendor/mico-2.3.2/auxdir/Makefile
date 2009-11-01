#
# MICO --- a free CORBA implementation
# Copyright (C) 1997 Kay Roemer & Arno Puder
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
# Send comments and/or bug reports to:
#                mico@informatik.uni-frankfurt.de
#

include ../MakeVars

LDLIBS    = -lmico$(VERSION) $(CONFLIBS)
LDFLAGS  := -L../orb $(LDFLAGS)
CXXFLAGS := -I. -I../include $(CXXFLAGS) $(X_CFLAGS)

AUX_SRCS=dynany_impl.cc
STATIC_AUX_OBJS = $(AUX_SRCS:.cc=.o)
SHARED_AUX_OBJS = $(AUX_SRCS:.cc=.pic.o)

STATIC_LIBS = libmicoaux$(VERSION).a

ifeq ($(HAVE_X11), yes)
STATIC_LIBS := $(STATIC_LIBS) libmicox$(VERSION).a
X11_SRCS := x11.cc
STATIC_X11_OBJS = $(X11_SRCS:.cc=.o)
SHARED_X11_OBJS = $(X11_SRCS:.cc=.pic.o)
endif

ifeq ($(HAVE_QT), yes)
STATIC_LIBS := $(STATIC_LIBS) libmicoqt$(VERSION).a
QT_SRCS := qtmico.cc
STATIC_QT_OBJS = $(QT_SRCS:.cc=.o)
SHARED_QT_OBJS = $(QT_SRCS:.cc=.pic.o)
endif

ifeq ($(HAVE_GTK), yes)
STATIC_LIBS := $(STATIC_LIBS) libmicogtk$(VERSION).a
CXXFLAGS := $(CXXFLAGS) $(GTK_CFLAGS)
GTK_SRCS := gtkmico.cc
STATIC_GTK_OBJS = $(GTK_SRCS:.cc=.o)
SHARED_GTK_OBJS = $(GTK_SRCS:.cc=.pic.o)
endif

ifeq ($(HAVE_TCL), yes)
STATIC_LIBS := $(STATIC_LIBS) libmicotcl$(VERSION).a
TCL_SRCS := tclmico.cc
STATIC_TCL_OBJS = $(TCL_SRCS:.cc=.o)
SHARED_TCL_OBJS = $(TCL_SRCS:.cc=.pic.o)
endif

SHARED_LIBS = $(STATIC_LIBS:.a=.$(SOEXT))

# normal rules

all: lib prg

lib: .depend

ifeq ($(HAVE_SHARED), yes)
ifeq ($(HAVE_STATIC), yes)
prg: .depend $(STATIC_LIBS) $(SHARED_LIBS)
else
prg: .depend $(SHARED_LIBS)
endif
else
prg: .depend $(STATIC_LIBS)
endif

qtmico.moc: ../include/mico/qtmico.h
	$(MOC) $< -o $@

dynany_impl.o: dynany_impl.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(EHFLAGS) -c $< -o $@

dynany_impl.pic.o: dynany_impl.cc
	$(CXX) $(PICFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(EHFLAGS) -c $< -o $@

qtmico.cc: qtmico.moc


# shared

libmicoaux$(VERSION).$(SOEXT): $(SHARED_AUX_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(SHARED_AUX_OBJS) $(LDFLAGS) $(LDLIBS)
endif
	rm -f $@
	$(LDSO) -o libmicoaux$(VERSION) $(SHARED_AUX_OBJS) \
		-L../libs -lmico$(VERSION)
	$(IDIRCMD) ../libs
	cd ../libs; rm -f $@; ln -f -s ../auxdir/$@ .

libmicox$(VERSION).$(SOEXT): $(SHARED_X11_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(SHARED_X11_OBJS) $(LDFLAGS) $(LDLIBS)
endif
	rm -f $@
	$(LDSO) -o libmicox$(VERSION) $(SHARED_X11_OBJS) \
		$(PURE_LDFLAGS) -lXt -lX11 -L../libs -lmico$(VERSION)
	$(IDIRCMD) ../libs
	cd ../libs; rm -f $@; ln -f -s ../auxdir/$@ .

libmicoqt$(VERSION).$(SOEXT): $(SHARED_QT_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(SHARED_QT_OBJS) $(LDFLAGS) $(LDLIBS)
endif
	rm -f $@
	$(LDSO) -o libmicoqt$(VERSION) $(SHARED_QT_OBJS) \
		$(PURE_LDFLAGS) -lqt -lX11 -L../libs -lmico$(VERSION)
	$(IDIRCMD) ../libs
	cd ../libs; rm -f $@; ln -f -s ../auxdir/$@ .

libmicogtk$(VERSION).$(SOEXT): $(SHARED_GTK_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(SHARED_GTK_OBJS) $(LDFLAGS) $(LDLIBS)
endif
	rm -f $@
	$(LDSO) -o libmicogtk$(VERSION) $(SHARED_GTK_OBJS) \
		$(PURE_LDFLAGS) $(GTK_LIBS) -L../libs -lmico$(VERSION)
	$(IDIRCMD) ../libs
	cd ../libs; rm -f $@; ln -f -s ../auxdir/$@ .

libmicotcl$(VERSION).$(SOEXT): $(SHARED_TCL_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(SHARED_TCL_OBJS) $(LDFLAGS) $(LDLIBS)
endif
	rm -f $@
	$(LDSO) -o libmicotcl$(VERSION) $(SHARED_TCL_OBJS) \
		$(PURE_LDFLAGS) $(TCL_LIBS) -L../libs -lmico$(VERSION)
	$(IDIRCMD) ../libs
	cd ../libs; rm -f $@; ln -f -s ../auxdir/$@ .


# static

libmicoaux$(VERSION).a: $(STATIC_AUX_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(STATIC_AUX_OBJS) $(LDFLAGS) $(LDLIBS)
endif
	$(AR) $(ARFLAGS) $@ $(STATIC_AUX_OBJS)
	$(RANLIB) $@
	$(IDIRCMD) ../libs
	cd ../libs; rm -f $@; ln -f -s ../auxdir/$@ .

libmicox$(VERSION).a: $(STATIC_X11_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(STATIC_X11_OBJS) $(LDFLAGS) $(LDLIBS)
endif
	$(AR) $(ARFLAGS) $@ $(STATIC_X11_OBJS)
	$(RANLIB) $@
	$(IDIRCMD) ../libs
	cd ../libs; rm -f $@; ln -f -s ../auxdir/$@ .

libmicoqt$(VERSION).a: $(STATIC_QT_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(STATIC_QT_OBJS) $(LDFLAGS) $(LDLIBS)
endif
	$(AR) $(ARFLAGS) $@ $(STATIC_QT_OBJS)
	$(RANLIB) $@
	$(IDIRCMD) ../libs
	cd ../libs; rm -f $@; ln -f -s ../auxdir/$@ .

libmicogtk$(VERSION).a: $(STATIC_GTK_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(STATIC_GTK_OBJS) $(LDFLAGS) $(LDLIBS)
endif
	$(AR) $(ARFLAGS) $@ $(STATIC_GTK_OBJS)
	$(RANLIB) $@
	$(IDIRCMD) ../libs
	cd ../libs; rm -f $@; ln -f -s ../auxdir/$@ .

libmicotcl$(VERSION).a: $(STATIC_TCL_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(STATIC_TCL_OBJS) $(LDFLAGS) $(LDLIBS)
endif
	$(AR) $(ARFLAGS) $@ $(STATIC_TCL_OBJS)
	$(RANLIB) $@
	$(IDIRCMD) ../libs
	cd ../libs; rm -f $@; ln -f -s ../auxdir/$@ .


# cleaning

clean:
	-$(RM) *.o *.a *~ *.rpo *.objid *.moc *.$(SOEXT)
	-$(RM) .depend TAGS core nohup.out
	-$(RM) *.orig

install:
	$(IDIRCMD) $(INSTDIR)/lib
ifeq ($(HAVE_SHARED), yes)
	@for i in $(SHARED_LIBS); do $(ILIBCMD) $$i $(INSTDIR)/lib; done
endif
ifeq ($(HAVE_STATIC), yes)
	@for i in $(STATIC_LIBS); do $(ILIBCMD) $$i $(INSTDIR)/lib; done
endif

install-cd: install

ifeq (.depend, $(wildcard .depend))
include .depend
endif

.depend :
	echo '# Module dependencies' > .depend
	$(MKDEPEND) $(CXXFLAGS) *.cc >> .depend
