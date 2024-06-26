# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonshin <yonshin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 20:46:00 by yonshin           #+#    #+#              #
#    Updated: 2023/01/06 13:30:07 by yonshin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
ifeq ($(CFLAGS),)
CFLAGS = -Wall -Wextra -Werror
endif
OBJS = pipex.o str_split.o

all: $(NAME) 

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(DEBUG) $(OUTPUT_OPTION) -framework OpenGL -framework AppKit 

%.o: %.c
	$(CC) $(CFLAGS) $(OUTPUT_OPTION) $(INCLUDE) $(DEBUG) -c $*.c

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: 
	make fclean
	make all

debug:
	CFLAGS='-Wall -Wextra' make DEBUG='-g3 -fsanitize=address'

test:
	make debug
	./pipex note.txt /bin/cat /bin/cat test.txt

.PHONY : all clean fclean re debug test
