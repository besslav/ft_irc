//
// Created by Price Skip on 4/9/23.
//

#include "Channel.hpp"

Channel::Channel(int firstUser) {
	_usersVector.push_back(firstUser);
}

std::vector<int> 		Channel::getUsersVector() {return _usersVector;}
void 					Channel::addUser(int newUser) { _usersVector.push_back(newUser);}
void 					Channel::kickUser(int user) {
	std::vector<int>::iterator it;
	for (it = _usersVector.begin(); it != _usersVector.end(); it++){
		if (*(it) == user){
			_usersVector.erase(it);
		}
	}
}
int 	Channel::getAdmin() {return _usersVector.at(0);}
