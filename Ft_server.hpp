//
// Created by Price Skip on 3/27/23.
//

#ifndef FT_IRC_FT_SERVER_H
#define FT_IRC_FT_SERVER_H

#include "libs.hpp"
#include "User.hpp"

class User;
class Ft_server {
private:
	int							_port;
	std::string 				_pass;
	int 						_listening;
	struct pollfd 				_fds[FDSSIZE];
	std::map<int, User*>		_users;



public:
	Ft_server();
	~Ft_server();
	Ft_server(int port, const std::string& pass);

//	setters
	void 					setPort(int port);
	void 					setPass(const std::string& pass);
	void 					setListening(int listening);

//	getters
	int						getPort();
	int						getListening();
	std::string				getPassword();
	struct pollfd*			getFds();
	std::map<int, User*>&	getUsers();

	//serv
	void 					server_init();
	void 					server_loop();
	void 					setNewConnection();
	void 					continueConnection(int &i);





};

#endif //FT_IRC_FT_SERVER_H
