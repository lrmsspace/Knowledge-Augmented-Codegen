// Source: https://leetcode.com/problems/maximize-ysum-by-picking-a-triplet-of-distinct-xvalues/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays x and y, each of length n. You must choose three distinct indices i, j, and k such that:
//
//
// 	x[i] != x[j]
// 	x[j] != x[k]
// 	x[k] != x[i]
//
//
// Your goal is to maximize the value of y[i] + y[j] + y[k] under these conditions. Return the maximum possible sum that can be obtained by choosing such a triplet of indices.
//
// If no such triplet exists, return -1.
//
// Example:
// Input: x = [1,2,1,3,2], y = [5,3,4,6,2]
//
// Output: 14
//
// Explanation:
//
//
// 	Choose i = 0 (x[i] = 1, y[i] = 5), j = 1 (x[j] = 2, y[j] = 3), k = 3 (x[k] = 3, y[k] = 6).
// 	All three values chosen from x are distinct. 5 + 3 + 6 = 14 is the maximum we can obtain. Hence, the output is 14.
//
// Constraints:
// n == x.length == y.length
// 	3 <= n <= 105
// 	1 <= x[i], y[i] <= 106
//

class Solution {
public:
    int maxSumDistinctTriplet(vector<int>& x, vector<int>& y) {
        unordered_map<int, priority_queue<int>> xToYMaxHeap;
        int n = x.size();
        for (int i = 0; i < n; ++i) {
            xToYMaxHeap[x[i]].push(y[i]);
        }

        priority_queue<int> topYSums;
        for (auto& [key, maxHeap] : xToYMaxHeap) {
            if (!maxHeap.empty()) {
                topYSums.push(maxHeap.top());
            }
        }

        if (topYSums.size() < 3) {
            return -1;
        }

        int result = 0;
        for (int i = 0; i < 3; ++i) {
            result += topYSums.top();
            topYSums.pop();
        }

        return result;          
    }
};
