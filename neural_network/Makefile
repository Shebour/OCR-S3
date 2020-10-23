CFLAGS = -Wall -Wextra -Werror -std=c99 -g
LDFLAGS = -fsanitize=address
BIN = main
OBJ = main.o network.o matrix.o

$(BIN) : $(OBJ)

clean:
	$(RM) $(BIN) $(OBJ) $(DEPS)
