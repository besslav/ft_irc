//
// Created by Price Skip on 4/5/23.
//

#ifndef FT_IRC_COMMAND_HPP
#define FT_IRC_COMMAND_HPP

#include "libs.hpp"
#include "Ft_server.hpp"
#include "User.hpp"


class Ft_server;
class User;
class Command {


public:
	void						checkPass(std::vector<std::string> &words, Ft_server &server, User &user);
	void						checkNick(std::vector<std::string> &words, Ft_server &server, User &user);
	void						checkUser(std::vector<std::string> &words, Ft_server &server, User &user);

	void 						doPrivmsg(Ft_server &server, std::vector<std::string> &words, User &user);
	void 						doJoin(Ft_server &server, User &user, std::vector<std::string> &words);
};


#endif //FT_IRC_COMMAND_HPP
