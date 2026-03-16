// Source: https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n which represents an array nums containing the numbers from 1 to n in order. Additionally, you are given a 2D array conflictingPairs, where conflictingPairs[i] = [a, b] indicates that a and b form a conflicting pair.
//
// Remove exactly one element from conflictingPairs. Afterward, count the number of non-empty subarrays of nums which do not contain both a and b for any remaining conflicting pair [a, b].
//
// Return the maximum number of subarrays possible after removing exactly one conflicting pair.
//
// Example:
// Input: n = 4, conflictingPairs = [[2,3],[1,4]]
//
// Output: 9
//
// Explanation:
//
//
// 	Remove [2, 3] from conflictingPairs. Now, conflictingPairs = [[1, 4]].
// 	There are 9 subarrays in nums where [1, 4] do not appear together. They are [1], [2], [3], [4], [1, 2], [2, 3], [3, 4], [1, 2, 3] and [2, 3, 4].
// 	The maximum number of subarrays we can achieve after removing one element from conflictingPairs is 9.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= conflictingPairs.length <= 2 * n
// 	conflictingPairs[i].length == 2
// 	1 <= conflictingPairs[i][j] <= n
// 	conflictingPairs[i][0] != conflictingPairs[i][1]
//

class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        vector<int> left(n + 1, 1);
        vector<int> right(n + 1, n);
        vector<int> count(n + 2, 0);
        
        for (auto& p : conflictingPairs) {
            int a = p[0], b = p[1];
            if (a > b) swap(a, b);
            left[b] = max(left[b], a + 1);
            right[a] = min(right[a], b - 1);
        }
        
        for (int i = 1; i <= n; i++) {
            count[left[i]]++;
            count[i + 1]--;
        }
        
        for (int i = 1; i <= n; i++) {
            count[i] += count[i - 1];
        }
        
        long long totalSubarrays = (long long)n * (n + 1) / 2;
        long long minReduction = LLONG_MAX;
        
        for (int i = 1; i <= n; i++) {
            if (count[i] == 0) {
                minReduction = 0;
                break;
            }
            long long reduction = (long long)(i - left[i] + 1) * (right[i] - i + 1);
            minReduction = min(minReduction, reduction);
        }
        
        return totalSubarrays - minReduction;           
    }
};
