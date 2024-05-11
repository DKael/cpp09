SRCS =	main.cpp \
		RPN.cpp

OBJDIR=obj

OBJS=$(addprefix $(OBJDIR)/,$(SRCS:.cpp=.o))

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = RPN

${NAME} : ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CFLAGS) -c $< -o $@

all : ${NAME}

clean:
	rm -f ${OBJS}
	rm -rf ${OBJDIR}

fclean:
	make clean
	rm -rf ${NAME}

re: 
	make fclean
	make all

.PHONY: all clean fclean re
