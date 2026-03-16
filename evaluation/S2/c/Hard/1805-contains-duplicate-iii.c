// Source: https://leetcode.com/problems/contains-duplicate-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers indexDiff and valueDiff.
//
// Find a pair of indices (i, j) such that:
//
//
// 	i != j,
// 	abs(i - j) <= indexDiff.
// 	abs(nums[i] - nums[j]) <= valueDiff, and
//
//
// Return true if such pair exists or false otherwise.
//
// Example:
// Input: nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
// Output: true
// Explanation: We can choose (i, j) = (0, 3).
// We satisfy the three conditions:
// i != j --> 0 != 3
// abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
// abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0
//
// Constraints:
// 2 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	1 <= indexDiff <= nums.length
// 	0 <= valueDiff <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Rabin-Karp Algorithm for string matching (string, number, hashing, rolling-hash)
//   • When to use: To efficiently find all occurrences of a given pattern string within a larger text string, especially when multiple patterns might be searched or for average-case linear time performance.
//   • Idea: The Rabin-Karp algorithm finds occurrences of a pattern in a text by comparing their hash values, using a rolling hash function to efficiently update substring hashes. It achieves an average time complexity of O(|s| + |t|) and a worst-case of O(|s| * |t|).
//   • Invariants: The hash of the pattern string remains constant throughout the search.; The current window's hash value accurately represents the substring T[i...i+len(P)-1].
//   • Tips: Choose a large prime modulus to minimize hash collisions.; Select a suitable base (e.g., a prime greater than alphabet size) for polynomial hashing.
//   • Pitfalls: Hash collisions can lead to false positives and degrade worst-case performance to O(MN).; Poor choice of base or modulus can significantly increase collision frequency.
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int indexDiff, int valueDiff) {
    if (numsSize < 2 || indexDiff < 1 || valueDiff < 0) {
        return false;
    }

    // We can use a balanced binary search tree (BST) to maintain a sliding window of the last `indexDiff` elements.
    // The BST allows us to efficiently check for the presence of any element within the range [nums[i] - valueDiff, nums[i] + valueDiff].
    // In C, we can use a sorted array to simulate the BST behavior.

    int* window = (int*)malloc(sizeof(int) * indexDiff);
    int windowSize = 0;

    for (int i = 0; i < numsSize; i++) {
        // Remove the element that is out of the current window
        if (i > indexDiff) {
            // Find and remove nums[i - indexDiff - 1] from the window
            int removeIndex = -1;
            for (int j = 0; j < windowSize; j++) {
                if (window[j] == nums[i - indexDiff - 1]) {
                    removeIndex = j;
                    break;
                }
            }
            if (removeIndex != -1) {
                memmove(&window[removeIndex], &window[removeIndex + 1], sizeof(int) * (windowSize - removeIndex - 1));
                windowSize--;
            }
        }

        // Check for any number in the window that is within valueDiff of nums[i]
        for (int j = 0; j < windowSize; j++) {
            if (abs(window[j] - nums[i]) <= valueDiff) {
                free(window);
                return true;
            }
        }

        // Add the current number to the window
        if (windowSize < indexDiff) {
            window[windowSize++] = nums[i];
        } else {
            memmove(&window[0], &window[1], sizeof(int) * (indexDiff - 1));
            window[indexDiff - 1] = nums[i];
        }
    }

    free(window);
    return false;       
}
