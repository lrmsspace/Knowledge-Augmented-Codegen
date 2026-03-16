// Source: https://leetcode.com/problems/number-of-equivalent-domino-pairs/   |   Difficulty: Easy
//
// Problem Description:
// Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d] if and only if either (a == c and b == d), or (a == d and b == c) - that is, one domino can be rotated to be equal to another domino.
//
// Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length, and dominoes[i] is equivalent to dominoes[j].
//
// Example:
// Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
// Output: 1
//
// Constraints:
// 1 <= dominoes.length <= 4 * 104
// 	dominoes[i].length == 2
// 	1 <= dominoes[i][j] <= 9
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numEquivDominoPairs(int** dominoes, int dominoesSize, int* dominoesColSize) {
    int count[100] = {0}; // Since domino values are between 1 and 9, we can use a fixed-size array to count pairs.
    int pairs = 0;

    for (int i = 0; i < dominoesSize; i++) {
        int a = dominoes[i][0];
        int b = dominoes[i][1];
        int key = (a < b) ? (a * 10 + b) : (b * 10 + a); // Create a unique key for the domino pair.

        pairs += count[key]; // Add the number of previously seen equivalent dominoes to the pairs count.
        count[key]++; // Increment the count for this domino pair.
    }

    return pairs;       
}
