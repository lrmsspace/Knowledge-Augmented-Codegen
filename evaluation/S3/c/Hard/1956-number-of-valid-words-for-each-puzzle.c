// Source: https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// With respect to a given puzzle string, a word is valid if both the following conditions are satisfied:
//
// 	word contains the first letter of puzzle.
// 	For each letter in word, that letter is in puzzle.
// 	
// 		For example, if the puzzle is "abcdefg", then valid words are "faced", "cabbage", and "baggage", while
// 		invalid words are "beefed" (does not include 'a') and "based" (includes 's' which is not in the puzzle).
// 	
// 	
//
// Return an array answer, where answer[i] is the number of words in the given word list words that is valid with respect to the puzzle puzzles[i].
//
// Example:
// Input: words = ["aaaa","asas","able","ability","actt","actor","access"], puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
// Output: [1,1,3,2,4,0]
// Explanation: 
// 1 valid word for "aboveyz" : "aaaa" 
// 1 valid word for "abrodyz" : "aaaa"
// 3 valid words for "abslute" : "aaaa", "asas", "able"
// 2 valid words for "absoryz" : "aaaa", "asas"
// 4 valid words for "actresz" : "aaaa", "asas", "actt", "access"
// There are no valid words for "gaswxyz" cause none of the words in the list contains letter 'g'.
//
// Constraints:
// 1 <= words.length <= 105
// 	4 <= words[i].length <= 50
// 	1 <= puzzles.length <= 104
// 	puzzles[i].length == 7
// 	words[i] and puzzles[i] consist of lowercase English letters.
// 	Each puzzles[i] does not contain repeated characters.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Bit manipulation (number, enumeration, simulation)
//   • When to use: When problems involve manipulating individual bits of numbers, representing sets as bitmasks, or optimizing operations on powers of two. It is also useful for certain combinatorics and dynamic programming problems.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators. This technique is often used to optimize computations, manage boolean flags efficiently, or represent subsets, typically achieving O(1) complexity for fixed-size integers.
//   • Invariants: Each bit in the mask accurately reflects the inclusion or exclusion status of its corresponding element.; Bitwise operations maintain the integrity of unaffected bits.
//   • Tips: Use (1 << k) to create a mask with the k-th bit set.; n & (n-1) clears the least significant set bit.
//   • Pitfalls: Incorrect operator precedence can lead to subtle bugs.; Mixing signed and unsigned integers in bitwise operations can yield unexpected results.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findNumOfValidWords(char** words, int wordsSize, char** puzzles, int puzzlesSize, int* returnSize) {
    // Step 1: Create a frequency map for the words based on their unique character sets.
    // We will represent each word as a bitmask of its characters.
    int wordMasks[wordsSize];
    int wordCount = 0;
    for (int i = 0; i < wordsSize; i++) {
        int mask = 0;
        for (char* p = words[i]; *p; p++) {
            mask |= 1 << (*p - 'a');
        }
        // Only consider words with at most 7 unique characters (since puzzles have 7 unique characters).
        if (__builtin_popcount(mask) <= 7) {
            wordMasks[wordCount++] = mask;
        }
    }

    // Step 2: For each puzzle, calculate the number of valid words.
    int* result = (int*)malloc(puzzlesSize * sizeof(int));
    for (int i = 0; i < puzzlesSize; i++) {
        int count = 0;
        int puzzleMask = 0;
        for (char* p = puzzles[i]; *p; p++) {
            puzzleMask |= 1 << (*p - 'a');
        }
        int firstCharMask = 1 << (puzzles[i][0] - 'a');

        // Check each word against the current puzzle.
        for (int j = 0; j < wordCount; j++) {
            // A word is valid if it contains the first letter of the puzzle and is a subset of the puzzle's character set.
            if ((wordMasks[j] & firstCharMask) && (wordMasks[j] & ~puzzleMask) == 0) {
                count++;
            }
        }
        result[i] = count;
    }

    *returnSize = puzzlesSize;
    return result;      
}
