// Source: https://leetcode.com/problems/finding-3-digit-even-numbers/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array digits, where each element is a digit. The array may contain duplicates.
//
// You need to find all the unique integers that follow the given requirements:
//
//
// 	The integer consists of the concatenation of three elements from digits in any arbitrary order.
// 	The integer does not have leading zeros.
// 	The integer is even.
//
//
// For example, if the given digits were [1, 2, 3], integers 132 and 312 follow the requirements.
//
// Return a sorted array of the unique integers.
//
// Example:
// Input: digits = [2,1,3,0]
// Output: [102,120,130,132,210,230,302,310,312,320]
// Explanation: All the possible integers that follow the requirements are in the output array. 
// Notice that there are no odd integers or integers with leading zeros.
//
// Constraints:
// 3 <= digits.length <= 100
// 	0 <= digits[i] <= 9
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, especially for large datasets or external sorting where data might not fit in memory.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and requires O(N) auxiliary space.
//   • Invariants: The elements `index[lo...k-1]` are sorted and contain the smallest `k-lo` elements from the original `aux[lo...mid]` and `aux[mid+1...hi]` segments.; Pointer `i` always indicates the next element to consider from the left sorted sub-array (`aux[lo...mid]`).
//   • Tips: Implement the merge step carefully to ensure stability.; Consider an iterative bottom-up approach to avoid recursion overhead.
//   • Pitfalls: High auxiliary space complexity (O(N)) can be a concern for memory-constrained systems.; Recursive calls can lead to stack overflow for very large inputs without tail call optimization.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findEvenNumbers(int* digits, int digitsSize, int* returnSize) {
    int count[10];
    for (int i = 0; i < 10; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < digitsSize; i++) {
        count[digits[i]]++;
    }

    int* result = (int*)malloc(900 * sizeof(int));
    int idx = 0;

    for (int h = 1; h <= 9; h++) {
        if (count[h] == 0) continue;
        count[h]--;

        for (int t = 0; t <= 9; t += 2) {
            if (count[t] == 0) continue;
            count[t]--;

            for (int u = 0; u <= 9; u++) {
                if (count[u] == 0) continue;

                result[idx++] = h * 100 + u * 10 + t;
            }

            count[t]++;
        }

        count[h]++;
    }

    // Sort the result array
    for (int i = 0; i < idx - 1; i++) {
        for (int j = i + 1; j < idx; j++) {
            if (result[i] > result[j]) {
                int temp = result[i];
                result[i] = result[j];
                result[j] = temp;
            }
        }
    }

    *returnSize = idx;
    return result;      
}
