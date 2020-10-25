CFLAGS = -Wall -Wextra -Werror -Wno-unused-result -std=c99 -g
LDFLAGS = -fsanitize=address
LDLIBS  = -lm
BIN = main
OBJ = main.o network.o matrix.o motion.o

$(BIN) : $(OBJ)

clean:
	$(RM) $(BIN) $(OBJ) $(DEPS)
