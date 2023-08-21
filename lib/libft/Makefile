# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 18:40:57 by hanmpark          #+#    #+#              #
#    Updated: 2023/08/19 22:30:43 by hanmpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------- COLORS ---------------------------------- #
DEF = \033[0m
BOLD = \033[1m
CUR = \033[3m
UL = \033[4m
UP = \033[A

ORANGE = \033[38;5;216m
LBLUE = \033[38;5;153m
LYELLOW = \033[38;5;222m
BEIGE = \033[38;5;223m
LGREEN = \033[38;5;155m

# ------------------------------ LIBFT SOURCES ------------------------------- #

CHARFT_PATH = ./src/charft/
SRCS_CHARFT = ${addprefix ${CHARFT_PATH}, ft_atoi.c \
											ft_itoa.c \
											ft_split.c \
											ft_strchr.c \
											ft_strdup.c \
											ft_strjoin.c \
											ft_strlen.c \
											ft_strncmp.c \
											ft_strcmp.c \
											ft_strnstr.c \
											ft_strrchr.c \
											ft_substr.c \
											ft_strndup.c \
											ft_arraylen.c \
											ft_arrayjoin.c \
											ft_arraydup.c \
											ft_arrayadd.c \
											ft_arraynew.c}

ISFT_PATH = ./src/isft/
SRCS_ISFT = ${addprefix ${ISFT_PATH}, ft_isalnum.c \
										ft_isalpha.c \
										ft_isdigit.c \
										ft_isspace.c \
										ft_isenv.c \
										ft_strisdigit.c \
										ft_isddot.c}

STRUCTFT_PATH = ./src/structft/
SRCS_STRUCTFT = ${addprefix ${STRUCTFT_PATH}, ft_tokadd_back.c \
											ft_tokadd_front.c \
											ft_toklast.c \
											ft_toknew.c \
											ft_treenew.c \
											ft_treeadd_left.c \
											ft_treeadd_right.c \
											ft_treereset.c \
											ft_treeset_cycles.c \
											ft_cmdnew.c \
											ft_countpipe.c}

MEMFT_PATH = ./src/memft/
SRCS_MEMFT = ${addprefix ${MEMFT_PATH}, ft_bzero.c \
										ft_calloc.c \
										ft_memcpy.c \
										ft_arrayfree.c}

PUTFT_PATH = ./src/putft/
SRCS_PUTFT = ${addprefix ${PUTFT_PATH}, ft_putchar_fd.c \
										ft_putendl_fd.c \
										ft_putnbr_fd.c \
										ft_putstr_fd.c}

PRINTF_PATH = ./src/ft_printf/
SRCS_PRINTF = ${addprefix ${PRINTF_PATH}, def_flags.c \
											format_hexa.c \
											ft_printf.c \
											print_basic.c \
											print_hexa.c \
											specifier_filter.c \
											treat_charflags.c \
											treat_intflags.c}

SRCS = ${SRCS_CHARFT} ${SRCS_ISFT} ${SRCS_STRUCTFT} ${SRCS_MEMFT} ${SRCS_PUTFT} ${SRCS_PRINTF}
OBJS = ${SRCS:.c=.o}

# --------------------------------- COMPILER --------------------------------- #
CC = gcc
CFLAGS = -Wall -Wextra -Werror
HEADER_PATH = ./inc/

SRCS_COUNT = 0
SRCS_TOT = ${shell find ./src/ -type f -name '*.c' | wc -l}
SRCS_PRCT = ${shell expr 100 \* ${SRCS_COUNT} / ${SRCS_TOT}}
BAR = ${shell expr 23 \* ${SRCS_COUNT} / ${SRCS_TOT}}

%.o:%.c ${HEADER_PATH}
	@${eval SRCS_COUNT = ${shell expr ${SRCS_COUNT} + 1}}
	@${CC} ${CFLAGS} -I${HEADER_PATH} -c $< -o ${<:.c=.o}
	@echo " ${BOLD}${CUR}${BEIGE}-> Compiling ${DEF}${BOLD}${LYELLOW}[LIBFT]${DEF}"
	@printf " ${BEIGE}   [${LGREEN}%-23.${BAR}s${BEIGE}] [%d/%d (%d%%)]${DEF}" "***********************" ${SRCS_COUNT} ${SRCS_TOT} ${SRCS_PRCT}
	@echo "${UP}${UP}"

# ---------------------------------- RULES ----------------------------------- #
NAME = libft.a

all: ${NAME}

${NAME}: ${OBJS}
	@ar rcs ${NAME} ${OBJS}

clean:
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
