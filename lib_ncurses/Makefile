# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/16 14:58:49 by tdieumeg          #+#    #+#              #
#    Updated: 2015/10/20 17:56:23 by tdieumeg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# binaries
CXX				= /usr/bin/g++
RM				= /bin/rm
MAKE			= /usr/bin/make
MKDIR			= /bin/mkdir
GIT				= /usr/bin/git
CMAKE			= $(HOME)/.brew/bin/cmake
BREW			= $(HOME)/.brew/bin/brew

# colors
NO_COLOR		= \x1b[0m
OK_COLOR		= \x1b[32;01m
WARN_COLOR		= \x1b[33;01m

# app name
NAME			= lib_ncurses.so

# dir
ROOT			= $(shell pwd)
OBJDIR			= $(ROOT)/objs
SRCDIR			= $(ROOT)/srcs
PARENT_SRCDIR	= $(ROOT)/../srcs
INCDIR			= $(ROOT)/includes
PARENT_INCDIR	= $(ROOT)/../srcs

# lib compilation flags
NCURSES_LIB_P	= -lncurses

# general compilation flags
INCFLAGS		= -I $(INCDIR) -I $(PARENT_INCDIR)
CXXFLAGS		= -Wall -Wextra -Werror -std=c++11 -fPIC

# source files
SRC				= LibNcurses.cpp

# obj
OBJS			= $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))

.PHONY: all clean fclean re

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	@printf "$(OK_COLOR)Compiling executable...$(NO_COLOR)\n"
	@$(CXX) -shared $^ -o $@ $(NCURSES_LIB_P) $(PARENT_SRCDIR)/Position.cpp $(PARENT_SRCDIR)/Direction.cpp

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@printf "$(OK_COLOR)Compiling objects...$(NO_COLOR)\n"
	@$(CXX) $< -o $@ -c $(INCFLAGS) $(CXXFLAGS)

$(OBJDIR):
	@$(MKDIR) $@

clean:
	@printf "$(WARN_COLOR)"
	$(RM) -rf $(OBJDIR)
	@printf "$(NO_COLOR)"

fclean: clean
	@printf "$(WARN_COLOR)"
	$(RM) -f $(NAME)
	@printf "$(NO_COLOR)"

re: fclean all
