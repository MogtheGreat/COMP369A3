CPP = gcc
OFLAG = -o $@
CPPFLAGS = -Wall
LIBFLAGS = `pkg-config --cflags --libs allegro` -lstdc++
.SUFFIXES : .o .cpp .c

.cpp.o:
	$(CPP) $(LIBFLAGS) $(CPPFLAGS) -c $<
.c.o:
	$(CPP) $(LIBFLAGS) $(CPPFLAGS) -c $<

TBD:	main.o sprites.o load.o mappyal.o level.o movement.o weapons.o enemy.o
	$(CPP) $(CPPFLAGS) $^ $(LIBFLAGS) $(OFLAG)

main.o:	main.cpp

sprites.o: sprites.cpp sprites.h

load.o: load.cpp load.h

movement.o: movement.cpp movement.h

mappyal.o: mappyal.c mappyal.h
	$(CPP) $(LIBFLAGS) $(CPPFLAGS) -w -c $<

level.o: level.cpp level.h

weapons.o: weapons.cpp weapons.h

enemy.o: enemy.cpp enemy.h

clean:
	rm -f *.o TBD