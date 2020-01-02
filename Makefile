##
## EPITECH PROJECT, 2019
## NWP_myarpspoof_2018
## File description:
## Makefile
##

DIR_CORE		=	src/

SRC_SERVER		=	$(DIR_CORE)main.c						\
					$(DIR_CORE)start.c						\
					$(DIR_CORE)log.c						\
					$(DIR_CORE)check.c						\
					$(DIR_CORE)check_options.c				\
					$(DIR_CORE)utils.c						\
					$(DIR_CORE)iface.c						\
					$(DIR_CORE)print.c						\
					$(DIR_CORE)fill.c						\
					$(DIR_CORE)send.c						\
					$(DIR_CORE)packet.c						\
					$(DIR_CORE)receive.c					\
					$(DIR_CORE)convert.c					\
					$(DIR_CORE)free.c						\

OBJ_CORE		=	$(SRC_SERVER:.c=.o)

OBJS			=	$(OBJ_CORE)

NAME_CORE		=	myARPspoof

NAMES			=	$(NAME_CORE)

CFLAGS        	+=  -W -Wall -Wextra -I./include -fsigned-char

CC			=	gcc

all: $(NAME_CORE)

$(NAME_CORE): $(OBJ_CORE)
	@printf "[\033[0;36mLinkage\033[0m] % 40s\n" $@ | tr ' ' '.'
	$(CC) -o $(NAME_CORE) $(OBJ_CORE) $(LDFLAGS)
	@printf "[\033[0;32mDone\033[0m] % 39s\n" $@ | tr ' ' '.'

%.o: %.c
	@printf "[\033[0;32mcompiled\033[0m] % 39s\n" $@ | tr ' ' '.'
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@printf "[\033[0;31mdeleted\033[0m] % 39s\n" $(OBJS) | tr ' ' '.'
	@rm -f $(OBJS)

fclean: clean
	@printf "[\033[0;31mdeleted\033[0m] % 39s\n" $(NAMES) | tr ' ' '.'
	@rm -f $(NAMES)


re: fclean all

.PHONY: all client clean fclean re

.SUFFIXES: .o .c
