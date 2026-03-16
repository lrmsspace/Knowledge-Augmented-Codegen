// Source: https://leetcode.com/problems/concatenated-divisibility/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums and a positive integer k.
//
// A permutation of nums is said to form a divisible concatenation if, when you concatenate the decimal representations of the numbers in the order specified by the permutation, the resulting number is divisible by k.
//
// Return the lexicographically smallest permutation (when considered as a list of integers) that forms a divisible concatenation. If no such permutation exists, return an empty list.
//
// Example:
// Input: nums = [3,12,45], k = 5
//
// Output: [3,12,45]
//
// Explanation:
//
//
// 	
// 		
// 			Permutation
// 			Concatenated Value
// 			Divisible by 5
// 		
// 	
// 	
// 		
// 			[3, 12, 45]
// 			31245
// 			Yes
// 		
// 		
// 			[3, 45, 12]
// 			34512
// 			No
// 		
// 		
// 			[12, 3, 45]
// 			12345
// 			Yes
// 		
// 		
// 			[12, 45, 3]
// 			12453
// 			No
// 		
// 		
// 			[45, 3, 12]
// 			45312
// 			No
// 		
// 		
// 			[45, 12, 3]
// 			45123
// 			No
// 		
// 	
//
//
// The lexicographically smallest permutation that forms a divisible concatenation is [3,12,45].
//
// Constraints:
// 1 <= nums.length <= 13
// 	1 <= nums[i] <= 105
// 	1 <= k <= 100
//

class Solution {
public:
    vector<int> concatenatedDivisibility(vector<int>& nums, int k) {
        int n = nums.size();
        int N = 1 << n;
        vector<vector<int>> dp(N, vector<int>(k, INT_MAX));
        vector<vector<int>> parent(N, vector<int>(k, -1));
        
        dp[0][0] = 0;
        
        for (int mask = 0; mask < N; mask++) {
            for (int mod = 0; mod < k; mod++) {
                if (dp[mask][mod] == INT_MAX) continue;
                
                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) continue;
                    
                    int newMask = mask | (1 << i);
                    int num = nums[i];
                    int len = to_string(num).length();
                    int newMod = (mod * pow(10, len) + num) % k;
                    
                    if (dp[newMask][newMod] > dp[mask][mod] + 1) {
                        dp[newMask][newMod] = dp[mask][mod] + 1;
                        parent[newMask][newMod] = i;
                    }
                }
            }
        }
        
        if (dp[N - 1][0] == INT_MAX) return {};
        
        vector<int> result;
        int mask = N - 1;
        int mod = 0;
        
        while (mask) {
            int idx = parent[mask][mod];
            result.push_back(nums[idx]);
            int num = nums[idx];
            int len = to_string(num).length();
            mod = (mod - num + k) % k;
            for (int j = 0; j < len; j++) {
                mod = (mod * modInverse(10, k)) % k;
            }
            mask ^= (1 << idx);
        }
        
        reverse(result.begin(), result.end());
        return result;          
    }
};
