CPP = gcc
OFLAG = -o $@
CPPFLAGS = -Wall
LIBFLAGS = `pkg-config --cflags --libs allegro` -lstdc++
.SUFFIXES : .o .cpp .c

.cpp.o:
	$(CPP) $(LIBFLAGS) $(CPPFLAGS) -c $<
.c.o:
	$(CPP) $(LIBFLAGS) $(CPPFLAGS) -c $<

TBD: main.o mappyal.o auxi.o level.o
	$(CPP) $(CPPFLAGS) $^ $(LIBFLAGS) $(OFLAG)

main.o:	main.cpp

auxi.o: auxi.cpp auxi.h

level.o: level.cpp level.h

mappyal.o: mappyal.c mappyal.h
	$(CPP) $(LIBFLAGS) $(CPPFLAGS) -w -c $<

clean:
	rm -f *.o TBD