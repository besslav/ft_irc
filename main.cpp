#include "Ft_server.hpp"

int		main(int argc, char **argv){
	if (argc != 3) { error("Args Error. Please type: <port> <password>"); }

	Ft_server	server(atoi(argv[1]), std::string(argv[2]));

	server.server_init();
	server.server_loop();
}
