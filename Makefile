#nasm -f elf64 hello.s -o hello.o
#ld hello.o -o hello
#./hello

NAME = libasm.a

COMPILATOR = nasm

FLAGS = -f elf64

SRCS =	ft_strlen.s \
		ft_strcpy.s \
		ft_strcmp.s \
		ft_write.s
#		ft_read.s 
#		ft_strdup.s

# TEST = hello_world.s \
# 		ft_itoa.s \
# 		testing.s

SRCS_DIR = src/
TEST_DIR = _testing/
OBJ_DIR = obj/

SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))
# TEST_PATH = $(addprefix $(TEST_DIR), $(TEST))

OBJS_PATH = $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.s=.o)))
TEST_OBJS_PATH = $(addprefix $(OBJ_DIR), $(notdir $(TEST_PATH:.s=.o)))

all: ${NAME}

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

${NAME}: $(OBJ_DIR) $(OBJS_PATH)
		ar rc ${NAME} ${OBJS_PATH}

$(OBJ_DIR)%.o: $(SRCS_DIR)%.s
		$(COMPILATOR) ${FLAGS} -s $< -o $@

# $(OBJ_DIR)%.o: $(TEST_DIR)%.s
# 		$(COMPILATOR) ${FLAGS} -s $< -o $@

clean:
		rm -rf ${OBJ_DIR}

fclean: clean
		rm -f ${NAME}
		rm -f test
		rm -f c
		rm -f testing

re: fclean all

# test: all $(OBJ_DIR) $(TEST_OBJS_PATH)
# 		ld -o testing $(TEST_OBJS_PATH) -L. -lasm -lc --dynamic-linker /lib64/ld-linux-x86-64.so.2

test: all $(OBJ_DIR)
	gcc $(TEST_DIR)all_test.c -L. -no-pie -lasm -o test

.PHONY: all clean fclean re test
