CC=g++
BOOST=-lboost_unit_test_framework
LINKER=-lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
INC=-I/usr/local/include/
LIB=-L/usr/local/lib/
FLAGS=-Wall -ansi -pedantic --std=c++11
GUITAR_BIN=GuitarHero
AUTO_BIN=AutoHero

all: ps3c

ps3a: ring_buffer_class.o ring_buffer_test.o
	$(CC) ring_buffer_test.o ring_buffer_class.o $(LIB) $(BOOST) -o ps3a

ps3b: ring_buffer_class.o ring_buffer_itr_test.o
	$(CC) ring_buffer_itr_test.o ring_buffer_class.o $(LIB) $(BOOST) -o ps3b

ps3c: guitar_string_class.o guitar_hero.o automatic_hero.o
	$(CC) guitar_string_class.o guitar_hero.o $(LIB) $(LINKER) -o $(GUITAR_BIN)
	$(CC) guitar_string_class.o automatic_hero.o $(LIB) $(LINKER) -o $(AUTO_BIN)

guitar_string_class.o: src/guitar_string_class.cpp src/guitar_string_class.hpp ring_buffer_class.o
	$(CC) $(FLAGS) $(INC) -c src/guitar_string_class.cpp src/guitar_string_class.hpp

guitar_hero.o: guitar_string_class.o src/guitar_hero.cpp
	$(CC) $(INC) -c src/guitar_hero.cpp

automatic_hero.o: guitar_string_class.o src/automatic_hero.cpp
	$(CC) $(INC) -c src/automatic_hero.cpp

ring_buffer_class.o: src/ring_buffer_class.cpp src/ring_buffer_class.hpp
	$(CC) $(FLAGS) -c src/ring_buffer_class.cpp src/ring_buffer_class.hpp

ring_buffer_test.o: /testring_buffer_test.cpp
	$(CC) $(INC) -c test/ring_buffer_test.cpp

ring_buffer_itr_test.o: test/ring_buffer_itr_test.cpp
	$(CC) $(INC) -c test/ring_buffer_itr_test.cpp

run: ps3c
	./$(GUITAR_BIN)
	./$(AUTO_BIN)

clean:
	rm -r *.o *.hpp.gch main ps3a *~ $(GUITAR_BIN) $(AUTO_BIN)
