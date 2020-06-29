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
	mx_profile_photo_box \
	mx_design \
	mx_message_to \
	mx_message_from \
	mx_parse_sign_in \
	create_friend \

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
	@clang $(CFLAGS) -c $(SRC_COMPILE)
	@clang $(CFLAGS) $(OBJ) -o $(NAME) $(OFLAGS)
	@mkdir -p obj
	@cp $(OBJ) obj/
	@rm -rf $(OBJ)

uninstall: clean
	@rm -rf $(NAME)

clean:
	@rm -rf obj

reinstall: uninstall install
