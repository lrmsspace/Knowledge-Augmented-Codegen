// Source: https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums.
//
// Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:
//
//
// 	The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
// 	The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
//
//
// Return the total number of such pairs.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4]
//
// Output: 10
//
// Explanation:
//
// The subsequence pairs which have the GCD of their elements equal to 1 are:
//
//
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 200
//

class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        const int MAX_A = 200;
        int n = nums.size();
        
        // Count frequency of each number
        vector<int> freq(MAX_A + 1, 0);
        for (int num : nums) {
            freq[num]++;
        }
        
        // dp[g] = number of subsequences with GCD = g
        vector<long long> dp(MAX_A + 1, 0);
        
        // Calculate dp values
        for (int g = MAX_A; g >= 1; g--) {
            long long count = 1; // empty subsequence
            for (int multiple = g; multiple <= MAX_A; multiple += g) {
                count = (count * (pow(2, freq[multiple], MOD))) % MOD;
            }
            count = (count - 1 + MOD) % MOD; // exclude empty subsequence
            
            // Subtract subsequences counted for multiples of g
            for (int multiple = 2 * g; multiple <= MAX_A; multiple += g) {
                count = (count - dp[multiple] + MOD) % MOD;
            }
            
            dp[g] = count;
        }
        
        // Calculate the result
        long long result = 0;
        for (int g = 1; g <= MAX_A; g++) {
            result = (result + dp[g] * dp[g]) % MOD;
        }
        
        return (int)result;         
    }
};
