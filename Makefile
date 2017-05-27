
BIN			=	trade

SRCS_FILES 	= 	main.cpp \
				Trade.cpp

SRCS_PATH	= 	$(addprefix srcs/,$(SRCS_FILES))
OBJS		= 	$(SRCS_PATH:.cpp=.o)

HDR_PATH 	= 	./includes/
CXXFLAGS 		=  -I$(HDR_PATH) -W -Wall -Wextra -Werror
LIBS		= 	

CC 			= g++
RM 			= rm -rf

all			: $(BIN)

$(BIN)		: $(OBJS)
			$(CC) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean		:
			$(RM) $(OBJS)

fclean		: clean
			$(RM) $(BIN)

re 			: fclean all

.PHONY		: all clean fclean re
