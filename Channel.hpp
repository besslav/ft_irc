//
// Created by Price Skip on 4/9/23.
//

#ifndef FT_IRC_CHANNEL_HPP
#define FT_IRC_CHANNEL_HPP

#include "libs.hpp"
#include "User.hpp"

class User;
class Channel {
private:
	std::vector<int> 			_usersVector;
	//User 						_admin;
public:
	Channel(int	firstUser);
	std::vector<int>			getUsersVector();
	int							getAdmin();
	void 						addUser(int newUser);
	void 						kickUser(int user);
};


#endif //FT_IRC_CHANNEL_HPP
