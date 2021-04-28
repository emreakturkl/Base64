# ----------------------------------------------------------------------

CC     = gcc
CFLAGS = -Wall -I${INCLUDE_DIR}

# ----------------------------------------------------------------------

PATH_           = $(PWD)
INCLUDE_DIR     = include/
SOURCE_DIR      = src/
OBJECT_DIR      = obj/Debug/
OBJECT_SRC_DIR  = obj/Debug/src/
DEBUG           = bin/Debug/

#$(info $(DIR))

# ----------------------------------------------------------------------

TARGET = main

$(DEBUG)${TARGET}: $(OBJECT_DIR)main.o $(OBJECT_SRC_DIR)base64.o
	if ! [ -d "$(PATH_)/$(DEBUG)" ]; then mkdir -p $(DEBUG); fi;
	${CC} -o $@ $^

$(OBJECT_DIR)main.o: main.c
	if ! [ -d "$(PATH_)/$(OBJECT_DIR)" ]; then mkdir -p $(OBJECT_SRC_DIR); fi;
	${CC} ${CFLAGS} -c $< -o $@

$(OBJECT_SRC_DIR)base64.o: $(SOURCE_DIR)base64.c
	${CC} ${CFLAGS} -c $< -o $@

run:
	make clean
	make
	./${DEBUG}main

clean:
	rm -f $(OBJECT_DIR)*.o
	rm -f $(OBJECT_SRC_DIR)*.o
	rm -f $(DEBUG)${TARGET}
