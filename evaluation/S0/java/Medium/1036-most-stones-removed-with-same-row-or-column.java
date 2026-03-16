// Source: https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/   |   Difficulty: Medium
//
// Problem Description:
// On a 2D plane, we place n stones at some integer coordinate points. Each coordinate point may have at most one stone.
//
// A stone can be removed if it shares either the same row or the same column as another stone that has not been removed.
//
// Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith stone, return the largest possible number of stones that can be removed.
//
// Example:
// Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
// Output: 5
// Explanation: One way to remove 5 stones is as follows:
// 1. Remove stone [2,2] because it shares the same row as [2,1].
// 2. Remove stone [2,1] because it shares the same column as [0,1].
// 3. Remove stone [1,2] because it shares the same row as [1,0].
// 4. Remove stone [1,0] because it shares the same column as [0,0].
// 5. Remove stone [0,1] because it shares the same row as [0,0].
// Stone [0,0] cannot be removed since it does not share a row/column with another stone still on the plane.
//
// Constraints:
// 1 <= stones.length <= 1000
// 	0 <= xi, yi <= 104
// 	No two stones are at the same coordinate point.
//

class Solution {
    public int removeStones(int[][] stones) {
        int n = stones.length;
        UnionFind uf = new UnionFind(20000); // since 0 <= xi, yi <= 10^4, we can use offset to distinguish row and column

        for (int[] stone : stones) {
            int row = stone[0];
            int col = stone[1] + 10000; // offset to avoid collision between row and column indices
            uf.union(row, col);
        }

        Set<Integer> uniqueParents = new HashSet<>();
        for (int[] stone : stones) {
            int row = stone[0];
            uniqueParents.add(uf.find(row));
        }

        return n - uniqueParents.size();            
    }
}
