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


public:
	user();
	user(int fd);
	~user();

//	setters
	void						setAuthorization_status(int newStatus);
	void 						setFd(int fd);
	void 						setNickname(const std::string& nick);
	void 						setUsername(const std::string& name);


// getters
	int 						getAuthorization_status();
	int 						getFd();
	std::string 				getNickname();
	std::string 				getUsername();

//	pars autorization
	void						checkPass(std::vector<std::string> *words, ft_server *server);
	void						checkNick(std::vector<std::string> *words, ft_server *server);
	void						checkUser(std::vector<std::string> *words, ft_server *server);
//	user

	void 						parsCommand(const std::string& command, ft_server server);
	std::vector<std::string>	parsCommandToVector(const std::string& command);

	void 						doPrivmsg(ft_server *server, std::vector<std::string> *words);
};


#endif //FT_IRC_USER_H
