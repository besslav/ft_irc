//
// Created by Price Skip on 3/30/23.
//

#include "libs.hpp"
#include "Ft_server.hpp"
#include "Command.hpp"
#include "User.hpp"


void	error(const std::string &error){
	std::cout << error << std::endl;
	exit(EXIT_FAILURE);
}

void debugChannels(Ft_server *server){
	std::map<std::string, Channel*>::const_iterator it_channel;
	std::map<int, User*>::iterator it_user;
	//в юзере вроде норм, а вот в чанеле список юзеров сломан

//	for (it_user = server->getUsers().begin(); it_user != server->getUsers().end(); it_user++) {
//		std::cout << "-----------------------------" << std::endl;
//		std::cout << "user:  " << it_user->second->getNickname() << std::endl;
//
//		std::cout << "-----_usersChannels list----" << std::endl;
//		std::vector<std::string>::iterator it_users_chanels;
//		for (it_users_chanels = it_user->second->getChannels().begin(); it_users_chanels != it_user->second->getChannels().end(); it_users_chanels++) {
//			std::cout << "chanel: " << *it_users_chanels << std::endl;
//		}
//		std::cout << "-----------------------------" << std::endl;
//	}
//	std::cout << "-------chanels list-------" << std::endl;
//	std::cout << "first_of_all: vectorCH->userFirst: " << *(server->getChannels().begin()->second->getUsersVector().begin()) << std::endl;
//	std::cout << "first_of_all: vectorCH->userFirst: " << *(server->getChannels().begin()->second->getUsersVector().begin()) << std::endl;
//	std::cout << "first_of_all: vectorCH->userFirst: " << *(server->getChannels().begin()->second->getUsersVector().begin()) << std::endl;
//	std::cout << "first_of_all: vectorCH->userFirst: " << *(server->getChannels().begin()->second->getUsersVector().begin()) << std::endl;
//	std::cout << "first_of_all: vectorCH->userFirst: " << *(server->getChannels().begin()->second->getUsersVector().begin()) << std::endl;
//	std::map<std::string, Channel*> channels = server->getChannels();
//	it_channel = channels.begin();
//	std::cout << "first userinch: " << *(it_channel->second->getUsersVector().begin()) << std::endl; // ошибка
//
//	std::cout << "size: " << (it_channel->second->getUsersVector().size()) << std::endl;// не ошибка
//	while (it_channel != channels.end()) {
//		std::cout << "w: " << (*(it_channel->second->getUsersVector().begin())) << std::endl; // ошибка
//		it_channel++;
//	}

//	for (it_channel = server->getChannels().begin(); it_channel != server->getChannels().end(); it_channel++){
//
//		std::cout << "chanel: " << it_channel->first << std::endl;
//		std::cout << "ovner: " << it_channel->second->getOvner() << std::endl;// не ошибка
//
//		//std::cout << "lastuserinch: " << (--it_channel->second->getUsersVector().end().) << std::endl;//  ошибка
//		std::cout << "		-------usersInChannel-------" << std::endl;
//		std::vector<std::string>::iterator itInChan;
//
//		for (itInChan = it_channel->second->getUsersVector().begin(); itInChan != it_channel->second->getUsersVector().end(); itInChan++){
//			std::cout << "	pre user:-->  ";
//			std::cout << "	user: " << *itInChan << std::endl;
//		}
//	}
}