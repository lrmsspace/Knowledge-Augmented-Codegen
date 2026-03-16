// Source: https://leetcode.com/problems/capitalize-the-title/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string title consisting of one or more words separated by a single space, where each word consists of English letters. Capitalize the string by changing the capitalization of each word such that:
//
//
// 	If the length of the word is 1 or 2 letters, change all letters to lowercase.
// 	Otherwise, change the first letter to uppercase and the remaining letters to lowercase.
//
//
// Return the capitalized title.
//
// Example:
// Input: title = "capiTalIze tHe titLe"
// Output: "Capitalize The Title"
// Explanation:
// Since all the words have a length of at least 3, the first letter of each word is uppercase, and the remaining letters are lowercase.
//
// Constraints:
// 1 <= title.length <= 100
// 	title consists of words separated by a single space without any leading or trailing spaces.
// 	Each word consists of uppercase and lowercase English letters and is non-empty.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
// - Integer factorization (number, enumeration)
//   • When to use: Use when needing to decompose a composite integer into its prime factors, especially for numbers where trial division is feasible. It's suitable for problems requiring the unique prime components of a number.
//   • Idea: Integer factorization decomposes a given composite number into a product of its prime factors. The most common approach, trial division, involves testing divisibility by prime numbers up to the square root of the number, with optimizations for small primes and patterns like modulo 6.
//   • Invariants: The product of found prime factors multiplied by the current number equals the original number.; All prime factors found so far are less than or equal to the current trial divisor.
//   • Tips: Handle small prime factors (2, 3, 5) separately for efficiency.; Optimize trial division by checking only primes or numbers of form 6k +/- 1.
//   • Pitfalls: Forgetting to handle the case where the remaining number is a prime factor itself.; Inefficiently checking all numbers instead of only potential prime divisors.
// - Shell Sort (array, shell-sort, heap-select)
//   • When to use: Use Shell Sort for medium to large-sized datasets as an efficient alternative to insertion sort, especially when minimizing call stack overhead or avoiding deep recursion is a concern.
//   • Idea: Shell Sort is an in-place comparison sort that improves upon insertion sort by sorting elements far apart, then gradually reducing the gap between elements to be compared. It typically has an average time complexity of O(N^1.25) and a space complexity of O(1).
//   • Invariants: The `temp` variable holds the element originally at `arr[i]` which is being inserted into its correct gapped-sorted position.; For the current `gap`, elements at indices `j`, `j + gap`, `j + 2*gap`, ... up to `i - gap` are sorted relative to each other.
//   • Tips: Choose an effective gap sequence for optimal performance, as it significantly impacts efficiency.; Consider it for medium to large datasets where its O(1) space complexity is beneficial.
//   • Pitfalls: Worst-case time complexity can be O(N^2) depending on the chosen gap sequence.; Performance is highly dependent on the specific gap sequence used, making optimal selection complex.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* capitalizeTitle(char* title) {
    char* p = title;
    while (*p) {
        // Skip leading spaces
        while (*p == ' ') {
            p++;
        }
        if (*p == '\0') {
            break; // End of string
        }

        // Start of a word
        char* word_start = p;
        int word_length = 0;

        // Calculate the length of the current word
        while (*p && *p != ' ') {
            word_length++;
            p++;
        }

        // Capitalize the word based on its length
        if (word_length <= 2) {
            // Convert to lowercase
            for (int i = 0; i < word_length; i++) {
                if (word_start[i] >= 'A' && word_start[i] <= 'Z') {
                    word_start[i] += ('a' - 'A'); // Convert to lowercase
                }
            }
        } else {
            // Convert first letter to uppercase and the rest to lowercase
            if (word_start[0] >= 'a' && word_start[0] <= 'z') {
                word_start[0] -= ('a' - 'A'); // Convert first letter to uppercase
            }
            for (int i = 1; i < word_length; i++) {
                if (word_start[i] >= 'A' && word_start[i] <= 'Z') {
                    word_start[i] += ('a' - 'A'); // Convert to lowercase
                }
            }
        }
    }
    return title;       
}
