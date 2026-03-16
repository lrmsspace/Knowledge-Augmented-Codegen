// Source: https://leetcode.com/problems/minimum-average-of-smallest-and-largest-elements/   |   Difficulty: Easy
//
// Problem Description:
// You have an array of floating point numbers averages which is initially empty. You are given an array nums of n integers where n is even.
//
// You repeat the following procedure n / 2 times:
//
//
// 	Remove the smallest element, minElement, and the largest element maxElement, from nums.
// 	Add (minElement + maxElement) / 2 to averages.
//
//
// Return the minimum element in averages.
//
// Example:
// Input: nums = [7,8,3,4,15,13,4,1]
//
// Output: 5.5
//
// Explanation:
//
//
// 	
// 		
// 			step
// 			nums
// 			averages
// 		
// 		
// 			0
// 			[7,8,3,4,15,13,4,1]
// 			[]
// 		
// 		
// 			1
// 			[7,8,3,4,13,4]
// 			[8]
// 		
// 		
// 			2
// 			[7,8,4,4]
// 			[8,8]
// 		
// 		
// 			3
// 			[7,4]
// 			[8,8,6]
// 		
// 		
// 			4
// 			[]
// 			[8,8,6,5.5]
// 		
// 	
//
// The smallest element of averages, 5.5, is returned.
//
// Constraints:
// 2 <= n == nums.length <= 50
// 	n is even.
// 	1 <= nums[i] <= 50
//
// Helpful references (internal KB):
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
// - bucket-sort (array, linked-list, bucket-sort)
//   • When to use: Use when sorting elements, especially floating-point numbers, that are uniformly distributed over a range. It offers linear time complexity on average for such distributions.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually using another sorting algorithm, and then concatenates the sorted buckets. It achieves an average time complexity of O(N+K), where N is the number of elements and K is the number of buckets.
//   • Invariants: Before sorting any bucket, all elements are correctly placed in their respective buckets based on their range.; After sorting each individual bucket, all elements within that bucket are in sorted order.
//   • Tips: Use a stable sorting algorithm like Insertion Sort for individual buckets to maintain overall stability.; The number of buckets should be chosen carefully, often proportional to N, to optimize performance.
//   • Pitfalls: Performance degrades significantly with non-uniform data distributions, potentially becoming O(N^2).; Requires extra space for the buckets, which can be substantial for many buckets or large elements.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double minimumAverage(int* nums, int numsSize) {
    // Sort the input array to easily access the smallest and largest elements.
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = 0; j < numsSize - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }

    double min_avg = (nums[0] + nums[numsSize - 1]) / 2.0; // Initialize with the average of the smallest and largest elements.

    // Calculate the average of pairs and find the minimum average.
    for (int i = 0; i < numsSize / 2; i++) {
        double avg = (nums[i] + nums[numsSize - 1 - i]) / 2.0;
        if (avg < min_avg) {
            min_avg = avg;
        }
    }

    return min_avg;     
}
