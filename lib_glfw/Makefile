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
NAME			= lib_glfw.so

# dir
ROOT			= $(shell pwd)
OBJDIR			= $(ROOT)/objs
SRCDIR			= $(ROOT)/srcs
INCDIR			= $(ROOT)/includes
GLFW_LIB_DIR	= $(ROOT)/glfw

# lib compilation flags
GLFW_LIB_P		= -L $(GLFW_LIB_DIR)/src
GLFW_FRAMEWORK	= -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework GLUT

# general compilation flags
INCFLAGS		= -I $(INCDIR) -I $(GLFW_LIB_DIR)/include
CXXFLAGS		= -Wall -Wextra -Werror -std=c++11 -fPIC
LDFLAGS			= -shared
LINKING			= -lglfw3 $(GLFW_FRAMEWORK)

# source files
SRC				= LibGlfw.cpp \
				  BMPLoader.cpp \
				  Position.cpp \
				  Direction.cpp

# obj
OBJS			= $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))

.PHONY: all clean fclean re

all: $(OBJDIR) glfw/CMakeLists.txt $(NAME)

$(NAME): $(OBJS)
	@printf "$(OK_COLOR)Compiling executable...$(NO_COLOR)\n"
	$(CXX) $(LDFLAGS) $(GLFW_LIB_P) $^ -o $@ $(LINKING)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@printf "$(OK_COLOR)Compiling objects...$(NO_COLOR)\n"
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $< -o $@ -c

$(OBJDIR):
	@$(MKDIR) $@

$(BREW):
	/usr/local/bin/brew update

$(CMAKE):
	$(BREW) update
	$(BREW) install cmake

glfw/CMakeLists.txt:
	@printf "$(OK_COLOR)Submodule initialization...$(NO_COLOR)"
	$(GIT) submodule init
	$(GIT) submodule update

$(GLFW_LIB):
	cd $(GLFW_LIB_DIR) && \
	$(CMAKE) . && \
	$(MAKE) && \
	cd ..

clean:
	@printf "$(WARN_COLOR)"
	$(RM) -rf $(OBJDIR)
	@printf "$(NO_COLOR)"

fclean: clean
	@printf "$(WARN_COLOR)"
	$(RM) -f $(NAME)
	@printf "$(NO_COLOR)"

re: fclean all
