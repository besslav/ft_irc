//
// Created by Price Skip on 4/5/23.
//

#include "Command.hpp"


void	Command::checkPass(std::vector<std::string> *words, Ft_server *server, User &user){
	if (words->size() == 2){
		if (words->at(1) == server->getPassword()) {
			user.upAuthorizationStatus();
			send(server->getFds()[user.getFd()].fd, "correct pass\n", strlen("correct pass\n"), 0);
			return;
		}
		send(server->getFds()[user.getFd()].fd, "bad pass\n", 10, 0);
	}
	else
		send(server->getFds()[user.getFd()].fd, "bad args\n", 10, 0);
}

void	Command::checkNick(std::vector<std::string> *words, Ft_server *server, User &user){
	if (words->size() == 2){
		user.setNickname(words->at(1));
		user.upAuthorizationStatus();
		send(server->getFds()[user.getFd()].fd, "nice nick bro\n", strlen("nice nick bro\n"), 0);
		return;
	}
	send(server->getFds()[user.getFd()].fd, "bad args\n", 10, 0);
}

void	Command::checkUser(std::vector<std::string> *words, Ft_server *server, User &user){
	if (words->size() == 2){
		user.setUsername(words->at(1));
		user.upAuthorizationStatus();
		send(server->getFds()[user.getFd()].fd, "nice name bro\n", strlen("nice name bro\n"), 0);
		send(server->getFds()[user.getFd()].fd, "autorised\n", strlen("autorised\n"), 0);
		return;
	}
	send(server->getFds()[user.getFd()].fd, "bad args\n", 10, 0);
}

void 	Command::doPrivmsg(Ft_server *server, std::vector<std::string> *words, User &user) {
	std::map<int, User*>::iterator it;

	for (it = server->getUsers().begin(); it != server->getUsers().end(); it++){
		if (words->at(1) == it->second->getNickname()){
			send(server->getFds()[it->first].fd, "you have an email\n", strlen("you have an email\n"), 0);
			return;
		}
	}
}
