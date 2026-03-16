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
    public int kthSmallest(int[][] mat, int k) {
        PriorityQueue<Integer> pq = new PriorityQueue<>((a, b) -> b - a);
        pq.offer(0);

        for (int i = 0; i < mat.length; i++) {
            PriorityQueue<Integer> nextPq = new PriorityQueue<>((a, b) -> b - a);

            while (!pq.isEmpty()) {
                int currSum = pq.poll();

                for (int j = 0; j < mat[i].length; j++) {
                    int newSum = currSum + mat[i][j];
                    nextPq.offer(newSum);

                    if (nextPq.size() > k) {
                        nextPq.poll();
                    }
                }
            }

            pq = nextPq;
        }

        return pq.poll();                   
    }
}
