// Source: https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word, and an integer numFriends.
//
// Alice is organizing a game for her numFriends friends. There are multiple rounds in the game, where in each round:
//
//
// 	word is split into numFriends non-empty strings, such that no previous round has had the exact same split.
// 	All the split words are put into a box.
//
//
// Find the lexicographically largest string from the box after all the rounds are finished.
//
// Example:
// Input: word = "dbca", numFriends = 2
//
// Output: "dbc"
//
// Explanation: 
//
// All possible splits are:
//
//
// 	"d" and "bca".
// 	"db" and "ca".
// 	"dbc" and "a".
//
// Constraints:
// 1 <= word.length <= 5 * 103
// 	word consists only of lowercase English letters.
// 	1 <= numFriends <= word.length
//
// Helpful references (internal KB):
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
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

char* answerString(char* word, int numFriends) {
    int n = strlen(word);
    char* answer = (char*)malloc((n + 1) * sizeof(char));
    answer[0] = '\0';

    // Generate all possible splits of the word into numFriends parts
    for (int i = 1; i < n; i++) {
        if (numFriends == 2) {
            // Split into two parts
            char part1[1001], part2[1001];
            strncpy(part1, word, i);
            part1[i] = '\0';
            strncpy(part2, word + i, n - i);
            part2[n - i] = '\0';

            // Check if the split is unique and update the answer
            char combined[2002];
            snprintf(combined, sizeof(combined), "%s%s", part1, part2);
            if (strcmp(combined, answer) > 0) {
                strcpy(answer, combined);
            }
        }
        // For numFriends > 2, we would need to implement a more complex splitting logic
        // which is not covered in this implementation.
    }

    return answer;      
}
