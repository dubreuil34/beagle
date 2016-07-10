# ----------------------------------------------------------------------
# Fichier d'exemple du livre "Solutions Temps-Reel sous Linux"
# (C) 2012 - Christophe BLAESS
# http://christophe.blaess.fr
# ----------------------------------------------------------------------

APPLICATIONS = test

#chemin de xeno-config dans le paquet libxenomai-dev sur la beagle
XENOCONFIG=/usr/bin/xeno-config

CC=$(shell      $(XENOCONFIG) --cc)
MY_CFLAGS=-g
CFLAGS=$(shell  $(XENOCONFIG) --skin=native --cflags)  $(MY_CFLAGS)
LDFLAGS=$(shell $(XENOCONFIG) --skin=native --ldflags) $(MY_LDFLAGS)
LIBDIR=$(shell  $(XENOCONFIG) --skin=native --libdir)  $(MY_LIBDIR)
LDFLAGS+=-lnative 
LDLIBS=-lnative -lxenomai 

all:: $(APPLICATIONS)

test: test.o beagle.o
	$(CC) -o test test.o beagle.o $(LDFLAGS) $(LDLIBS)

beagle.o: lib/beagle.c
	$(CC) -o beagle.o -c lib/beagle.c $(CFLAGS)

test.o: test.c
	$(CC) -o test.o -c test.c $(CFLAGS)

clean::
	$(RM) -f $(APPLICATIONS) *.o *~
