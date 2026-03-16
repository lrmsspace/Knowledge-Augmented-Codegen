// Source: https://leetcode.com/problems/find-array-given-subset-sums/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n representing the length of an unknown array that you are trying to recover. You are also given an array sums containing the values of all 2n subset sums of the unknown array (in no particular order).
//
// Return the array ans of length n representing the unknown array. If multiple answers exist, return any of them.
//
// An array sub is a subset of an array arr if sub can be obtained from arr by deleting some (possibly zero or all) elements of arr. The sum of the elements in sub is one possible subset sum of arr. The sum of an empty array is considered to be 0.
//
// Note: Test cases are generated such that there will always be at least one correct answer.
//
// Example:
// Input: n = 3, sums = [-3,-2,-1,0,0,1,2,3]
// Output: [1,2,-3]
// Explanation: [1,2,-3] is able to achieve the given subset sums:
// - []: sum is 0
// - [1]: sum is 1
// - [2]: sum is 2
// - [1,2]: sum is 3
// - [-3]: sum is -3
// - [1,-3]: sum is -2
// - [2,-3]: sum is -1
// - [1,2,-3]: sum is 0
// Note that any permutation of [1,2,-3] and also any permutation of [-1,-2,3] will also be accepted.
//
// Constraints:
// 1 <= n <= 15
// 	sums.length == 2n
// 	-104 <= sums[i] <= 104
//

class Solution {
public:
    vector<int> recoverArray(int n, vector<int>& sums) {
        vector<int> result;
        unordered_map<int, int> count;
        for (int sum : sums) {
            count[sum]++;
        }
        
        for (int i = 0; i < n; i++) {
            vector<int> keys;
            for (const auto& pair : count) {
                keys.push_back(pair.first);
            }
            sort(keys.begin(), keys.end());
            
            int x = keys[1] - keys[0];
            unordered_map<int, int> countWithX, countWithoutX;
            for (int key : keys) {
                if (count[key] > 0) {
                    countWithoutX[key] += count[key];
                    countWithX[key + x] += count[key];
                }
            }
            
            bool valid = true;
            for (const auto& pair : countWithX) {
                if (count[pair.first] < pair.second) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                result.push_back(x);
                for (const auto& pair : countWithX) {
                    count[pair.first] -= pair.second;
                }
            } else {
                result.push_back(-x);
                for (const auto& pair : countWithoutX) {
                    count[pair.first] -= pair.second;
                }
            }
        }
        
        return result;          
    }
};
