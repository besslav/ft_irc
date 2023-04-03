//
// Created by Price Skip on 3/30/23.
//

#ifndef FT_IRC_USER_H
#define FT_IRC_USER_H

#include "libs.hpp"
#include "ft_server.hpp"

class ft_server;
class user {
private:
	std::string				_nickname;
	std::string				_username;
	int 					_authorization_status;

	int						_sockfd;//key in map

	//void checkUserPassword(ft_server &server, std::string message, int i);

public:
	user();
	user(int fd);
	~user();

//	setters
	void					setAuthorization_status(int newStatus);
	void 					setFd(int fd);
	void 					setNickname(const std::string& nick);
	void 					setUsername(const std::string& name);


// getters
	int 					getAuthorization_status();
	int 					getFd();
	std::string 			getNickname();
	std::string 			getUsername();


//	user

	void 					parsCommand(const std::string& command, struct pollfd *fds);
	void 					printAns();
};


#endif //FT_IRC_USER_H
