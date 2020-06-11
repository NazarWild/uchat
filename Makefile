NAME = klient

SERVER = server

FILES = mx_log_in \
		mx_connection \

SRC_PREFFIX = $(addprefix src/, $(FILES))

HEADER = inc/uchat.h

DEL_SRC = $(addsuffix .c, $(FILES))

SRC = $(addsuffix .c, $(SRC_PREFFIX))

SRC_COMPILE = $(addsuffix .c, $(SRC_PREFFIX))

OBJ = $(addsuffix .o, $(FILES))

CFLAGS = -std=c11 -Werror -Wall -Wextra -Wpedantic

all: install

install: $(NAME) $(SERVER)

$(NAME) : $(SRC) $(INC)
	@make -C libmx install
	@clang $(CFLAGS) -c $(SRC_COMPILE)
	@clang $(CFLAGS) $(OBJ) -o $(NAME)
	@mkdir -p obj
	@cp $(OBJ) obj/
	@rm -rf $(OBJ)

$(SERVER) :
	@clang src/userver.c -o $(SERVER)

uninstall: clean
	@make -C libmx uninstall
	@rm -rf $(NAME)
	@rm -rf $(SERVER)

clean:
	@make -C libmx clean
	@rm -rf obj

reinstall: uninstall install
