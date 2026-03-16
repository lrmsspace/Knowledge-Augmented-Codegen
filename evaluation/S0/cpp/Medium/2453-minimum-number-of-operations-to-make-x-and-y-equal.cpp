// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-x-and-y-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers x and y.
//
// In one operation, you can do one of the four following operations:
//
//
// 	Divide x by 11 if x is a multiple of 11.
// 	Divide x by 5 if x is a multiple of 5.
// 	Decrement x by 1.
// 	Increment x by 1.
//
//
// Return the minimum number of operations required to make  x and y equal.
//
// Example:
// Input: x = 26, y = 1
// Output: 3
// Explanation: We can make 26 equal to 1 by applying the following operations: 
// 1. Decrement x by 1
// 2. Divide x by 5
// 3. Divide x by 5
// It can be shown that 3 is the minimum number of operations required to make 26 equal to 1.
//
// Constraints:
// 1 <= x, y <= 104
//

class Solution {
public:
    int minimumOperationsToMakeEqual(int x, int y) {
        queue<pair<int, int>> q; // {current value, operations count}
        unordered_set<int> visited;
        q.push({x, 0});
        visited.insert(x);

        while (!q.empty()) {
            auto [current, ops] = q.front();
            q.pop();

            if (current == y) {
                return ops;
            }

            // Possible operations
            vector<int> nextValues;

            if (current % 11 == 0) {
                nextValues.push_back(current / 11);
            }
            if (current % 5 == 0) {
                nextValues.push_back(current / 5);
            }
            nextValues.push_back(current - 1);
            nextValues.push_back(current + 1);

            for (int next : nextValues) {
                if (next >= 1 && next <= 10000 && visited.find(next) == visited.end()) {
                    visited.insert(next);
                    q.push({next, ops + 1});
                }
            }
        }

        return -1; // This line should never be reached given the problem constraints           
    }
};
