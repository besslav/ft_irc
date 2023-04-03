//
// Created by Price Skip on 3/30/23.
//

#include "user.hpp"


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


//user

void	user::parsCommand(const std::string& command, struct pollfd *fds ) {
	std::vector<std::string> Words;
	std::istringstream input2;
	input2.str(command);
	if (command != "fsdfs" and fds[0].fd != 0){ }
	for (std::string line; std::getline(input2, line, ' ');) {
		line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
		line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
		Words.push_back(line);
	}
	std::cout << '(' << Words.at(0) << ")" << std::endl;


}

void 	user::printAns() {
	printf("(ans from %d)\n", _sockfd);
	//send(_sockfd, "(ans)\n", 7, 0);
}