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
											ft_striteri.c \
											ft_strjoin.c \
											ft_strlcat.c \
											ft_strlcpy.c \
											ft_strlen.c \
											ft_strmapi.c \
											ft_strncmp.c \
											ft_strnstr.c \
											ft_strrchr.c \
											ft_strtrim.c \
											ft_substr.c \
											ft_tolower.c \
											ft_toupper.c \
											ft_strndup.c \
											ft_arraylen.c \
											ft_arrayjoin.c \
											ft_arraydup.c \
											ft_arrayadd.c}

ISFT_PATH = ./src/isft/
SRCS_ISFT = ${addprefix ${ISFT_PATH}, ft_isalnum.c \
										ft_isalpha.c \
										ft_isascii.c \
										ft_isdigit.c \
										ft_isprint.c \
										ft_isspace.c \
										ft_isenv.c \
										ft_strisdigit.c \
										ft_foundspace.c}

STRUCTFT_PATH = ./src/structft/
SRCS_STRUCTFT = ${addprefix ${STRUCTFT_PATH}, ft_lstadd_back.c \
											ft_lstadd_front.c \
											ft_lstclear.c \
											ft_lstdelone.c \
											ft_lstiter.c \
											ft_lstlast.c \
											ft_lstnew.c \
											ft_lstsize.c \
											ft_treenew.c \
											ft_treeadd_left.c \
											ft_treeadd_right.c \
											ft_treereset.c \
											ft_treeset_depth.c \
											ft_cmdnew.c \
											ft_count_pipeline.c}

MEMFT_PATH = ./src/memft/
SRCS_MEMFT = ${addprefix ${MEMFT_PATH}, ft_bzero.c \
										ft_calloc.c \
										ft_memchr.c \
										ft_memcmp.c \
										ft_memcpy.c \
										ft_memmove.c \
										ft_memset.c \
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

GNL_PATH = ./src/get_next_line/
SRCS_GNL = ${addprefix ${GNL_PATH}, get_next_line_utils.c \
									get_next_line.c}

SRCS = ${SRCS_CHARFT} ${SRCS_ISFT} ${SRCS_STRUCTFT} ${SRCS_MEMFT} ${SRCS_PUTFT} ${SRCS_PRINTF} ${SRCS_GNL}
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
	@${CC} ${CFLAGS} -I ${HEADER_PATH} -c $< -o ${<:.c=.o}
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
