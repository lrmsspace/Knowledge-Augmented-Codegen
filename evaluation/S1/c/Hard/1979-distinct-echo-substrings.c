// Source: https://leetcode.com/problems/distinct-echo-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Return the number of distinct non-empty substrings of text that can be written as the concatenation of some string with itself (i.e. it can be written as a + a where a is some string).
//
// Example:
// Input: text = "abcabcabc"
// Output: 3
// Explanation: The 3 substrings are "abcabc", "bcabca" and "cabcab".
//
// Constraints:
// 1 <= text.length <= 2000
// 	text has only lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing)
//   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
//   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
//   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
//   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
//   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int distinctEchoSubstrings(char* text) {
    int n = strlen(text);
    int mod1 = 1000000007, mod2 = 1000000009;
    int base1 = 31, base2 = 37;

    /* Precompute powers of bases */
    int p1[2001], p2[2001];
    p1[0] = 1; p2[0] = 1;
    for (int i = 1; i <= n; ++i) {
        p1[i] = (1LL * p1[i - 1] * base1) % mod1;
        p2[i] = (1LL * p2[i - 1] * base2) % mod2;
    }

    /* Precompute prefix hashes */
    int h1[2001], h2[2001];
    h1[0] = 0; h2[0] = 0;
    for (int i = 0; i < n; ++i) {
        h1[i + 1] = ( (1LL * h1[i] * base1) % mod1 + (text[i] - 'a' + 1) ) % mod1;
        h2[i + 1] = ( (1LL * h2[i] * base2) % mod2 + (text[i] - 'a' + 1) ) % mod2;
    }

    /* Hash set for distinct echo substrings */
    #define HASH_SIZE 100003
    typedef struct HashNode {
        int hash1;
        int hash2;
        struct HashNode* next;
    } HashNode;

    HashNode* hashTable[HASH_SIZE];
    memset(hashTable, 0, sizeof(hashTable));

    int distinctCount = 0;

    /* Check all substrings of even length */
    for (int len = 2; len <= n; len += 2) {
        for (int start = 0; start <= n - len; ++start) {
            int mid = start + len / 2;
            int end = start + len;

            /* Compute hashes for the two halves */
            int hash1_first = (h1[mid] - (1LL * h1[start] * p1[len / 2]) % mod1 + mod1) % mod1;
            int hash1_second = (h1[end] - (1LL * h1[mid] * p1[len / 2]) % mod1 + mod1) % mod1;

            int hash2_first = (h2[mid] - (1LL * h2[start] * p2[len / 2]) % mod2 + mod2) % mod2;
            int hash2_second = (h2[end] - (1LL * h2[mid] * p2[len / 2]) % mod2 + mod2) % mod2;

            /* If hashes match, we found an echo substring */
            if (hash1_first == hash1_second && hash2_first == hash2_second) {
                int combinedHash1 = hash1_first;
                int combinedHash2 = hash2_first;
                int hashIndex = (combinedHash1 ^ combinedHash2) % HASH_SIZE;

                /* Check for duplicates in the hash table */
                HashNode* node = hashTable[hashIndex];
                int found = 0;
                while (node) {
                    if (node->hash1 == combinedHash1 && node->hash2 == combinedHash2) {
                        found = 1;
                        break;
                    }
                    node = node->next;
                }

                if (!found) {
                    /* Insert new hash into the table */
                    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
                    newNode->hash1 = combinedHash1;
                    newNode->hash2 = combinedHash2;
                    newNode->next = hashTable[hashIndex];
                    hashTable[hashIndex] = newNode;
                    distinctCount++;
                }
            }
        }
    }
    return distinctCount;
}
