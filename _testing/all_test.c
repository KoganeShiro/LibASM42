#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

extern size_t ft_strlen(const char *str);
extern char *ft_strcpy(char *dest, const char *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buf, size_t count);
extern ssize_t ft_read(int fd, void *buf, size_t count);
extern char *ft_strdup(const char *str);

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

// =============================================================================
// STRLEN TESTS
// =============================================================================

typedef struct {
    const char *description;
    const char *input;
    size_t expected_length;
} strlen_test_t;

void test_strlen()
{
    printf(BLUE "=== TESTING ft_strlen vs strlen ===\n" RESET);
    
    strlen_test_t tests[] = {
        {"Empty string", "", 0},
        {"Single character", "a", 1},
        {"Short word", "Hello", 5},
        {"Original test", "this is a test", 14},
        {"Just a space", " ", 1},
        {"Multiple spaces", "   ", 3},
        {"Tab and space", "\t ", 2},
        {"Length 10", "1234567890", 10},
        {"Length 26", "abcdefghijklmnopqrstuvwxyz", 26},
        {"Sentence", "The quick brown fox jumps over the lazy dog", 43},
        {"With punctuation", "Hello, World!", 13},
        {"Long string", "This is a very long string to test our implementation", 53}
    };
    
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    
    for (int i = 0; i < num_tests; i++) {
        size_t stdlib_result = strlen(tests[i].input);
        size_t ft_result = ft_strlen(tests[i].input);
        
        printf("Test %d: %s\n", i + 1, tests[i].description);
        printf("  Input: \"%s\"\n", tests[i].input);
        printf("  strlen:    %zu\n", stdlib_result);
        printf("  ft_strlen: %zu\n", ft_result);
        
        if (stdlib_result == ft_result && ft_result == tests[i].expected_length) {
            printf("  " GREEN "✓ PASS\n" RESET);
            passed++;
        } else {
            printf("  " RED "✗ FAIL\n" RESET);
        }
        printf("\n");
    }
    
    printf(YELLOW "STRLEN SUMMARY: %d/%d tests passed\n\n" RESET, passed, num_tests);
}

// =============================================================================
// STRCPY TESTS  
// =============================================================================

typedef struct {
    const char *description;
    const char *src;
    char expected_dest[100];  // Large enough for test strings
} strcpy_test_t;

void test_strcpy()
{
    printf(BLUE "=== TESTING ft_strcpy vs strcpy ===\n" RESET);
    
    strcpy_test_t tests[] = {
        {"Empty string", "", ""},
        {"Single char", "a", "a"},
        {"Short string", "Hello", "Hello"},
        {"With spaces", "Hello World", "Hello World"},
        {"Numbers", "12345", "12345"},
        {"Special chars", "!@#$%", "!@#$%"},
        {"Long string", "The quick brown fox jumps", "The quick brown fox jumps"}
    };
    
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    
    for (int i = 0; i < num_tests; i++) {
        char stdlib_dest[100] = {0};
        char ft_dest[100] = {0};        
        char *stdlib_result = strcpy(stdlib_dest, tests[i].src);
        char *ft_result = ft_strcpy(ft_dest, tests[i].src);
        
        printf("Test %d: %s\n", i + 1, tests[i].description);
        printf("  Source: \"%s\"\n", tests[i].src);
        printf("  strcpy result:    \"%s\"\n", stdlib_dest);
        printf("  ft_strcpy result: \"%s\"\n", ft_dest);
        
        // Check if results match
        int results_match = (strcmp(stdlib_dest, ft_dest) == 0);
        int expected_match = (strcmp(ft_dest, tests[i].expected_dest) == 0);
        int return_correct = (ft_result == ft_dest && stdlib_result == stdlib_dest);
        
        if (results_match && expected_match && return_correct) {
            printf("  " GREEN "✓ PASS\n" RESET);
            passed++;
        } else {
            printf("  " RED "✗ FAIL - ");
            if (!results_match) printf("results differ ");
            if (!expected_match) printf("wrong result ");
            if (!return_correct) printf("wrong return value ");
            printf("\n" RESET);
        }
        printf("\n");
    }
    
    printf(YELLOW "STRCPY SUMMARY: %d/%d tests passed\n\n" RESET, passed, num_tests);
}

// =============================================================================
// STRCMP TESTS
// =============================================================================

typedef struct {
    const char *description;
    const char *s1;
    const char *s2;
    int expected_sign;  // -1, 0, or 1 for the sign of the result
} strcmp_test_t;

void test_strcmp()
{
    printf(BLUE "=== TESTING ft_strcmp vs strcmp ===\n" RESET);
    
    strcmp_test_t tests[] = {
        {"Equal strings", "hello", "hello", 0},
        {"Empty strings", "", "", 0},
        {"First < Second", "abc", "abd", -1},
        {"First > Second", "abd", "abc", 1},
        {"Different lengths 1", "hello", "hello world", -1},
        {"Different lengths 2", "hello world", "hello", 1},
        {"Numbers", "123", "124", -1},
        {"Single chars equal", "a", "a", 0},
        {"Single chars different", "a", "b", -1}
    };
    
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    
    for (int i = 0; i < num_tests; i++) {
        int stdlib_result = strcmp(tests[i].s1, tests[i].s2);
        int ft_result = ft_strcmp(tests[i].s1, tests[i].s2);
        
        // Normalize results to -1, 0, 1
        int stdlib_sign = (stdlib_result > 0) ? 1 : (stdlib_result < 0) ? -1 : 0;
        int ft_sign = (ft_result > 0) ? 1 : (ft_result < 0) ? -1 : 0;
        
        printf("Test %d: %s\n", i + 1, tests[i].description);
        printf("  s1: \"%s\", s2: \"%s\"\n", tests[i].s1, tests[i].s2);
        printf("  strcmp result:    %d (sign: %d)\n", stdlib_result, stdlib_sign);
        printf("  ft_strcmp result: %d (sign: %d)\n", ft_result, ft_sign);
        
        if (stdlib_sign == ft_sign && ft_sign == tests[i].expected_sign) {
            printf("  " GREEN "✓ PASS\n" RESET);
            passed++;
        } else {
            printf("  " RED "✗ FAIL\n" RESET);
        }
        printf("\n");
    }
    
    printf(YELLOW "STRCMP SUMMARY: %d/%d tests passed\n\n" RESET, passed, num_tests);
}

// =============================================================================
// WRITE TESTS
// =============================================================================

void test_write()
{
    printf(BLUE "=== TESTING ft_write vs write ===\n" RESET);
    
    const char *test_msg = "Hello from write test!\n";
    int passed = 0;
    int total_tests = 3;
    
    // Test 1: Valid write to stdout
    printf("Test 1: Valid write to stdout\n");
    
    errno = 0;
    ssize_t ft_result = ft_write(1, test_msg, strlen(test_msg));
    int ft_errno = errno;
    ssize_t std_result = write(1, test_msg, strlen(test_msg));
    int std_errno = errno;
    
    printf("  ft_write returned: %zd, errno: %d\n", ft_result, ft_errno);
    printf("  write returned: %zd, errno: %d\n", std_result, std_errno);
    
    if (ft_result == std_result && ft_errno == std_errno) {
        printf("  " GREEN "✓ PASS\n" RESET);
        passed++;
    } else {
        printf("  " RED "✗ FAIL\n" RESET);
    }
    
    // Test 2: Invalid file descriptor
    printf("\nTest 2: Invalid file descriptor (-1)\n");
    errno = 0;
    ft_result = ft_write(-1, test_msg, strlen(test_msg));
    ft_errno = errno;
    std_result = write(-1, test_msg, strlen(test_msg));
    std_errno = errno;
    
    printf("  ft_write(-1) returned: %zd, errno: %d (%s)\n", 
           ft_result, ft_errno, strerror(ft_errno));
    printf("  write(-1) returned: %zd, errno: %d (%s)\n", 
           std_result, std_errno, strerror(std_errno));
    
    if (ft_result == -1 && std_result == -1 && ft_errno == std_errno) {
        printf("  " GREEN "✓ PASS\n" RESET);
        passed++;
    } else {
        printf("  " RED "✗ FAIL\n" RESET);
    }

    // Test 3: Write to a created file
    printf("\nTest 3: Write to a file\n");
    const char *filename = "test_write_file.tmp";
    
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        printf("  " RED "✗ FAIL - Could not create test file: %s\n" RESET, strerror(errno));
    } else {
        printf("  Created file '%s' with fd: %d\n", filename, fd);
        
        errno = 0;
        ft_result = ft_write(fd, test_msg, strlen(test_msg));
        ft_errno = errno;
        close(fd);
        fd = open(filename, O_WRONLY | O_TRUNC);        
        std_result = write(fd, test_msg, strlen(test_msg));
        std_errno = errno;
        
        printf("  ft_write(file) returned: %zd, errno: %d\n", ft_result, ft_errno);
        printf("  write(file) returned: %zd, errno: %d\n", std_result, std_errno);
        
        if (ft_result == std_result && ft_errno == std_errno && ft_result > 0) {
            printf("  " GREEN "✓ PASS\n" RESET);
            passed++;
        } else {
            printf("  " RED "✗ FAIL\n" RESET);
        }
        close(fd);
        unlink(filename);  // Clean up test file
    }
    printf("\n" YELLOW "WRITE SUMMARY: %d/%d tests passed\n\n" RESET, passed, total_tests);
}

// =============================================================================
// READ TESTS
// =============================================================================
void test_read()
{
    printf(BLUE "=== TESTING ft_read vs read ===\n" RESET);
    
    int passed = 0;
    int total_tests = 2;
    
    // Test 1: Invalid file descriptor (-1)
    printf("Test 1: Invalid file descriptor (-1)\n");
    char buffer1[100];
    char buffer2[100];
    
    errno = 0;
    ssize_t ft_result = ft_read(-1, buffer1, sizeof(buffer1));
    int ft_errno = errno;
    
    errno = 0;
    ssize_t std_result = read(-1, buffer2, sizeof(buffer2));
    int std_errno = errno;
    
    printf("  ft_read(-1) returned: %zd, errno: %d (%s)\n", 
           ft_result, ft_errno, strerror(ft_errno));
    printf("  read(-1) returned: %zd, errno: %d (%s)\n", 
           std_result, std_errno, strerror(std_errno));
    
    if (ft_result == -1 && std_result == -1 && ft_errno == std_errno) {
        printf("  " GREEN "✓ PASS\n" RESET);
        passed++;
    } else {
        printf("  " RED "✗ FAIL\n" RESET);
    }

    // Test 2: Successful read from file
    printf("\nTest 2: Read from file with proper content\n");
    const char *filename = "test_read_file.tmp";
    const char *test_content = "Hello World for reading!";

    int write_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (write_fd != -1) {
        write(write_fd, test_content, strlen(test_content));
        close(write_fd);
        
        // Open for reading
        int read_fd = open(filename, O_RDONLY);
        if (read_fd != -1) {
            memset(buffer1, 0, sizeof(buffer1));
            memset(buffer2, 0, sizeof(buffer2));
            
            errno = 0;
            ft_result = ft_read(read_fd, buffer1, 10);  // Read first 10 bytes
            ft_errno = errno;
            
            // Reset file position for standard read
            lseek(read_fd, 0, SEEK_SET);
            
            errno = 0;
            std_result = read(read_fd, buffer2, 10);
            std_errno = errno;
            
            printf("  ft_read returned: %zd, errno: %d\n", ft_result, ft_errno);
            printf("  ft_read content: \"%.10s\"\n", buffer1);
            printf("  read returned: %zd, errno: %d\n", std_result, std_errno);
            printf("  read content: \"%.10s\"\n", buffer2);
            
            if (ft_result == std_result && ft_errno == std_errno && 
                ft_result > 0 && memcmp(buffer1, buffer2, ft_result) == 0) {
                printf("  " GREEN "✓ PASS\n" RESET);
                passed++;
            } else {
                printf("  " RED "✗ FAIL\n" RESET);
            }
            
            close(read_fd);
        }
        unlink(filename);
    }
    
    printf("\n" YELLOW "READ SUMMARY: %d/%d tests passed\n\n" RESET, passed, total_tests);
}


// =============================================================================
// STRDUP TESTS
// =============================================================================
typedef struct {
    const char *description;
    const char *input;
} strdup_test_t;

void test_strdup()
{
    printf(BLUE "=== TESTING ft_strdup vs strdup ===\n" RESET);
    
    strdup_test_t tests[] = {
        {"Empty string", ""},
        {"Single character", "a"},
        {"Short string", "Hello"},
        {"String with space", "Hello World"},
        {"Numbers", "12345"},
        {"Special characters", "!@#$%^&*()"},
        {"Only spaces", "   "},
        {"Tab and newline", "\t\n"},
        {"Long string", "The quick brown fox jumps over the lazy dog"},
        {"Very long string", "Very long string to test memory allocation and copying"},
        {"With punctuation", "Hello, World!"},
        {"Mixed content", "Test123 with CAPS and symbols: @#$"}
    };
    
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    
    for (int i = 0; i < num_tests; i++) {
        char *stdlib_result = strdup(tests[i].input);
        char *ft_result = ft_strdup(tests[i].input);
        
        printf("Test %d: %s\n", i + 1, tests[i].description);
        printf("  Input: \"%s\"\n", tests[i].input);
        printf("  strdup result:    %s\n", stdlib_result ? stdlib_result : "NULL");
        printf("  ft_strdup result: %s\n", ft_result ? ft_result : "NULL");
        
        int results_match = 0;
        int different_string = 0;
        
        if (stdlib_result == NULL && ft_result == NULL) {
            results_match = 1;
            different_string = 1;
        } else if (stdlib_result != NULL && ft_result != NULL) {
            results_match = (strcmp(stdlib_result, ft_result) == 0);
            different_string = (ft_result != tests[i].input);
        }        
        if (results_match && different_string) {
            printf("  " GREEN "✓ PASS\n" RESET);
            passed++;
        } else {
            printf("  " RED "✗ FAIL\n" RESET);
        }
        
        if (stdlib_result) free(stdlib_result);
        if (ft_result) free(ft_result);
        
        printf("\n");
    }
    
    printf(YELLOW "STRDUP SUMMARY: %d/%d tests passed\n\n" RESET, passed, num_tests);
}


// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main(int argc, char *argv[])
{
    printf(BLUE "========================================\n");
    printf("    ASSEMBLY FUNCTIONS TEST SUITE\n");
    printf("========================================\n" RESET);
    
    if (argc == 1) {
        test_strlen();
        test_strcpy();
        test_strcmp();
        test_write();
        test_read();
        test_strdup();
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "strlen") == 0) {
            test_strlen();
        } else if (strcmp(argv[i], "strcpy") == 0) {
            test_strcpy();
        } else if (strcmp(argv[i], "strcmp") == 0) {
            test_strcmp();
        } else if (strcmp(argv[i], "write") == 0) {
            test_write();
        } else if (strcmp(argv[i], "read") == 0) {
            test_read();
        } else if (strcmp(argv[i], "strdup") == 0) {
            test_strdup();
        } else {
            printf(RED "Unknown test: %s\n" RESET, argv[i]);
            printf("Available tests: strlen, strcpy, strcmp, write, read, strdup\n");
        }
    }
    return 0;
}