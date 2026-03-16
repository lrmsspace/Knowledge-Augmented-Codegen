// Source: https://leetcode.com/problems/sorted-gcd-pair-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of length n and an integer array queries.
//
// Let gcdPairs denote an array obtained by calculating the GCD of all possible pairs (nums[i], nums[j]), where 0 <= i < j < n, and then sorting these values in ascending order.
//
// For each query queries[i], you need to find the element at index queries[i] in gcdPairs.
//
// Return an integer array answer, where answer[i] is the value at gcdPairs[queries[i]] for each query.
//
// The term gcd(a, b) denotes the greatest common divisor of a and b.
//
// Example:
// Input: nums = [2,3,4], queries = [0,2,2]
//
// Output: [1,2,2]
//
// Explanation:
//
// gcdPairs = [gcd(nums[0], nums[1]), gcd(nums[0], nums[2]), gcd(nums[1], nums[2])] = [1, 2, 1].
//
// After sorting in ascending order, gcdPairs = [1, 1, 2].
//
// So, the answer is [gcdPairs[queries[0]], gcdPairs[queries[1]], gcdPairs[queries[2]]] = [1, 2, 2].
//
// Constraints:
// 2 <= n == nums.length <= 105
// 	1 <= nums[i] <= 5 * 104
// 	1 <= queries.length <= 105
// 	0 <= queries[i] < n * (n - 1) / 2
//

class Solution {
    public int[] gcdValues(int[] nums, long[] queries) {
        int maxNum = 50000;
        int[] freq = new int[maxNum + 1];
        for (int num : nums) {
            freq[num]++;
        }

        long[] gcdCount = new long[maxNum + 1];
        for (int g = 1; g <= maxNum; g++) {
            long count = 0;
            for (int multiple = g; multiple <= maxNum; multiple += g) {
                count += freq[multiple];
            }
            gcdCount[g] = count * (count - 1) / 2;
        }

        for (int g = maxNum - 1; g >= 1; g--) {
            for (int multiple = 2 * g; multiple <= maxNum; multiple += g) {
                gcdCount[g] -= gcdCount[multiple];
            }
        }

        long[] prefixSum = new long[maxNum + 1];
        for (int g = 1; g <= maxNum; g++) {
            prefixSum[g] = prefixSum[g - 1] + gcdCount[g];
        }

        int[] result = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            long query = queries[i] + 1;
            int left = 1, right = maxNum;
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (prefixSum[mid] < query) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            result[i] = left;
        }

        return result;          
    }
}
