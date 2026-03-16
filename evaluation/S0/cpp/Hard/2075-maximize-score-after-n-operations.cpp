// Source: https://leetcode.com/problems/maximize-score-after-n-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given nums, an array of positive integers of size 2 * n. You must perform n operations on this array.
//
// In the ith operation (1-indexed), you will:
//
//
// 	Choose two elements, x and y.
// 	Receive a score of i * gcd(x, y).
// 	Remove x and y from nums.
//
//
// Return the maximum score you can receive after performing n operations.
//
// The function gcd(x, y) is the greatest common divisor of x and y.
//
// Example:
// Input: nums = [1,2]
// Output: 1
// Explanation: The optimal choice of operations is:
// (1 * gcd(1, 2)) = 1
//
// Constraints:
// 1 <= n <= 7
// 	nums.length == 2 * n
// 	1 <= nums[i] <= 106
//

class Solution {
public:
    int maxScore(vector<int>& nums) {
        int n = nums.size();
        int N = n / 2;
        vector<vector<int>> gcdTable(n, vector<int>(n, 0));
        
        // Precompute GCDs
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                gcdTable[i][j] = gcd(nums[i], nums[j]);
            }
        }
        
        int maxMask = 1 << n;
        vector<int> dp(maxMask, 0);
        
        for (int mask = 0; mask < maxMask; mask++) {
            int bitsCount = __builtin_popcount(mask);
            if (bitsCount % 2 != 0) continue; // Only consider even counts
            
            int operation = bitsCount / 2 + 1;
            
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) continue; // i already used
                
                for (int j = i + 1; j < n; j++) {
                    if (mask & (1 << j)) continue; // j already used
                    
                    int newMask = mask | (1 << i) | (1 << j);
                    dp[newMask] = max(dp[newMask], dp[mask] + operation * gcdTable[i][j]);
                }
            }
        }
        
        return dp[maxMask - 1];         
    }
};
