// Source: https://leetcode.com/problems/sum-of-total-strength-of-wizards/   |   Difficulty: Hard
//
// Problem Description:
// As the ruler of a kingdom, you have an army of wizards at your command.
//
// You are given a 0-indexed integer array strength, where strength[i] denotes the strength of the ith wizard. For a contiguous group of wizards (i.e. the wizards' strengths form a subarray of strength), the total strength is defined as the product of the following two values:
//
//
// 	The strength of the weakest wizard in the group.
// 	The total of all the individual strengths of the wizards in the group.
//
//
// Return the sum of the total strengths of all contiguous groups of wizards. Since the answer may be very large, return it modulo 109 + 7.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: strength = [1,3,1,2]
// Output: 44
// Explanation: The following are all the contiguous groups of wizards:
// - [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
// - [3] from [1,3,1,2] has a total strength of min([3]) * sum([3]) = 3 * 3 = 9
// - [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
// - [2] from [1,3,1,2] has a total strength of min([2]) * sum([2]) = 2 * 2 = 4
// - [1,3] from [1,3,1,2] has a total strength of min([1,3]) * sum([1,3]) = 1 * 4 = 4
// - [3,1] from [1,3,1,2] has a total strength of min([3,1]) * sum([3,1]) = 1 * 4 = 4
// - [1,2] from [1,3,1,2] has a total strength of min([1,2]) * sum([1,2]) = 1 * 3 = 3
// - [1,3,1] from [1,3,1,2] has a total strength of min([1,3,1]) * sum([1,3,1]) = 1 * 5 = 5
// - [3,1,2] from [1,3,1,2] has a total strength of min([3,1,2]) * sum([3,1,2]) = 1 * 6 = 6
// - [1,3,1,2] from [1,3,1,2] has a total strength of min([1,3,1,2]) * sum([1,3,1,2]) = 1 * 7 = 7
// The sum of all the total strengths is 1 + 9 + 1 + 4 + 4 + 4 + 3 + 5 + 6 + 7 = 44.
//
// Constraints:
// 1 <= strength.length <= 105
// 	1 <= strength[i] <= 109
//

class Solution {
public:
    int totalStrength(vector<int>& strength) {
        const int MOD = 1e9 + 7;
        int n = strength.size();
        
        // Prefix sums
        vector<long long> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = (prefixSum[i] + strength[i]) % MOD;
        }
        
        // Prefix of prefix sums
        vector<long long> prefixOfPrefixSum(n + 2, 0);
        for (int i = 0; i <= n; i++) {
            prefixOfPrefixSum[i + 1] = (prefixOfPrefixSum[i] + prefixSum[i]) % MOD;
        }
        
        // Monotonic stack to find previous and next smaller elements
        stack<int> stk;
        long long result = 0;
        
        for (int i = 0; i <= n; i++) {
            while (!stk.empty() && (i == n || strength[stk.top()] > strength[i])) {
                int mid = stk.top();
                stk.pop();
                int left = stk.empty() ? -1 : stk.top();
                int right = i;
                
                long long totalLeft = (prefixOfPrefixSum[mid + 1] - prefixOfPrefixSum[left + 1] + MOD) % MOD;
                long long totalRight = (prefixOfPrefixSum[right + 1] - prefixOfPrefixSum[mid + 1] + MOD) % MOD;
                
                long long countLeft = mid - left;
                long long countRight = right - mid;
                
                long long contribution = strength[mid] * ((totalRight * countLeft % MOD - totalLeft * countRight % MOD + MOD) % MOD) % MOD;
                result = (result + contribution) % MOD;
            }
            stk.push(i);
        }
        
        return (int)result;         
    }
};
