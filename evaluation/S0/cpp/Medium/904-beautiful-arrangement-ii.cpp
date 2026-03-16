// Source: https://leetcode.com/problems/beautiful-arrangement-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers n and k, construct a list answer that contains n different positive integers ranging from 1 to n and obeys the following requirement:
//
//
// 	Suppose this list is answer = [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|] has exactly k distinct integers.
//
//
// Return the list answer. If there multiple valid answers, return any of them.
//
// Example:
// Input: n = 3, k = 1
// Output: [1,2,3]
// Explanation: The [1,2,3] has three different positive integers ranging from 1 to 3, and the [1,1] has exactly 1 distinct integer: 1
//
// Constraints:
// 1 <= k < n <= 104
//

class Solution {
public:
    vector<int> constructArray(int n, int k) {
        vector<int> result;
        int left = 1, right = n;

        // Create the first k elements with alternating high and low values
        for (int i = 0; i < k; ++i) {
            if (i % 2 == 0) {
                result.push_back(left++);
            } else {
                result.push_back(right--);
            }
        }

        // Fill the remaining elements in ascending order
        if (k % 2 == 0) {
            for (int i = left; i <= right; ++i) {
                result.push_back(i);
            }
        } else {
            for (int i = right; i >= left; --i) {
                result.push_back(i);
            }
        }

        return result;          
    }
};
