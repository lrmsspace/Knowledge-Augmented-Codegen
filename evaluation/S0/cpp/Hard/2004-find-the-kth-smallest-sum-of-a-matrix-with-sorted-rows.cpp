// Source: https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n matrix mat that has its rows sorted in non-decreasing order and an integer k.
//
// You are allowed to choose exactly one element from each row to form an array.
//
// Return the kth smallest array sum among all possible arrays.
//
// Example:
// Input: mat = [[1,3,11],[2,4,6]], k = 5
// Output: 7
// Explanation: Choosing one element from each row, the first k smallest sum are:
// [1,2], [1,4], [3,2], [3,4], [1,6]. Where the 5th sum is 7.
//
// Constraints:
// m == mat.length
// 	n == mat.length[i]
// 	1 <= m, n <= 40
// 	1 <= mat[i][j] <= 5000
// 	1 <= k <= min(200, nm)
// 	mat[i] is a non-decreasing array.
//

class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        priority_queue<int> pq;
        pq.push(0);
        
        for (const auto& row : mat) {
            priority_queue<int> newPq;
            
            while (!pq.empty()) {
                int currSum = pq.top();
                pq.pop();
                
                for (int val : row) {
                    int newSum = currSum + val;
                    newPq.push(newSum);
                    
                    if (newPq.size() > k) {
                        newPq.pop();
                    }
                }
            }
            
            pq = move(newPq);
        }
        
        return pq.top();            
    }
};
