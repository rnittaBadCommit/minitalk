NAME1=server
NAME2=client
CFLAG=-Wall -Wextra -Werror
UTILS=./srcs/error.c ./srcs/coder.c 
SRCS1=./srcs/server.c
SRCS2=./srcs/client.c
OBJS1=$(SRCS1:.c=.o) $(UTILS:.c=.o)
OBJS2=$(SRCS2:.c=.o) $(UTILS:.c=.o)

all: $(NAME1) $(NAME2)

%.o: %.c
	gcc $(CFLAG) -c $< -o $@

$(NAME1): $(OBJS1)
	gcc $(CFLAG) -o $(NAME1) $(OBJS1) 

$(NAME2): $(OBJS2)
	gcc $(CFLAG) -o $(NAME2) $(OBJS2)

clean:
	rm -f $(OBJS1) $(OBJS2)

fclean: clean
	rm -f $(NAME1) $(NAME2)

re: fclean all

.PHONY: clean fclean re
