// Source: https://leetcode.com/problems/make-k-subarray-sums-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array arr and an integer k. The array arr is circular. In other words, the first element of the array is the next element of the last element, and the last element of the array is the previous element of the first element.
//
// You can do the following operation any number of times:
//
//
// 	Pick any element from arr and increase or decrease it by 1.
//
//
// Return the minimum number of operations such that the sum of each subarray of length k is equal.
//
// A subarray is a contiguous part of the array.
//
// Example:
// Input: arr = [1,4,1,3], k = 2
// Output: 1
// Explanation: we can do one operation on index 1 to make its value equal to 3.
// The array after the operation is [1,3,1,3]
// - Subarray starts at index 0 is [1, 3], and its sum is 4 
// - Subarray starts at index 1 is [3, 1], and its sum is 4 
// - Subarray starts at index 2 is [1, 3], and its sum is 4 
// - Subarray starts at index 3 is [3, 1], and its sum is 4
//
// Constraints:
// 1 <= k <= arr.length <= 105
// 	1 <= arr[i] <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long makeSubKSumEqual(int* arr, int arrSize, int k) {
    long long result = 0;
    int groupCount = 0;
    int* groupSizes = (int*)calloc(k, sizeof(int));
    int** groups = (int**)calloc(k, sizeof(int*));
    
    for (int i = 0; i < k; i++) {
        groups[i] = (int*)malloc((arrSize / k + 1) * sizeof(int));
    }
    
    for (int i = 0; i < arrSize; i++) {
        int groupIndex = i % k;
        groups[groupIndex][groupSizes[groupIndex]++] = arr[i];
    }
    
    for (int i = 0; i < k; i++) {
        int size = groupSizes[i];
        int* group = groups[i];
        
        // Find median
        int medianIndex = size / 2;
        // Quickselect algorithm to find the median
        int left = 0, right = size - 1;
        while (left < right) {
            int pivot = group[right];
            int pIndex = left;
            for (int j = left; j < right; j++) {
                if (group[j] <= pivot) {
                    int temp = group[j];
                    group[j] = group[pIndex];
                    group[pIndex] = temp;
                    pIndex++;
                }
            }
            group[right] = group[pIndex];
            group[pIndex] = pivot;
            if (pIndex == medianIndex) {
                break;
            } else if (pIndex < medianIndex) {
                left = pIndex + 1;
            } else {
                right = pIndex - 1;
            }
        }
        
        int median = group[medianIndex];
        
        // Calculate the cost to make all elements equal to the median
        for (int j = 0; j < size; j++) {
            result += llabs((long long)group[j] - (long long)median);
        }
    }
    
    for (int i = 0; i < k; i++) {
        free(groups[i]);
    }
    free(groups);
    free(groupSizes);
    
    return result;      
}
