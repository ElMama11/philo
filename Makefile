# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/20 14:44:07 by mverger           #+#    #+#              #
#    Updated: 2022/07/24 17:25:56 by mverger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
GCCF = gcc -g #-Wall -Werror -Wextra
GREEN       = \033[32m
RED         = \033[31m
DEFAULT     = \033[37m
PATHOBJ = obj/
PATHSRC = src/
INCLUDE_PATH=include
#DEP = Makefile src/$(INCLUDE_PATH)/philo.h
#SRC =   	main.c func_libft.c parsing.c init_philo.c init_struct.c init_forks.c philo_utils.c

DEP = Makefile src/$(INCLUDE_PATH)/philo2.h
SRC =   	toto.c toto_init.c toto_parsing.c toto_time.c toto_actions.c

HEAD = -I ./src/$(INCLUDE_PATH)/
OBJ = $(patsubst %.c,$(PATHOBJ)/%.o,$(SRC))

ifeq ($(shell uname),Darwin)
    ECHO    = echo
else
	ECHO    = echo
endif

all: $(NAME)

$(PATHOBJ):
	@mkdir -p obj
	
$(NAME): $(DEP) $(addprefix $(PATHSRC)/,$(SRC)) $(PATHOBJ) $(OBJ) 
	@$(ECHO) "\r$(GREEN) The .o from $(NAME) are compiled.$(DEFAULT)"
	@$(GCCF) $(OBJ) -o $(NAME) -lpthread
	@$(ECHO) "$(GREEN)$(NAME)$(DEFAULT) created."

$(PATHOBJ)/%.o: $(PATHSRC)/%.c $(DEP)
	@$(ECHO) "\r$(GREEN) Compiling $@                      \c\033[K"
	@$(GCCF) -c $< -o $@ $(HEAD)

clean:
	@$(ECHO) "All $(RED).o$(DEFAULT) are now deleted for $(NAME)."
	@rm -rf $(PATHOBJ)

fclean: clean
	@$(ECHO) "$(RED)$(NAME)$(DEFAULT) is now deleted."
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re