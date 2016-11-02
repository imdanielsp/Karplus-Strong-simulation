CC=g++
BOOST=-lboost_unit_test_framework
LINKER=-lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
INC=-I/usr/local/include/
LIB=-L/usr/local/lib/
FLAGS=-Wall -ansi -pedantic

all: ps3c

ps3a: ring_buffer_class.o ring_buffer_test.o
	$(CC) ring_buffer_test.o ring_buffer_class.o $(LIB) $(BOOST) -o ps3a

ps3b: ring_buffer_class.o ring_buffer_itr_test.o
	$(CC) ring_buffer_itr_test.o ring_buffer_class.o $(LIB) $(BOOST) -o ps3b

ps3c: guitar_string_class.o guitar_hero.o automatic_hero.o
	$(CC) guitar_string_class.o guitar_hero.o $(LIB) $(LINKER) -o GuitarHero
	$(CC) guitar_string_class.o automatic_hero.o $(LIB) $(LINKER) -o AutoHero

guitar_string_class.o: guitar_string_class.cpp guitar_string_class.hpp ring_buffer_class.o
	$(CC) $(FLAGS) $(INC) -c ring_buffer_class.o guitar_string_class.cpp guitar_string_class.hpp

guitar_hero.o: guitar_string_class.o guitar_hero.cpp
	$(CC) $(INC) -c guitar_hero.cpp

automatic_hero.o: guitar_string_class.o automatic_hero.cpp
	$(CC) $(INC) -c automatic_hero.cpp

ring_buffer_class.o: ring_buffer_class.cpp ring_buffer_class.hpp
	$(CC) $(FLAGS) -c ring_buffer_class.cpp ring_buffer_class.hpp

ring_buffer_test.o: ring_buffer_test.cpp
	$(CC) $(INC) -c ring_buffer_test.cpp

ring_buffer_itr_test.o: ring_buffer_itr_test.cpp
	$(CC) $(INC) -c ring_buffer_itr_test.cpp

main: ring_buffer_class.o
	$(CC) main.cpp ring_buffer_class.o -o main

clean:
	rm -r *.o *.hpp.gch test main ps3a *~ GuitarHero AutoHero