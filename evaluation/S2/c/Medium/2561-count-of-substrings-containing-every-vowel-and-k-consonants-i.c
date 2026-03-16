// Source: https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word and a non-negative integer k.
//
// Return the total number of substrings of word that contain every vowel ('a', 'e', 'i', 'o', and 'u') at least once and exactly k consonants.
//
// Example:
// Input: word = "aeioqq", k = 1
//
// Output: 0
//
// Explanation:
//
// There is no substring with every vowel.
//
// Constraints:
// 5 <= word.length <= 250
// 	word consists only of lowercase English letters.
// 	0 <= k <= word.length - 5
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countOfSubstrings(char* word, int k) {
    int n = strlen(word);
    int count = 0;

    // Helper function to check if a substring contains all vowels and exactly k consonants
    int isValidSubstring(char* str, int start, int end, int k) {
        int vowelCount[5] = {0}; // a, e, i, o, u
        int consonantCount = 0;

        for (int i = start; i <= end; i++) {
            char c = str[i];
            if (c == 'a') vowelCount[0]++;
            else if (c == 'e') vowelCount[1]++;
            else if (c == 'i') vowelCount[2]++;
            else if (c == 'o') vowelCount[3]++;
            else if (c == 'u') vowelCount[4]++;
            else consonantCount++;
        }

        // Check if all vowels are present at least once
        for (int i = 0; i < 5; i++) {
            if (vowelCount[i] == 0) return 0; // Not valid if any vowel is missing
        }

        // Check if the number of consonants is exactly k
        return consonantCount == k;
    }

    // Iterate through all possible substrings of the word
    for (int start = 0; start < n; start++) {
        for (int end = start + 4; end < n; end++) { // Minimum length of substring is 5 to contain all vowels
            if (isValidSubstring(word, start, end, k)) {
                count++;
            }
        }
    }

    return count;       
}
