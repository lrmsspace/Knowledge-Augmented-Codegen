// Source: https://leetcode.com/problems/find-x-value-of-array-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums and a positive integer k. You are also given a 2D array queries, where queries[i] = [indexi, valuei, starti, xi].
//
// You are allowed to perform an operation once on nums, where you can remove any suffix from nums such that nums remains non-empty.
//
// The x-value of nums for a given x is defined as the number of ways to perform this operation so that the product of the remaining elements leaves a remainder of x modulo k.
//
// For each query in queries you need to determine the x-value of nums for xi after performing the following actions:
//
//
// 	Update nums[indexi] to valuei. Only this step persists for the rest of the queries.
// 	Remove the prefix nums[0..(starti - 1)] (where nums[0..(-1)] will be used to represent the empty prefix).
//
//
// Return an array result of size queries.length where result[i] is the answer for the ith query.
//
// A prefix of an array is a subarray that starts from the beginning of the array and extends to any point within it.
//
// A suffix of an array is a subarray that starts at any point within the array and extends to the end of the array.
//
// Note that the prefix and suffix to be chosen for the operation can be empty.
//
// Note that x-value has a different definition in this version.
//
// Example:
// Input: nums = [1,2,3,4,5], k = 3, queries = [[2,2,0,2],[3,3,3,0],[0,1,0,1]]
//
// Output: [2,2,2]
//
// Explanation:
//
//
// 	For query 0, nums becomes [1, 2, 2, 4, 5], and the empty prefix must be removed. The possible operations are:
//
// 	
// 		Remove the suffix [2, 4, 5]. nums becomes [1, 2].
// 		Remove the empty suffix. nums becomes [1, 2, 2, 4, 5] with a product 80, which gives remainder 2 when divided by 3.
// 	
// 	
// 	For query 1, nums becomes [1, 2, 2, 3, 5], and the prefix [1, 2, 2] must be removed. The possible operations are:
// 	
// 		Remove the empty suffix. nums becomes [3, 5].
// 		Remove the suffix [5]. nums becomes [3].
// 	
// 	
// 	For query 2, nums becomes [1, 2, 2, 3, 5], and the empty prefix must be removed. The possible operations are:
// 	
// 		Remove the suffix [2, 2, 3, 5]. nums becomes [1].
// 		Remove the suffix [3, 5]. nums becomes [1, 2, 2].
//
// Constraints:
// 1 <= nums[i] <= 109
// 	1 <= nums.length <= 105
// 	1 <= k <= 5
// 	1 <= queries.length <= 2 * 104
// 	queries[i] == [indexi, valuei, starti, xi]
// 	0 <= indexi <= nums.length - 1
// 	1 <= valuei <= 109
// 	0 <= starti <= nums.length - 1
// 	0 <= xi <= k - 1
//

class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<vector<int>> prefixDP(n + 1, vector<int>(k, 0));
        prefixDP[0][1 % k] = 1;  // empty prefix product is 1
        
        for (int i = 1; i <= n; i++) {
            int numMod = nums[i - 1] % k;
            for (int r = 0; r < k; r++) {
                prefixDP[i][r] = prefixDP[i - 1][r];  // not include nums[i-1]
                int prevR = (r * modInverse(numMod, k)) % k;
                prefixDP[i][r] = (prefixDP[i][r] + prefixDP[i - 1][prevR]) % MOD;
            }
        }
        
        vector<int> results;
        
        for (const auto& query : queries) {
            int index = query[0];
            int value = query[1];
            int start = query[2];
            int x = query[3];
            
            // Update nums
            int oldNumMod = nums[index] % k;
            int newNumMod = value % k;
            nums[index] = value;
            
            // Recompute prefixDP from index+1 to n
            for (int i = index + 1; i <= n; i++) {
                for (int r = 0; r < k; r++) {
                    prefixDP[i][r] = prefixDP[i - 1][r];  // not include nums[i-1]
                    int prevR = (r * modInverse(nums[i - 1] % k, k)) % k;
                    prefixDP[i][r] = (prefixDP[i][r] + prefixDP[i - 1][prevR]) % MOD;
                }
            }
            
            results.push_back(prefixDP[n][x]);
        }
        
        return results;         
    }
};
