//
// Created by Price Skip on 3/30/23.
//

#ifndef FT_IRC_USER_H
#define FT_IRC_USER_H

#include "libs.hpp"
#include "Ft_server.hpp"
#include "Command.hpp"

class Ft_server;
class User {
private:
	std::string						_nickname;
	std::string						_username;
	std::vector<std::string>		_usersChannels;
	int 							_authorization_status;
	int								_sockfd;//key in map


public:
	User();
	User(int fd);
	~User();

//	setters
	void						setAuthorizationStatus(int newStatus);
	void 						setFd(int fd);
	void 						setNickname(const std::string& nick);
	void 						setUsername(const std::string& name);
	void 						upAuthorizationStatus();
	void 						addChannels(const std::string&	newChannel);


// getters
	int 						getAuthorization_status();
	int 						getFd();
	std::string 				getNickname();
	std::string 				getUsername();
	std::vector<std::string>	getChannels();

//	user

	void 						parsCommand(const std::string& command, Ft_server &server);
	std::vector<std::string>	parsCommandToVector(const std::string& command);

};


#endif //FT_IRC_USER_H
