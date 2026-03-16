// Source: https://leetcode.com/problems/minimum-number-of-flips-to-convert-binary-matrix-to-zero-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given a m x n binary matrix mat. In one step, you can choose one cell and flip it and all the four neighbors of it if they exist (Flip is changing 1 to 0 and 0 to 1). A pair of cells are called neighbors if they share one edge.
//
// Return the minimum number of steps required to convert mat to a zero matrix or -1 if you cannot.
//
// A binary matrix is a matrix with all cells equal to 0 or 1 only.
//
// A zero matrix is a matrix with all cells equal to 0.
//
// Example:
// Input: mat = [[0,0],[0,1]]
// Output: 3
// Explanation: One possible solution is to flip (1, 0) then (0, 1) and finally (1, 1) as shown.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 3
// 	mat[i][j] is either 0 or 1.
//

class Solution {
    public int minFlips(int[][] mat) {
        int m = mat.length, n = mat[0].length;
        int start = 0, target = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                start |= (mat[i][j] << (i * n + j));
            }
        }

        Queue<Integer> queue = new LinkedList<>();
        Set<Integer> visited = new HashSet<>();

        queue.offer(start);
        visited.add(start);

        int steps = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();

            for (int i = 0; i < size; i++) {
                int curr = queue.poll();

                if (curr == target) {
                    return steps;
                }

                for (int r = 0; r < m; r++) {
                    for (int c = 0; c < n; c++) {
                        int next = flip(curr, r, c, m, n);

                        if (!visited.contains(next)) {
                            visited.add(next);
                            queue.offer(next);
                        }
                    }
                }
            }

            steps++;
        }

        return -1;                  
    }
}
