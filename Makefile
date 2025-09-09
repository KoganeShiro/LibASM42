NAME = libasm.a

ASSEMBLE = nasm

FLAGS = -f elf64

SRCS =	ft_strlen.s \
		ft_strcpy.s \
		ft_strcmp.s \
		ft_write.s \
		ft_read.s  \
		ft_strdup.s


SRCS_DIR = src/
TEST_DIR = _testing/
OBJ_DIR = obj/

SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))

OBJS_PATH = $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.s=.o)))
TEST_OBJS_PATH = $(addprefix $(OBJ_DIR), $(notdir $(TEST_PATH:.s=.o)))

all: ${NAME}

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

${NAME}: $(OBJ_DIR) $(OBJS_PATH)
		ar rc ${NAME} ${OBJS_PATH}

$(OBJ_DIR)%.o: $(SRCS_DIR)%.s
		$(ASSEMBLE) ${FLAGS} -s $< -o $@

clean:
		rm -rf ${OBJ_DIR}

fclean: clean
		rm -f ${NAME}
		rm -f test

re: fclean all

test: all $(OBJ_DIR)
	gcc $(TEST_DIR)all_test.c -L. -lasm -o test

.PHONY: all clean fclean re test
