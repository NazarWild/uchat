CC = clang
NAME = uchat

R = \033[1;91m
G = \033[1;92m
B = \033[1;94m
D = \033[0m
K = \033[K

SRC_DIR = src/
OBJ_DIR = obj/

SRC = $(wildcard src/*.c)
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

CFLAGS = -std=c11 -pipe -g3 -fsanitize=address

LFLAGS = -I/usr/local/opt/openssl/include -lsqlite3 \
	-L/usr/local/opt/openssl/lib/ -I/usr/local/opt/openssl/include \
	-lssl -lcrypto -lpthread `pkg-config --libs --cflags gtk+-3.0` \
	-Ilocal_lib/include -L. -Ilocal_lib/include

WFLAGS = -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument \
	-Wno-unused-variable -Wno-unused-function -Wno-unused-parameter

COMPILE = $(CC) $(CFLAGS) $(LFLAGS) $(WFLAGS)

all: $(NAME)

$(OBJ_DIR):
	@mkdir $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@printf "$K$G COMPILING $B$(<:$(SRC_DIR)%=%)$D\r"
	@$(COMPILE) -o $@ -c $<

$(NAME) : $(OBJ_DIR) $(OBJ)
	@cp local_lib/lib/libcrypto.dylib .
	@cp local_lib/lib/libssl.dylib .
	@printf "$K$G COMPILING $R$(NAME)$D\r"
	@$(COMPILE) $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

uninstall: clean
	@rm -rf $(NAME) libcrypto.dylib libssl.dylib

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
