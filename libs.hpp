//
// Created by Price Skip on 3/30/23.
//

#ifndef FT_IRC_LIBS_HPP
#define FT_IRC_LIBS_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
//#include <netinet/in.h>
#include <fcntl.h>
#include <vector>
#include <map>


#define BUFFSIZE	4096
#define FDSSIZE		10
#define TIMEOUT		5000



void			error(const std::string &error);


#endif //FT_IRC_LIBS_HPP
