//
// Created by Price Skip on 3/27/23.
//

#include "ft_server.hpp"


ft_server::ft_server() {}
ft_server::~ft_server() {}
ft_server::ft_server(int port, const std::string& pass) : _port(port), _pass(pass), _listening(-1)
{
	for (size_t i = 0; i < (size_t)FDSSIZE; i++)
		_fds[i].fd = -1;
	_fds[0].events = POLLIN;
	_fds[0].revents = 0;
}


//setters
void ft_server::setPort(int port) {_port = port;}
void ft_server::setListening(int listening) {_listening = listening;}
void ft_server::setPass(const std::string& pass) {_pass = pass;}

//getters
int 			ft_server::getPort() {return (_port);}
int 			ft_server::getListening() {return (_listening);}
std::string 	ft_server::getPassword() {return (_pass);}
struct pollfd* 	ft_server::getFds() {return (_fds);}

void ft_server::setNewConnection()
{
	for (size_t i = 1; i < (size_t)FDSSIZE; i++) {
		if (_fds[i].fd == -1) {
			//add user to map with key = i;
			_fds[i].fd = accept(_fds[0].fd, nullptr, nullptr);
			std::cout << "\033[1;33m" << "NEW CONNNECT key=" << i << "\033[0m" << std::endl;
			_fds[i].events = POLLIN;
			_fds[i].revents = 0;
			break;
		}
	}
}

void ft_server::continueConnection(size_t &i)
{
	char buf[BUFFSIZE];
	memset(buf, 0, BUFFSIZE);
	ssize_t bytesReceived = recv(_fds[i].fd, buf, BUFFSIZE, 0);
	if (bytesReceived == -1){
		error("Error in recv(). Quitting");
	}
	else if (bytesReceived == 0){
		std::cout << i << "Client disconnected " << std::endl;
		_fds[i].fd = -1;
	}
	else
	{
		printf("%s", buf);
	}

}
