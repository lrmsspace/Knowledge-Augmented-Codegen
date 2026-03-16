// Source: https://leetcode.com/problems/find-the-peaks/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array mountain. Your task is to find all the peaks in the mountain array.
//
// Return an array that consists of indices of peaks in the given array in any order.
//
// Example:
// Input: mountain = [2,4,4]
// Output: []
// Explanation: mountain[0] and mountain[2] can not be a peak because they are first and last elements of the array.
// mountain[1] also can not be a peak because it is not strictly greater than mountain[2].
// So the answer is [].
//
// Constraints:
// 3 <= mountain.length <= 100
// 	1 <= mountain[i] <= 100
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
int* findPeaks(int* mountain, int mountainSize, int* returnSize) {
    // Allocate memory for the maximum possible number of peaks
    int* peaks = (int*)malloc(mountainSize * sizeof(int));
    int count = 0;

    // Iterate through the mountain array, skipping the first and last elements
    for (int i = 1; i < mountainSize - 1; i++) {
        // Check if the current element is a peak
        if (mountain[i] > mountain[i - 1] && mountain[i] > mountain[i + 1]) {
            peaks[count++] = i; // Store the index of the peak
        }
    }

    // Set the return size to the number of peaks found
    *returnSize = count;

    // Reallocate memory to fit the number of peaks found
    peaks = (int*)realloc(peaks, count * sizeof(int));

    return peaks; // Return the array of peak indices       
}
