NAME = ircserv

SRCS = main.cpp \
		Ft_server.cpp  User.cpp\
		libs.cpp Command.cpp Channel.cpp

CLANG = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

RM = rm -rf

all:
	${CLANG}  -g ${SRCS} -o ${NAME}

run:
	${CLANG}  -g ${SRCS} -o ${NAME} && ./${NAME} 6667 5555

clean:
	rm -rf ${NAME}

re: clean all

PHOHY: all re clean fclean