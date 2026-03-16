// Source: https://leetcode.com/problems/minimum-total-cost-to-make-arrays-unequal/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2, of equal length n.
//
// In one operation, you can swap the values of any two indices of nums1. The cost of this operation is the sum of the indices.
//
// Find the minimum total cost of performing the given operation any number of times such that nums1[i] != nums2[i] for all 0 <= i <= n - 1 after performing all the operations.
//
// Return the minimum total cost such that nums1 and nums2 satisfy the above condition. In case it is not possible, return -1.
//
// Example:
// Input: nums1 = [1,2,3,4,5], nums2 = [1,2,3,4,5]
// Output: 10
// Explanation: 
// One of the ways we can perform the operations is:
// - Swap values at indices 0 and 3, incurring cost = 0 + 3 = 3. Now, nums1 = [4,2,3,1,5]
// - Swap values at indices 1 and 2, incurring cost = 1 + 2 = 3. Now, nums1 = [4,3,2,1,5].
// - Swap values at indices 0 and 4, incurring cost = 0 + 4 = 4. Now, nums1 =[5,3,2,1,4].
// We can see that for each index i, nums1[i] != nums2[i]. The cost required here is 10.
// Note that there are other ways to swap values, but it can be proven that it is not possible to obtain a cost less than 10.
//
// Constraints:
// n == nums1.length == nums2.length
//  1 <= n <= 105
//  1 <= nums1[i], nums2[i] <= n
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long minimumTotalCost(int[] nums1, int[] nums2) {
        int n = nums1.length;
        long totalCost = 0;

        // Count the frequency of each number in nums1 and nums2
        int[] freq1 = new int[n + 1];
        int[] freq2 = new int[n + 1];

        for (int i = 0; i < n; i++) {
            freq1[nums1[i]]++;
            freq2[nums2[i]]++;
        }

        // Calculate the total cost of making nums1 and nums2 unequal
        for (int i = 0; i < n; i++) {
            if (nums1[i] == nums2[i]) {
                totalCost += i; // Cost of swapping at index i
            }
        }

        // Check if it's possible to make nums1 and nums2 unequal
        for (int num = 1; num <= n; num++) {
            if (freq1[num] + freq2[num] > n) {
                return -1; // Not possible to make them unequal
            }
        }

        return totalCost;           
    }
}
