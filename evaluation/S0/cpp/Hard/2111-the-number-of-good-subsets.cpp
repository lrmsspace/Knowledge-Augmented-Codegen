// Source: https://leetcode.com/problems/the-number-of-good-subsets/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. We call a subset of nums good if its product can be represented as a product of one or more distinct prime numbers.
//
//
// 	For example, if nums = [1, 2, 3, 4]:
//
// 	
// 		[2, 3], [1, 2, 3], and [1, 3] are good subsets with products 6 = 2*3, 6 = 2*3, and 3 = 3 respectively.
// 		[1, 4] and [4] are not good subsets with products 4 = 2*2 and 4 = 2*2 respectively.
// 	
// 	
//
//
// Return the number of different good subsets in nums modulo 109 + 7.
//
// A subset of nums is any array that can be obtained by deleting some (possibly none or all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 6
// Explanation: The good subsets are:
// - [1,2]: product is 2, which is the product of distinct prime 2.
// - [1,2,3]: product is 6, which is the product of distinct primes 2 and 3.
// - [1,3]: product is 3, which is the product of distinct prime 3.
// - [2]: product is 2, which is the product of distinct prime 2.
// - [2,3]: product is 6, which is the product of distinct primes 2 and 3.
// - [3]: product is 3, which is the product of distinct prime 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 30
//

class Solution {
public:
    int numberOfGoodSubsets(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        vector<int> primes = {2,3,5,7,11,13,17,19,23,29};
        vector<int> freq(31, 0);
        for (int num : nums) {
            freq[num]++;
        }
        
        // dp[mask]: number of ways to form subsets with prime factors represented by mask
        vector<long long> dp(1 << primes.size(), 0);
        dp[0] = 1;  // empty subset
        
        for (int num = 2; num <= 30; num++) {
            if (freq[num] == 0) continue;
            
            // Check if num has any squared prime factors
            int mask = 0;
            bool isValid = true;
            for (int i = 0; i < primes.size(); i++) {
                int prime = primes[i];
                if (num % (prime * prime) == 0) {
                    isValid = false;
                    break;
                }
                if (num % prime == 0) {
                    mask |= (1 << i);
                }
            }
            if (!isValid) continue;
            
            // Update dp array
            for (int prevMask = (1 << primes.size()) - 1; prevMask >= 0; prevMask--) {
                if ((prevMask & mask) == 0) {
                    dp[prevMask | mask] = (dp[prevMask | mask] + dp[prevMask] * freq[num]) % MOD;
                }
            }
        }
        
        long long result = 0;
        for (int mask = 1; mask < (1 << primes.size()); mask++) {
            result = (result + dp[mask]) % MOD;
        }
        
        // Account for the number of 1's
        if (freq[1] > 0) {
            long long pow2 = 1;
            for (int i = 0; i < freq[1]; i++) {
                pow2 = (pow2 * 2) % MOD;
            }
            result = (result * pow2) % MOD;
        }
        
        return (int)result;         
    }
};
