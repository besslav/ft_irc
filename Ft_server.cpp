//
// Created by Price Skip on 3/27/23.
//

#include "Ft_server.hpp"


Ft_server::Ft_server() {}
Ft_server::~Ft_server() {}
Ft_server::Ft_server(int port, const std::string& pass) : _port(port), _pass(pass), _listening(-1)
{
	for (size_t i = 0; i < (size_t)FDSSIZE; i++)
		_fds[i].fd = -1;
	_fds[0].events = POLLIN;
	_fds[0].revents = 0;
}


//setters
void Ft_server::setPort(int port) {_port = port;}
void Ft_server::setListening(int listening) {_listening = listening;}
void Ft_server::setPass(const std::string& pass) {_pass = pass;}
void Ft_server::addChannel(const std::string& channelName, int user) {
	_channels.insert(std::pair<std::string, Channel*>(channelName, new Channel(user)));

}

void Ft_server::addUserToChannel(int user, const std::string& channel) {
	_channels.at(channel)->addUser(user);
}

//getters
int 							Ft_server::getPort() {return (_port);}
int 							Ft_server::getListening() {return (_listening);}
std::string 					Ft_server::getPassword() {return (_pass);}
struct pollfd* 					Ft_server::getFds() {return (_fds);}
std::map<int, User*>&			Ft_server::getUsers() {return (_users);}
std::map<std::string, Channel*>	Ft_server::getChannels() { return (_channels);}

//serv
void Ft_server::server_init()
{
	_listening =  socket(PF_INET, SOCK_STREAM, 0);
	if (_listening == -1) { error("Error establishing connection"); }

	// позволяет использовать порт повторно(в случае если он еще не освободился)
	int flagOne = 1;
	if (setsockopt(_listening, SOL_SOCKET, SO_REUSEADDR, &flagOne, sizeof(int)) < 0){ error("setsockpt error"); }

	// связь сокета с портом чтобы слушать входные подключения на порте
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(_port);
	hint.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);
	if (bind(_listening, (sockaddr *)&hint, sizeof(hint)) == -1) { error("Can't bind"); }

	// слушаем сокет
	if (listen(_listening, SOMAXCONN) == -1) { error("Can't listen"); }
	_fds[0].fd = _listening;
	fcntl(_fds[0].fd, F_SETFL, O_NONBLOCK);
}

void Ft_server::server_loop()
{
	while (true)
	{
		int ret = poll(_fds, FDSSIZE, TIMEOUT);
		if (ret == -1) { error("poll error"); }
		for (int i = 0; i < FDSSIZE; i++)
		{
			if (_fds[i].fd > 0 && (_fds[i].revents & POLLIN) == POLLIN)
			{
				if (i == 0)
					setNewConnection();
				else
					continueConnection(i);
			}
		}
	}
}


void Ft_server::setNewConnection()
{
	for (int i = 1; i < FDSSIZE; i++) {
		if (_fds[i].fd == -1) {
			_fds[i].fd = accept(_fds[0].fd, nullptr, nullptr);
			std::cout << "\033[1;33m" << "NEW CONNNECT KEY=" << i << "\033[0m" << std::endl;
			_fds[i].events = POLLIN;
			_fds[i].revents = 0;

			_users.insert(std::pair<int, User*>(i, new User(i)));

			break;
		}
	}
}

void Ft_server::dcUser(int i){
	std::cout << i << " Client disconnected " << std::endl;
	_users.erase(i);
	close(_fds[i].fd);
	_fds[i].fd = -1;
}

void Ft_server::continueConnection(int &i)
{
	char buf[BUFFSIZE];
	memset(buf, 0, BUFFSIZE);
	ssize_t bytesReceived = recv(_fds[i].fd, buf, BUFFSIZE, 0);
	if (bytesReceived == -1){
		error("Error in recv(). Quitting");
	}
	else if (bytesReceived == 0){
		dcUser(i);
	}
	else{
		_users.at((int)i)->parsCommand(buf, *this);
	}
}
