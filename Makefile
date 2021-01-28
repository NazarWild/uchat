name_server = uchat_server
name_client = uchat

all: server_ client_

$(name_server): server_

server_:
	@make -sC server
	@cp server/uchat_server .

$(name_client): client_

client_:
	@make -sC client
	@cp client/uchat .


uninstall: clean
	@make -sC server $@
	@make -sC client $@
	@rm -rf $(name_client) $(name_server)

clean:
	@make -sC server $@
	@make -sC client $@

reinstall: uninstall all
