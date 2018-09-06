# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/19 15:49:46 by jmocniak          #+#    #+#              #
#    Updated: 2018/09/06 14:41:49 by jmocniak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol

SRC := main window key_hook mouse_hook julia mandelbrot burningship tricorn color threads menu error

SRCDIR := ./src/

OBJDIR := ./obj/

LIBS := -L 42-libft -lft -L libmlx -lmlx -lm -lpthread

FRAMEWORKS := -framework OpenGL -framework AppKit

FLAGS := -Wall -Werror -Wextra

CC := gcc

HEADER := fractol.h


all: $(NAME)

42-libft/libft.a:
	make -C 42-libft

libmlx/libmlx.a:
	make -C libmlx

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c $(SRCDIR)$(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR)get_next_line.o: ./42-get_next_line/get_next_line.c \
	./42-get_next_line/get_next_line.h
	$(CC) $(FLAGS) -c ./42-get_next_line/get_next_line.c -o $@

$(NAME): 42-libft/libft.a libmlx/libmlx.a $(OBJDIR) \
	$(addprefix $(OBJDIR), $(addsuffix .o, $(SRC))) $(OBJDIR)get_next_line.o
	$(CC) $(FLAGS) $(LIBS) $(FRAMEWORKS) \
		$(addprefix $(OBJDIR), $(addsuffix .o, $(SRC))) \
		$(OBJDIR)get_next_line.o -o $(NAME)

clean:
	rm -Rf $(OBJDIR)
	make -C 42-libft clean
	make -C libmlx clean

fclean: clean
	rm -f $(NAME)
	make -C 42-libft fclean

re: fclean all

.PHONY: all clean fclean re
