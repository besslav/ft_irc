//
// Created by Price Skip on 3/30/23.
//

#include "User.hpp"
#include <typeinfo>


User::User() :   _authorization_status(0), _sockfd(-1)  {}
User::User(int fd) : _authorization_status(0), _sockfd(fd)  {}
User::~User() {}

// SETTERS
void		User::setFd(int fd) { _sockfd = fd; }
void		User::setUsername(const std::string& username) { _username = username; }
void		User::setNickname(const std::string& nickname) { _nickname = nickname; }
void		User::setAuthorizationStatus(int status) { _authorization_status = status; }
void 		User::upAuthorizationStatus() {_authorization_status += 1;}


// GETTERS
int					User::getFd() { return(_sockfd); }
int					User::getAuthorization_status() { return(_authorization_status); }
std::string 		User::getNickname() { return (_nickname); }
std::string 		User::getUsername() { return (_username);  }


std::vector<std::string>	User::parsCommandToVector(const std::string& command) {
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

void	User::parsCommand(const std::string& command_line, Ft_server &server ) {
	std::vector<std::string> words = parsCommandToVector(command_line);
	Command commandexecuter;
	if (!words.empty()) {
		if (words.at(0) == "PASS" and _authorization_status == 0) {
			commandexecuter.checkPass(&words, &server, *this);
		}
		else if (words.at(0) == "NICK" and _authorization_status == 1) {
			commandexecuter.checkNick(&words , &server, *this);
		}
		else if (words.at(0) == "USER" and _authorization_status == 2) {
			commandexecuter.checkUser(&words, &server, *this);
		}
		else if (_authorization_status == 3){
			if (words.at(0) == "PRIVMSG"){
				commandexecuter.doPrivmsg(&server, &words, *this);
			}
			printf("user %s with nick %s autoriz on fd: %i\n", _username.c_str(), _nickname.c_str(), _sockfd);
		}
		else{
			send(server.getFds()[_sockfd].fd, "who are you, warrior?\n", strlen("who are you, warrior?\n"), 0);
		}
	}


}