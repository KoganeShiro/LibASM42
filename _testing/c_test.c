#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Declare your assembly function
// This tells C that ft_strlen exists and will be linked later
extern size_t ft_strlen(const char *str);

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

// Test structure to organize our tests
typedef struct {
    const char *description;
    const char *input;
    size_t expected_length;
} test_case_t;

void print_test_header() {
    printf(BLUE "================================\n");
    printf("   ft_strlen vs strlen TEST\n");
    printf("================================\n" RESET);
}

void run_single_test(int test_num, test_case_t *test) {
    // Call the standard library strlen
    size_t stdlib_result = strlen(test->input);
    
    // Call your assembly ft_strlen
    size_t ft_result = ft_strlen(test->input);
    
    // Print test info
    printf("Test %d: %s\n", test_num, test->description);
    printf("  Input: \"%s\"\n", test->input);
    printf("  strlen result:    %zu\n", stdlib_result);
    printf("  ft_strlen result: %zu\n", ft_result);
    
    // Check if results match
    int stdlib_correct = (stdlib_result == test->expected_length);
    int ft_correct = (ft_result == test->expected_length);
    int match = (stdlib_result == ft_result);
    
    if (stdlib_correct && ft_correct && match) {
        printf("  " GREEN "✓ PASS - All results correct and match!\n" RESET);
    } else {
        printf("  " RED "✗ FAIL - ");
        if (!stdlib_correct) printf("stdlib wrong ");
        if (!ft_correct) printf("ft_strlen wrong ");
        if (!match) printf("results don't match ");
        printf("\n" RESET);
    }
    printf("\n");
}

int main() {
    print_test_header();
    
    // Define all your test cases
    test_case_t tests[] = {
        // Basic tests
        {"Empty string", "", 0},
        {"Single character", "a", 1},
        {"Short word", "Hello", 5},
        
        // Your original test string
        {"Original test", "this is a test", 14},
        
        // Edge cases
        {"Just a space", " ", 1},
        {"Multiple spaces", "   ", 3},
        {"Tab and space", "\t ", 2},
        
        // Different lengths
        {"Length 10", "1234567890", 10},
        {"Length 26", "abcdefghijklmnopqrstuvwxyz", 26},
        
        // Longer strings
        {"Sentence", "The quick brown fox jumps over the lazy dog", 43},
        {"Lorem ipsum", "Lorem ipsum dolor sit amet, consectetur adipiscing elit", 55},
        
        // Special characters
        {"With numbers", "abc123def456", 12},
        {"With punctuation", "Hello, World!", 13},
        {"With symbols", "!@#$%^&*()", 10},
        
        // Very long string
        {"Long string", "This is a very long string to test if our ft_strlen function works correctly with longer inputs that might stress test the implementation", 137}
    };
    
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    
    // Run all tests
    for (int i = 0; i < num_tests; i++) {
        run_single_test(i + 1, &tests[i]);
        
        // Check if test passed (simple check)
        size_t stdlib_result = strlen(tests[i].input);
        size_t ft_result = ft_strlen(tests[i].input);
        if (stdlib_result == ft_result && ft_result == tests[i].expected_length) {
            passed++;
        }
    }
    
    // Print summary
    printf(YELLOW "================================\n");
    printf("SUMMARY: %d/%d tests passed\n", passed, num_tests);
    if (passed == num_tests) {
        printf(GREEN "🎉 ALL TESTS PASSED!\n" RESET);
    } else {
        printf(RED "❌ Some tests failed. Check your ft_strlen implementation.\n" RESET);
    }
    printf(YELLOW "================================\n" RESET);
    
    return (passed == num_tests) ? 0 : 1;
}