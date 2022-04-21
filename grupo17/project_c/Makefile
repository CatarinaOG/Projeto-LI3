FLAGS= -std=c99 -Wextra -O2 -D_GNU_SOURCE -g -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include  
PKG = `pkg-config --cflags --libs glib-2.0`
COMPILER=gcc
INCLUDES=includes
SRC=source
OBJ=objects



program: $(OBJ)/main.o $(OBJ)/users.o $(OBJ)/reviews.o $(OBJ)/business.o $(OBJ)/stats.o $(OBJ)/sgr.o $(OBJ)/queriesAux.o $(OBJ)/interpretador.o $(OBJ)/tasks.o $(OBJ)/apresentador.o
	$(COMPILER) $(FLAGS)  -o program $(OBJ)/main.o $(OBJ)/users.o $(OBJ)/reviews.o $(OBJ)/business.o $(OBJ)/stats.o $(OBJ)/sgr.o $(OBJ)/queriesAux.o $(OBJ)/interpretador.o $(OBJ)/tasks.o $(OBJ)/apresentador.o $(PKG)

objects/main.o: $(SRC)/main.c $(INCLUDES)/users.h $(INCLUDES)/business.h $(INCLUDES)/reviews.h $(INCLUDES)/stats.h $(INCLUDES)/sgr.h $(INCLUDES)/queriesAux.h $(INCLUDES)/interpretador.h $(INCLUDES)/tasks.h  $(INCLUDES)/apresentador.h
	$(COMPILER) $(FLAGS)  -o $(OBJ)/main.o -c $(SRC)/main.c $(PKG)

objects/users.o: $(SRC)/users.c $(INCLUDES)/users.h
	$(COMPILER) $(FLAGS)  -o $(OBJ)/users.o -c $(SRC)/users.c $(PKG)

objects/reviews.o: $(SRC)/reviews.c $(INCLUDES)/reviews.h
	$(COMPILER) $(FLAGS)  -o $(OBJ)/reviews.o -c $(SRC)/reviews.c $(PKG)

objects/business.o: $(SRC)/business.c $(INCLUDES)/business.h
	$(COMPILER) $(FLAGS)  -o $(OBJ)/business.o -c $(SRC)/business.c $(PKG)

objects/stats.o: $(SRC)/stats.c $(INCLUDES)/stats.h
	$(COMPILER) $(FLAGS)  -o $(OBJ)/stats.o -c $(SRC)/stats.c $(PKG)

objects/sgr.o: $(SRC)/sgr.c $(INCLUDES)/sgr.h
	$(COMPILER) $(FLAGS)  -o $(OBJ)/sgr.o -c $(SRC)/sgr.c $(PKG)

objects/queriesAux.o: $(SRC)/queriesAux.c $(INCLUDES)/queriesAux.h
	$(COMPILER) $(FLAGS)  -o $(OBJ)/queriesAux.o -c $(SRC)/queriesAux.c $(PKG)

objects/interpretador.o: $(SRC)/interpretador.c $(INCLUDES)/interpretador.h
	$(COMPILER) $(FLAGS)  -o $(OBJ)/interpretador.o -c $(SRC)/interpretador.c $(PKG)

objects/tasks.o: $(SRC)/tasks.c $(INCLUDES)/tasks.h
	$(COMPILER) $(FLAGS)  -o $(OBJ)/tasks.o -c $(SRC)/tasks.c $(PKG)

objects/apresentador.o: $(SRC)/apresentador.c $(INCLUDES)/apresentador.h
	$(COMPILER) $(FLAGS)  -o $(OBJ)/apresentador.o -c $(SRC)/apresentador.c $(PKG) 

memcheck:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./prog
clean:
	rm -rf $(OBJ)/*.o program