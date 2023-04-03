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


//std::string *parsWords(std::string s) {
//	// Use find function to find 1st position of delimiter.
//	int end = s.find(' ');
//	while (end != -1) { // Loop until no delimiter is left in the string.
//		s.erase(s.begin(), s.begin() + end + 1);
//		end = s.find(' ');
//	}
//}
//void	user::parsCommand(std::string command, const struct pollfd &fds ) {
//	//std::string Words[3];
//	all_words
//
//
//
//
//}

void 	user::printAns() {
	printf("(ans from %d)\n", _sockfd);
	send(_sockfd, "(ans)\n", 7, 0);
}