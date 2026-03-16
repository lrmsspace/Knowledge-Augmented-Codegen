// Source: https://leetcode.com/problems/minimum-number-of-people-to-teach/   |   Difficulty: Medium
//
// Problem Description:
// On a social network consisting of m users and some friendships between users, two users can communicate with each other if they know a common language.
//
// You are given an integer n, an array languages, and an array friendships where:
//
//
// 	There are n languages numbered 1 through n,
// 	languages[i] is the set of languages the i​​​​​​th​​​​ user knows, and
// 	friendships[i] = [u​​​​​​i​​​, v​​​​​​i] denotes a friendship between the users u​​​​​​​​​​​i​​​​​ and vi.
//
//
// You can choose one language and teach it to some users so that all friends can communicate with each other. Return the minimum number of users you need to teach.
// Note that friendships are not transitive, meaning if x is a friend of y and y is a friend of z, this doesn't guarantee that x is a friend of z.
//
// Example:
// Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
// Output: 1
// Explanation: You can either teach user 1 the second language or user 2 the first language.
//
// Constraints:
// 2 <= n <= 500
// 	languages.length == m
// 	1 <= m <= 500
// 	1 <= languages[i].length <= n
// 	1 <= languages[i][j] <= n
// 	1 <= u​​​​​​i < v​​​​​​i <= languages.length
// 	1 <= friendships.length <= 500
// 	All tuples (u​​​​​i, v​​​​​​i) are unique
// 	languages[i] contains only unique values
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumTeachings(int n, int** languages, int languagesSize, int* languagesColSize, int** friendships, int friendshipsSize, int* friendshipsColSize) {
    // Create a 2D array to track which users know which languages
    int knows[500][501] = {0};
    for (int i = 0; i < languagesSize; i++) {
        for (int j = 0; j < languagesColSize[i]; j++) {
            knows[i][languages[i][j]] = 1;
        }
    }

    // Array to count how many users need to learn each language
    int needToLearn[501] = {0};

    // Iterate through each friendship
    for (int i = 0; i < friendshipsSize; i++) {
        int u = friendships[i][0] - 1; // Convert to 0-based index
        int v = friendships[i][1] - 1; // Convert to 0-based index

        // Check if u and v can communicate
        int canCommunicate = 0;
        for (int lang = 1; lang <= n; lang++) {
            if (knows[u][lang] && knows[v][lang]) {
                canCommunicate = 1;
                break;
            }
        }

        // If they cannot communicate, mark the languages they need to learn
        if (!canCommunicate) {
            for (int lang = 1; lang <= n; lang++) {
                if (!knows[u][lang]) {
                    needToLearn[lang]++;
                }
                if (!knows[v][lang]) {
                    needToLearn[lang]++;
                }
            }
        }
    }

    // Find the minimum number of users that need to learn a language
    int minTeachings = languagesSize; // Start with the maximum possible
    for (int lang = 1; lang <= n; lang++) {
        if (needToLearn[lang] < minTeachings) {
            minTeachings = needToLearn[lang];
        }
    }

    return minTeachings;        
}
