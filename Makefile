NAME = uchat

FILES = mx_log_in \
	cJSON \
	mx_register \
	mx_connection \
	mx_login_win \
	mx_chat_win \
	mx_create_widge \
	main \
	mx_profile_gtk \
	mx_mini_profile_gtk \
	mx_photo_set \
	mx_message_to \
	mx_message_from \
	mx_parse_sign_in \
	create_friend \
	set_images \
	mx_dialog_open \
	setting_win \
	theme_1 \
	theme_2 \
	theme_3 \
	send_file_to \
	mx_time_mess_from \
	mx_time_mess_to \
	mx_name_mess_from \
	mx_name_mess_to \
	mx_hash_to_string \
	mx_hash \
	mx_find_login_by_id \
	mx_create_chat \
	mx_itoa \
	mx_strnew \
	mx_ssl \
	send_file_from \
	mx_memrchr \
	mx_delete_row \
	mx_delete_rows \
	mx_sticker \
	mx_unique_listbox_id \
	mx_sendsticker_to \
	mx_send_message \
	mx_sendsticker_from \
	mx_update_chat_id \
	mx_set_cur_chat_id \
	mx_type_of_file \
	mx_len_of_file \

SRC_PREFFIX = $(addprefix src/, $(FILES))

HEADER = inc/uchat.h

DEL_SRC = $(addsuffix .c, $(FILES))

SRC = $(addsuffix .c, $(SRC_PREFFIX))

SRC_COMPILE = $(addsuffix .c, $(SRC_PREFFIX))

OBJ = $(addsuffix .o, $(FILES))

CFLAGS = -std=c11 `pkg-config --cflags gtk+-3.0`  #`pkg-config --libs gtk+-3.0`

OFLAGS = `pkg-config --libs gtk+-3.0` -lpthread

all: install

install: $(NAME)
	
$(NAME) : $(SRC) $(INC)
	@cp local_lib/lib/libcrypto.dylib . 
	@cp local_lib/lib/libssl.dylib .
	@clang $(CFLAGS) -c $(SRC_COMPILE) -I local_lib/include
	@clang $(CFLAGS) $(OBJ) -o $(NAME) $(OFLAGS) -L ./ -I local_lib/include -lssl -lcrypto
	@mkdir -p obj
	@cp $(OBJ) obj/
	@rm -rf $(OBJ)

uninstall: clean
	@rm -rf $(NAME)
	@rm -rf libcrypto.dylib libssl.dylib

clean:
	@rm -rf obj

reinstall: uninstall install
