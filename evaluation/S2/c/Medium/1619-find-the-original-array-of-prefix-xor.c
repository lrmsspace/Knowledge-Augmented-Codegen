// Source: https://leetcode.com/problems/find-the-original-array-of-prefix-xor/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array pref of size n. Find and return the array arr of size n that satisfies:
//
//
// 	pref[i] = arr[0] ^ arr[1] ^ ... ^ arr[i].
//
//
// Note that ^ denotes the bitwise-xor operation.
//
// It can be proven that the answer is unique.
//
// Example:
// Input: pref = [5,2,0,3,1]
// Output: [5,7,2,3,2]
// Explanation: From the array [5,7,2,3,2] we have the following:
// - pref[0] = 5.
// - pref[1] = 5 ^ 7 = 2.
// - pref[2] = 5 ^ 7 ^ 2 = 0.
// - pref[3] = 5 ^ 7 ^ 2 ^ 3 = 3.
// - pref[4] = 5 ^ 7 ^ 2 ^ 3 ^ 2 = 1.
//
// Constraints:
// 1 <= pref.length <= 105
// 	0 <= pref[i] <= 106
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
int* findArray(int* pref, int prefSize, int* returnSize) {
    int* arr = (int*)malloc(prefSize * sizeof(int));
    if (!arr) {
        *returnSize = 0;
        return NULL; // Allocation failed
    }

    arr[0] = pref[0]; // The first element of arr is the same as the first element of pref
    for (int i = 1; i < prefSize; i++) {
        arr[i] = pref[i] ^ pref[i - 1]; // Calculate arr[i] using the prefix XOR values
    }

    *returnSize = prefSize; // Set the return size to the size of the input array
    return arr; // Return the original array        
}
