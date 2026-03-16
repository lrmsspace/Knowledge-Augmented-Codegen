// Source: https://leetcode.com/problems/minimize-string-length/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, you have two types of operation:
//
//
// 	Choose an index i in the string, and let c be the character in position i. Delete the closest occurrence of c to the left of i (if exists).
// 	Choose an index i in the string, and let c be the character in position i. Delete the closest occurrence of c to the right of i (if exists).
//
//
// Your task is to minimize the length of s by performing the above operations zero or more times.
//
// Return an integer denoting the length of the minimized string.
//
// Example:
// Input: s = "aaabc"
//
// Output: 3
//
// Explanation:
//
//
// 	Operation 2: we choose i = 1 so c is 'a', then we remove s[2] as it is closest 'a' character to the right of s[1].
// 	s becomes "aabc" after this.
// 	Operation 1: we choose i = 1 so c is 'a', then we remove s[0] as it is closest 'a' character to the left of s[1].
// 	s becomes "abc" after this.
//
// Constraints:
// 1 <= s.length <= 100
// 	s contains only lowercase English letters
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - MEX (minimal excluded) of a sequence (ds, enumeration)
//   • When to use: Use when needing to efficiently find the smallest non-negative integer not present in a dynamic sequence or range, supporting both updates and queries in logarithmic time.
//   • Idea: This technique finds the Minimal Excluded (MEX) value in a sequence by maintaining counts of distinct elements in ranges using a specialized data structure, typically a segment tree. It supports both updates and queries in O(log N) time.
//   • Invariants: Each segment tree node accurately reflects the count of distinct numbers within its corresponding range.; If a range [L, R) contains R-L distinct numbers, then all integers from L to R-1 are present.
//   • Tips: Implement a segment tree where each node stores the count of distinct numbers in its range.; The binary search for MEX checks if a range [0, k) contains k distinct numbers to decide which child to traverse.
//   • Pitfalls: Incorrectly calculating distinct counts in segment tree nodes, especially after updates.; Off-by-one errors when comparing the number of distinct elements with the expected count for a full range.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimizedStringLength(char* s) {
    int freq[26] = {0};  // Frequency array for lowercase English letters
    int i;
    
    // Count the frequency of each character in the string
    for (i = 0; s[i] != '\0'; i++) {
        freq[s[i] - 'a']++;
    }
    
    int uniqueCount = 0;  // Count of unique characters
    for (i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            uniqueCount++;
        }
    }
    
    return uniqueCount;  // The length of the minimized string is the count of unique characters        
}
