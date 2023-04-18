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

void	Command::sendMessage(Ft_server &server, std::vector <std::string> &words, int usersFd) {
	std::vector<std::string>::iterator itWords;
	for (itWords = words.begin()+2; itWords != words.end(); itWords++) {
		send(server.getFds()[usersFd].fd, (*itWords).c_str(), (size_t)(*itWords).size(), 0);
		send(server.getFds()[usersFd].fd, " ", 1, 0);
	}
	send(server.getFds()[usersFd].fd, "\n", 1, 0);
}

void 	Command::doPrivmsg(Ft_server &server, std::vector<std::string> &words, User &user) {
	std::string sendTo = words.at(1);
	if (sendTo[0] == '#'){
		std::map<std::string, Channel*>::iterator it;
		std::map<std::string, Channel*> chanels = server.getChannels();
		it = chanels.find(sendTo);
		if (it != chanels.end()){
			std::vector<int> users = it->second->getUsersVector();
			std::vector<int>::iterator usersIt;
			for (usersIt = users.begin(); usersIt != users.end(); usersIt++){
				sendMessage(server, words, *usersIt);
			}
		}
	} else{
		std::map<int, User*>::iterator it;
		std::map<int, User*> users = server.getUsers();
		int userFd = server.getUsersFdByName(sendTo);
		if (userFd == -1){
			send(server.getFds()[user.getFd()].fd, "unknown user\n", 13, 0);
			return;
		}
		it = users.find(userFd);
		if (it != users.end()){
			sendMessage(server, words, it->second->getFd());
		}
	}

}



// проработать ситуацию, когда южер джойнится в канал, в котором он уже состоит
void 	Command::doJoin(Ft_server &server, User &user, std::vector<std::string> &words) {
	std::string channelName = words.at(1);
	if (channelName[0] != '#'){
		send(server.getFds()[user.getFd()].fd,	"channel name should start by #\n", 31, 0);
		return;
	}
	std::map<std::string, Channel*>::iterator it;
	std::map<std::string, Channel*> chanels = server.getChannels();
	it = chanels.find(channelName);

	if (it != chanels.end()){
		user.addChannels(channelName);
		server.addUserToChannel(user.getFd(), channelName);
	} else {
		server.addChannel(channelName, user.getFd());
		user.addChannels(channelName);
	}
}
