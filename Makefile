NAME = ircserv

SRCS = main.cpp \
		ft_server.cpp \
		libs.cpp

CLANG = c++

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

all:
	${CLANG} ${FLAGS} -g ${SRCS} -o ${NAME}

run:
	${CLANG} ${FLAGS} -g ${SRCS} -o ${NAME} && ./${NAME} 6667 5555

clean:
	rm -rf ${NAME}

re: clean all

PHOHY: all re clean fclean