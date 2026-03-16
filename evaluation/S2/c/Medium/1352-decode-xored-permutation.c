// Source: https://leetcode.com/problems/decode-xored-permutation/   |   Difficulty: Medium
//
// Problem Description:
// There is an integer array perm that is a permutation of the first n positive integers, where n is always odd.
//
// It was encoded into another integer array encoded of length n - 1, such that encoded[i] = perm[i] XOR perm[i + 1]. For example, if perm = [1,3,2], then encoded = [2,1].
//
// Given the encoded array, return the original array perm. It is guaranteed that the answer exists and is unique.
//
// Example:
// Input: encoded = [3,1]
// Output: [1,2,3]
// Explanation: If perm = [1,2,3], then encoded = [1 XOR 2,2 XOR 3] = [3,1]
//
// Constraints:
// 3 <= n < 105
// 	n is odd.
// 	encoded.length == n - 1
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* decode(int* encoded, int encodedSize, int* returnSize) {
    int n = encodedSize + 1;
    int* perm = (int*)malloc(n * sizeof(int));
    if (!perm) {
        *returnSize = 0;
        return NULL; // Handle memory allocation failure
    }

    // Step 1: Calculate total XOR of numbers from 1 to n
    int totalXOR = 0;
    for (int i = 1; i <= n; i++) {
        totalXOR ^= i;
    }

    // Step 2: Calculate XOR of all odd indexed elements in encoded
    int oddXOR = 0;
    for (int i = 1; i < encodedSize; i += 2) {
        oddXOR ^= encoded[i];
    }

    // Step 3: The first element of perm can be found by XORing totalXOR and oddXOR
    perm[0] = totalXOR ^ oddXOR;

    // Step 4: Fill the rest of the perm array using the encoded values
    for (int i = 1; i < n; i++) {
        perm[i] = perm[i - 1] ^ encoded[i - 1];
    }

    *returnSize = n;
    return perm;        
}
