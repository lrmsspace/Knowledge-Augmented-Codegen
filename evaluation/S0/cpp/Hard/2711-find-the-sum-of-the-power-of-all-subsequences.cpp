// Source: https://leetcode.com/problems/find-the-sum-of-the-power-of-all-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of length n and a positive integer k.
//
// The power of an array of integers is defined as the number of subsequences with their sum equal to k.
//
// Return the sum of power of all subsequences of nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input:   nums = [1,2,3], k = 3 
//
// Output:   6 
//
// Explanation:
//
// There are 5 subsequences of nums with non-zero power:
//
//
// 	The subsequence [1,2,3] has 2 subsequences with sum == 3: [1,2,3] and [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
//
//
// Hence the answer is 2 + 1 + 1 + 1 + 1 = 6.
//
// Constraints:
// 1 <= n <= 100
// 	1 <= nums[i] <= 104
// 	1 <= k <= 100
//

class Solution {
public:
    int sumOfPower(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        long long result = 0;

        // Iterate over all subsequences using bitmask
        for (int mask = 1; mask < (1 << n); ++mask) {
            long long sum = 0;
            // Calculate sum of the current subsequence
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    sum += nums[i];
                }
            }
            // If sum equals k, add to result
            if (sum == k) {
                result = (result + sum) % MOD;
            }
        }

        return (int)result;         
    }
};
