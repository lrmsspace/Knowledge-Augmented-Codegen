// Source: https://leetcode.com/problems/pyramid-transition-matrix/   |   Difficulty: Medium
//
// Problem Description:
// You are stacking blocks to form a pyramid. Each block has a color, which is represented by a single letter. Each row of blocks contains one less block than the row beneath it and is centered on top.
//
// To make the pyramid aesthetically pleasing, there are only specific triangular patterns that are allowed. A triangular pattern consists of a single block stacked on top of two blocks. The patterns are given as a list of three-letter strings allowed, where the first two characters of a pattern represent the left and right bottom blocks respectively, and the third character is the top block.
//
//
// 	For example, "ABC" represents a triangular pattern with a 'C' block stacked on top of an 'A' (left) and 'B' (right) block. Note that this is different from "BAC" where 'B' is on the left bottom and 'A' is on the right bottom.
//
//
// You start with a bottom row of blocks bottom, given as a single string, that you must use as the base of the pyramid.
//
// Given bottom and allowed, return true if you can build the pyramid all the way to the top such that every triangular pattern in the pyramid is in allowed, or false otherwise.
//
// Example:
// Input: bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]
// Output: true
// Explanation: The allowed triangular patterns are shown on the right.
// Starting from the bottom (level 3), we can build "CE" on level 2 and then build "A" on level 1.
// There are three triangular patterns in the pyramid, which are "BCC", "CDE", and "CEA". All are allowed.
//
// Constraints:
// 2 <= bottom.length <= 6
// 	0 <= allowed.length <= 216
// 	allowed[i].length == 3
// 	The letters in all input strings are from the set {'A', 'B', 'C', 'D', 'E', 'F'}.
// 	All the values of allowed are unique.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - String Hashing (string, array, hashing)
//   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
//   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
//   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
//   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
//   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to efficiently compare strings or substrings, especially in scenarios involving large texts or numerous comparisons. It's also useful for pattern matching and detecting duplicates in collections of strings.
//   • Idea: String hashing converts a string into a numerical value (hash) to enable fast comparisons and lookups. This technique typically uses polynomial hashing with a base and a modulus, offering O(L) for initial hash computation and O(1) for substring hashes after O(N) precomputation.
//   • Invariants: The hash of a string S of length L is (S[0]*P^(L-1) + S[1]*P^(L-2) + ... + S[L-1]*P^0) % M.; For any substring S[i...j], its hash can be derived from precomputed prefix hashes in O(1) time.
//   • Tips: Use multiple hash functions with different bases and moduli to reduce collision probability.; Choose a large prime modulus (e.g., 10^9 + 7) and a random base for robustness.
//   • Pitfalls: Hash collisions are possible; always verify equality for critical applications or use multiple hashes.; Choosing a small or non-prime modulus significantly increases the risk of collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool pyramidTransition(char* bottom, char** allowed, int allowedSize) {
    // Step 1: Create a mapping of allowed patterns
    char* map[6][6]; // Since we have 6 possible colors (A-F)
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            map[i][j] = NULL; // Initialize all to NULL
        }
    }

    // Fill the mapping based on allowed patterns
    for (int i = 0; i < allowedSize; i++) {
        char* pattern = allowed[i];
        int left = pattern[0] - 'A';
        int right = pattern[1] - 'A';
        char top = pattern[2];

        if (map[left][right] == NULL) {
            map[left][right] = malloc(7 * sizeof(char)); // Allocate space for up to 6 chars + null terminator
            map[left][right][0] = '\0'; // Initialize as empty string
        }
        strncat(map[left][right], &top, 1); // Append the top character to the mapping
    }

    // Step 2: Recursive function to check if we can build the pyramid
    bool canBuildPyramid(char* current) {
        int len = strlen(current);
        if (len == 1) return true; // Reached the top of the pyramid

        char nextLevel[7]; // Next level can have at most 6 blocks + null terminator
        nextLevel[0] = '\0'; // Initialize as empty string

        for (int i = 0; i < len - 1; i++) {
            int left = current[i] - 'A';
            int right = current[i + 1] - 'A';

            if (map[left][right] == NULL) {
                return false; // No allowed pattern for this pair
            }

            strcat(nextLevel, map[left][right]); // Append all possible tops for this pair
        }

        return canBuildPyramid(nextLevel); // Recur with the next level
    }

    bool result = canBuildPyramid(bottom);

    // Free allocated memory for the mapping
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (map[i][j] != NULL) {
                free(map[i][j]);
            }
        }
    }
    return result;
}
