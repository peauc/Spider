##
## Makefile for  in /home/thauvi_a/rendu/tek2/trade
##
## Made by Alexandre Thauvin
## Login   <thauvi_a@epitech.net>
##
## Started on  Mon Feb 27 11:44:29 2017 Alexandre Thauvin
## Last update Wed Apr 26 09:07:26 2017 thomas lavigne
##

DIR		= src/

NAME		= toto

SRCS		= $(DIR)test.cpp

OBJS		= $(SRCS:.cpp=.o)

GXX		= g++

RM		= rm -rf

CXXFLAGS	= -Wall -Werror -W -Wextra -Iincludes -std=c++11 -lboost_system -lboost_date_time -lboost_thread

$(NAME): $(OBJS)
	$(GXX) $(OBJS) -o $(NAME) $(CXXFLAGS)

all: $(NAME)

.c.o:
	$(GXX) $(CXXLAGS) -c $< -o $@


clean:
	$(RM) $(OBJS)
	$(RM) $(DIR)*~
	$(RM) $(DIR)*#

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:         all clean fclean re
