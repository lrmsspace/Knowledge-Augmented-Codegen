// Source: https://leetcode.com/problems/odd-string-difference/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of equal-length strings words. Assume that the length of each string is n.
//
// Each string words[i] can be converted into a difference integer array difference[i] of length n - 1 where difference[i][j] = words[i][j+1] - words[i][j] where 0 <= j <= n - 2. Note that the difference between two letters is the difference between their positions in the alphabet i.e. the position of 'a' is 0, 'b' is 1, and 'z' is 25.
//
//
// 	For example, for the string "acb", the difference integer array is [2 - 0, 1 - 2] = [2, -1].
//
//
// All the strings in words have the same difference integer array, except one. You should find that string.
//
// Return the string in words that has different difference integer array.
//
// Example:
// Input: words = ["adc","wzy","abc"]
// Output: "abc"
// Explanation: 
// - The difference integer array of "adc" is [3 - 0, 2 - 3] = [3, -1].
// - The difference integer array of "wzy" is [25 - 22, 24 - 25]= [3, -1].
// - The difference integer array of "abc" is [1 - 0, 2 - 1] = [1, 1]. 
// The odd array out is [1, 1], so we return the corresponding string, "abc".
//
// Constraints:
// 3 <= words.length <= 100
// 	n == words[i].length
// 	2 <= n <= 20
// 	words[i] consists of lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing)
//   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
//   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
//   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
//   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
//   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* oddString(char** words, int wordsSize) {
    int n = strlen(words[0]);
    int diff[wordsSize][n - 1];
    
    // Compute the difference array for each word
    for (int i = 0; i < wordsSize; i++) {
        for (int j = 0; j < n - 1; j++) {
            diff[i][j] = words[i][j + 1] - words[i][j];
        }
    }
    
    // Compare the difference arrays to find the odd one out
    for (int i = 0; i < wordsSize; i++) {
        int count = 0;
        for (int j = 0; j < wordsSize; j++) {
            if (i != j) {
                int match = 1;
                for (int k = 0; k < n - 1; k++) {
                    if (diff[i][k] != diff[j][k]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    count++;
                }
            }
        }
        if (count == wordsSize - 2) { // Found the odd one out
            return words[i];
        }
    }
    
    return NULL; // Should never reach here as per problem constraints      
}
