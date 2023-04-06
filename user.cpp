//
// Created by Price Skip on 3/30/23.
//

#include "user.hpp"
#include <typeinfo>


user::user() :   _authorization_status(0)  {}
user::user(int fd) : _authorization_status(0), _sockfd(fd)  {}
user::~user() {}

// SETTERS
void		user::setFd(int fd) { _sockfd = fd; }
void		user::setUsername(const std::string& username) { _username = username; }
void		user::setNickname(const std::string& nickname) { _nickname = nickname; }
void		user::setAuthorization_status(int status) { _authorization_status = status; }


// GETTERS
int					user::getFd() { return(_sockfd); }
int					user::getAuthorization_status() { return(_authorization_status); }
std::string 		user::getNickname() { return (_nickname); }
std::string 		user::getUsername() { return (_username);  }


std::vector<std::string>	user::parsCommandToVector(const std::string& command) {
	std::vector<std::string> Words;
	std::istringstream input2;
	input2.str(command);
	for (std::string line; std::getline(input2, line, ' ');) {
		line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
		line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
		Words.push_back(line);
	}
	return Words;
}

void	user::checkPass(std::vector<std::string> *words, ft_server *server){
	if (words->size() == 2){
		if (words->at(1) == server->getPassword()) {
			_authorization_status += 1;
			send(server->getFds()[_sockfd].fd, "correct pass\n", strlen("correct pass\n"), 0);
			return;
		}
		send(server->getFds()[_sockfd].fd, "bad pass\n", 10, 0);
	}
	else
		send(server->getFds()[_sockfd].fd, "bad args\n", 10, 0);
}

void	user::checkNick(std::vector<std::string> *words, ft_server *server){
	if (words->size() == 2){
		_nickname = words->at(1);
		_authorization_status += 1;
		send(server->getFds()[_sockfd].fd, "nice nick bro\n", strlen("nice nick bro\n"), 0);
		return;
	}
	send(server->getFds()[_sockfd].fd, "bad args\n", 10, 0);
}

void	user::checkUser(std::vector<std::string> *words, ft_server *server){
	if (words->size() == 2){
		_username = words->at(1);
		_authorization_status += 1;
		send(server->getFds()[_sockfd].fd, "nice name bro\n", strlen("nice name bro\n"), 0);
		send(server->getFds()[_sockfd].fd, "autorised\n", strlen("autorised\n"), 0);
		return;
	}
	send(server->getFds()[_sockfd].fd, "bad args\n", 10, 0);
}

void 	user::doPrivmsg(ft_server *server, std::vector<std::string> *words) {
	std::map<int, user*>::iterator it;
//	it = server.ge

	for (it = server->getUsers().begin(); it != server->getUsers().end(); it++){
		std::cout << "too_this_one_or?"  << std::endl;
		//std::cout << "adress " << server->getFds()[it->first].fd << std::endl;
//		if (words->at(1) == it->second->_nickname){
//			std::cout << "sended_in" << std::endl;
//			//send(server->getFds()[it->first].fd, "you have an email\n", strlen("you have an email\n"), 0);
//		}
//		std::cout << "sended" << std::endl;
	}

}

void	user::parsCommand(const std::string& command, ft_server server ) {
	std::vector<std::string> words = parsCommandToVector(command);
	if (!words.empty()) {
		if (words.at(0) == "PASS" and _authorization_status == 0) {
			checkPass(&words, &server);
		}
		else if (words.at(0) == "NICK" and _authorization_status == 1) {
			checkNick(&words , &server);
		}
		else if (words.at(0) == "USER" and _authorization_status == 2) {
			checkUser(&words, &server);
		}
		else if (_authorization_status == 3){
			if (words.at(0) == "PRIVMSG"){
				doPrivmsg(&server, &words);
			}
			printf("user %s with nick %s autoriz on fd: %i\n", _username.c_str(), _nickname.c_str(), _sockfd);
		}
		else{
			send(server.getFds()[_sockfd].fd, "who are you, warrior?\n", strlen("who are you, warrior?\n"), 0);
		}
	}


}