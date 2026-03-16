// Source: https://leetcode.com/problems/maximum-sum-obtained-of-any-permutation/   |   Difficulty: Medium
//
// Problem Description:
// We have an array of integers, nums, and an array of requests where requests[i] = [starti, endi]. The ith request asks for the sum of nums[starti] + nums[starti + 1] + ... + nums[endi - 1] + nums[endi]. Both starti and endi are 0-indexed.
//
// Return the maximum total sum of all requests among all permutations of nums.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4,5], requests = [[1,3],[0,1]]
// Output: 19
// Explanation: One permutation of nums is [2,1,3,4,5] with the following result: 
// requests[0] -> nums[1] + nums[2] + nums[3] = 1 + 3 + 4 = 8
// requests[1] -> nums[0] + nums[1] = 2 + 1 = 3
// Total sum: 8 + 3 = 11.
// A permutation with a higher total sum is [3,5,4,2,1] with the following result:
// requests[0] -> nums[1] + nums[2] + nums[3] = 5 + 4 + 2 = 11
// requests[1] -> nums[0] + nums[1] = 3 + 5  = 8
// Total sum: 11 + 8 = 19, which is the best that you can do.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	0 <= nums[i] <= 105
// 	1 <= requests.length <= 105
// 	requests[i].length == 2
// 	0 <= starti <= endi < n
//

class Solution {
    public int maxSumRangeQuery(int[] nums, int[][] requests) {
        int n = nums.length;
        int[] freq = new int[n + 1];

        // Calculate frequency of each index in nums based on requests
        for (int[] request : requests) {
            freq[request[0]]++;
            freq[request[1] + 1]--;
        }

        // Prefix sum to get the actual frequency for each index
        for (int i = 1; i < n; i++) {
            freq[i] += freq[i - 1];
        }

        // Remove the extra element used for easier calculation
        freq = Arrays.copyOf(freq, n);

        // Sort both nums and freq arrays
        Arrays.sort(nums);
        Arrays.sort(freq);

        long result = 0;
        int MOD = 1_000_000_007;

        // Calculate the maximum sum by pairing largest frequencies with largest numbers
        for (int i = 0; i < n; i++) {
            result = (result + (long) nums[i] * freq[i]) % MOD;
        }

        return (int) result;            
    }
}
