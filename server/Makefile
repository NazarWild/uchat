NAME = uchat_server

FILES = u_server \
		cJSON \
		mx_create_table \
		mx_sqlite \
		mx_registr \
		mx_sign_in_error \
		mx_pass_connect \
		mx_creating \
		mx_send_mess \
		mx_itoa \
		mx_list \
		mx_whoonline \
		mx_add_mess \
		mx_papa_bot \
		mx_delete \
		mx_delete_socket \
		mx_free_online \
		mx_file_type \
		mx_strjoin \
		mx_strnew \
		mx_chats_send \
		mx_list_last_users_messeges \
		mx_answers_papa \
		mx_new_chat \
		mx_group_chat \
		mx_send_group \

SRC_PREFFIX = $(addprefix src/, $(FILES))

HEADER = inc/uchat.h

DEL_SRC = $(addsuffix .c, $(FILES))

SRC = $(addsuffix .c, $(SRC_PREFFIX))

SRC_COMPILE = $(addsuffix .c, $(SRC_PREFFIX))

OBJ = $(addsuffix .o, $(FILES))

CFLAGS = -std=c11

all: install

install: $(NAME)

$(NAME) : $(SRC) $(INC)
	@clang $(CFLAGS) -c $(SRC_COMPILE) -I/usr/local/opt/openssl/include 
	@clang $(CFLAGS) $(OBJ) -o $(NAME) -l sqlite3 -L/usr/local/opt/openssl/lib/ -I/usr/local/opt/openssl/include -lssl -lcrypto
	@mkdir -p obj
	@cp $(OBJ) obj/
	@rm -rf $(OBJ)

uninstall: clean
	@rm -rf $(NAME)

clean:
	@rm -rf obj

reinstall: uninstall install
