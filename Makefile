NAME = klient_2

SERVER = server

SERVER_SRC = src/u_server.c \
	src/cJSON.c
	
FILES = mx_log_in \
	mx_connection \
	mx_login_win \
	mx_chat_win \
	mx_create_widge \
	main \
	cJSON \
	

SRC_PREFFIX = $(addprefix src/, $(FILES))

HEADER = inc/uchat.h

DEL_SRC = $(addsuffix .c, $(FILES))

SRC = $(addsuffix .c, $(SRC_PREFFIX))

SRC_COMPILE = $(addsuffix .c, $(SRC_PREFFIX))

OBJ = $(addsuffix .o, $(FILES))

CFLAGS = -std=c11 `pkg-config --libs --cflags gtk+-3.0` -lpthread

CFLAGS_SER = -std=c11 -lpthread

all: install

install: $(NAME) $(SERVER)

$(NAME) : $(SRC) $(INC)
	@clang $(CFLAGS) -c $(SRC_COMPILE)
	@clang $(CFLAGS) $(OBJ) -o $(NAME)
	@mkdir -p obj
	@cp $(OBJ) obj/
	@rm -rf $(OBJ)

$(SERVER) : $(SERVER_SRC)
	@clang $(CFLAGS_SER) -c $(SERVER_SRC)
	@clang $(SERVER_SRC) -o $(SERVER)

uninstall: clean
	@rm -rf $(NAME)
	@rm -rf $(SERVER)

clean:
	@rm -rf obj
	@rm userver.o

reinstall: uninstall install
