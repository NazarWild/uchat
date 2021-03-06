CC = clang
NAME = uchat_server

R = \033[1;91m
G = \033[1;92m
B = \033[1;94m
D = \033[0m
K = \033[K

SRC_DIR = src/
OBJ_DIR = obj/
FILES_DIR = file_serv/
PROFILE_DIR = profile_users/

SRC = $(wildcard src/*.c)
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

CFLAGS = -std=c11 -pipe -g3 -fsanitize=address,undefined

LFLAGS = -lsqlite3 \
	-I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib \
	-lssl -lcrypto

WFLAGS = -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument \
	-Wno-unused-variable -Wno-unused-function -Wno-unused-parameter

COMPILE = $(CC) $(CFLAGS) $(LFLAGS) $(WFLAGS)

all: $(NAME)

$(OBJ_DIR):
	@mkdir $@

$(FILES_DIR):
	@mkdir $@

$(PROFILE_DIR):
	@mkdir $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@printf "$K$G COMPILING $B$(<:$(SRC_DIR)%=%)$D\r"
	@$(COMPILE) -c $< -o $@

$(NAME) : $(OBJ_DIR) $(OBJ) $(FILES_DIR) $(PROFILE_DIR)
	@printf "$K$G COMPILING $R$(NAME)$D\r"
	@$(COMPILE) $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

uninstall: clean
	@rm -rf $(NAME) libcrypto.dylib libssl.dylib

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
