prefix = /usr/local
CXXFILES = main.c
CXXFLAGS = -Wall -o freedomboxalarm -lftdi1
INCLUDE = -I/usr/include/libftdi1/
LIBS = -L/usr/lib/arm-linux-gnueabihf/

all:
	$(CC) $(CXXFILES) $(INCLUDE) $(LIBS) $(CXXFLAGS) 

install:
	install freedomboxalarm $(DESTDIR)$(prefix)/bin
	install freedomboxalarm.1 $(DESTDIR)$(prefix)/share/man/man1

clean:
	rm -f freedomboxalarm
