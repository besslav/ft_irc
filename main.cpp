#include "ft_server.hpp"

int		main(int argc, char **argv){
	if (argc != 3) { error("Args Error. Please type: <port> <password>"); }

	ft_server	server(atoi(argv[1]), std::string(argv[2]));

	// инит сокета
	server.setListening(socket(PF_INET, SOCK_STREAM, 0));
	if (server.getListening() == -1) { error("Error establishing connection"); }

	// позволяет использовать порт повторно(в случае если он еще не освободился)
	int flagOne = 1;
	if (setsockopt(server.getListening(), SOL_SOCKET, SO_REUSEADDR, &flagOne, sizeof(int)) < 0){ error("setsockpt error"); }

	// связь сокета с портом чтобы слушать входные подключения на порте
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(server.getPort());
	hint.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);
	if (bind(server.getListening(), (sockaddr *)&hint, sizeof(hint)) == -1) { error("Can't bind"); }

	// слушаем сокет
	if (listen(server.getListening(), SOMAXCONN) == -1) { error("Can't listen"); }
	server.getFds()[0].fd = server.getListening();
	fcntl(server.getFds()[0].fd, F_SETFL, O_NONBLOCK);


	//serverMainLoop
	while (true)
	{
		//int ret = poll(server.getFds(), server.getNumberOfConnections(), TIMEOUT);
		int ret = poll(server.getFds(), FDSSIZE, TIMEOUT);
		if (ret == -1) { error("poll error"); }
		for (size_t i = 0; i < (size_t )FDSSIZE; i++)
		{
			if (server.getFds()[i].fd > 0 && (server.getFds()[i].revents & POLLIN) == POLLIN)
			{
				if (i == 0)
					server.setNewConnection();
				else
					server.continueConnection(i);
			}
		}
	}
}
