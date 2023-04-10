//
// Created by Price Skip on 4/5/23.
//

#include "Command.hpp"


void	Command::checkPass(std::vector<std::string> &words, Ft_server &server, User &user){
	if (words.size() == 2){
		if (words.at(1) == server.getPassword()) {
			user.upAuthorizationStatus();
			send(server.getFds()[user.getFd()].fd, "correct pass\n", strlen("correct pass\n"), 0);
			return;
		}
		send(server.getFds()[user.getFd()].fd, "bad pass\n", 10, 0);
	}
	else
		send(server.getFds()[user.getFd()].fd, "bad args\n", 10, 0);
}

void	Command::checkNick(std::vector<std::string> &words, Ft_server &server, User &user){
	if (words.size() == 2){
		user.setNickname(words.at(1));
		user.upAuthorizationStatus();
		send(server.getFds()[user.getFd()].fd, "nice nick bro\n", strlen("nice nick bro\n"), 0);
		return;
	}
	send(server.getFds()[user.getFd()].fd, "bad args\n", 10, 0);
}

void	Command::checkUser(std::vector<std::string> &words, Ft_server &server, User &user){
	if (words.size() == 2){
		user.setUsername(words.at(1));
		user.upAuthorizationStatus();
		send(server.getFds()[user.getFd()].fd, "nice name bro\n", strlen("nice name bro\n"), 0);
		send(server.getFds()[user.getFd()].fd, "autorised\n", strlen("autorised\n"), 0);
		return;
	}
	send(server.getFds()[user.getFd()].fd, "bad args\n", 10, 0);
}

void 	Command::doPrivmsg(Ft_server &server, std::vector<std::string> &words, User &user) {
	std::map<int, User*>::iterator it;
	std::map<std::string, Channel*>	::iterator itCh;
	std::vector<std::string>::iterator itWords;

	for (it = server.getUsers().begin(); it != server.getUsers().end(); it++){
		if (words.at(1) == it->second->getNickname()){
			for (itWords = words.begin()+2; itWords != words.end(); itWords++) {
				//printf("(%s) with len = (%lu)\n", (*itWords).c_str(), (*itWords).size());
				send(server.getFds()[it->first].fd, (*itWords).c_str(), (size_t)(*itWords).size(), 0);
				send(server.getFds()[it->first].fd, " ", 1, 0);
			}
			send(server.getFds()[it->first].fd, "\n", 1, 0);
		}
	}
	if (!server.getChannels().empty()){
		for (itCh = server.getChannels().begin(); itCh != server.getChannels().end(); itCh++){
			if (words.at(1) == itCh->first){
				std::vector<int>::iterator itUsers;
				for (itUsers = itCh->second->getUsersVector().begin(); itUsers != itCh->second->getUsersVector().end(); itUsers++) {
					for (itWords = words.begin() + 2; itWords != words.end(); itWords++) {
						send(server.getFds()[*itUsers].fd, (*itWords).c_str(), (size_t) (*itWords).size(), 0);
						send(server.getFds()[*itUsers].fd, " ", 1, 0);
					}
					send(server.getFds()[*itUsers].fd, "\n", 1, 0);
				}
			}
		}
	}
}
// проработать ситуацию, когда южер джойнится в канал, в котором он уже состоит
void 	Command::doJoin(Ft_server &server, User &user, std::vector<std::string> &words) {
	std::map<std::string, Channel*>::iterator it;
	if (!server.getChannels().empty()) {
		for (it = server.getChannels().begin(); it != server.getChannels().end(); it++) {
			if (it->first == words.at(1)) {
				user.addChannels(words.at(1));
				server.addUserToChannel(user.getFd(), it->first);
				return;
			}
		}
	}
	server.addChannel(words.at(1), user.getFd());
	user.addChannels(words.at(1));

}
