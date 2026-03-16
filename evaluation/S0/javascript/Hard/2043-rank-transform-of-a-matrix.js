// Source: https://leetcode.com/problems/rank-transform-of-a-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n matrix, return a new matrix answer where answer[row][col] is the rank of matrix[row][col].
//
// The rank is an integer that represents how large an element is compared to other elements. It is calculated using the following rules:
//
//
// 	The rank is an integer starting from 1.
// 	If two elements p and q are in the same row or column, then:
// 	
// 		If p < q then rank(p) < rank(q)
// 		If p == q then rank(p) == rank(q)
// 		If p > q then rank(p) > rank(q)
// 	
// 	
// 	The rank should be as small as possible.
//
//
// The test cases are generated so that answer is unique under the given rules.
//
// Example:
// Input: matrix = [[1,2],[3,4]]
// Output: [[1,2],[2,3]]
// Explanation:
// The rank of matrix[0][0] is 1 because it is the smallest integer in its row and column.
// The rank of matrix[0][1] is 2 because matrix[0][1] > matrix[0][0] and matrix[0][0] is rank 1.
// The rank of matrix[1][0] is 2 because matrix[1][0] > matrix[0][0] and matrix[0][0] is rank 1.
// The rank of matrix[1][1] is 3 because matrix[1][1] > matrix[0][1], matrix[1][1] > matrix[1][0], and both matrix[0][1] and matrix[1][0] are rank 2.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 500
// 	-109 <= matrix[row][col] <= 109
//

/**
 * @param {number[][]} matrix
 * @return {number[][]}
 */
var matrixRankTransform = function(matrix) {
        const m = matrix.length;
        const n = matrix[0].length;
        const valueToPositions = new Map();
        for (let i = 0; i < m; i++) {
            for (let j = 0; j < n; j++) {
                const value = matrix[i][j];
                if (!valueToPositions.has(value)) {
                    valueToPositions.set(value, []);
                }
                valueToPositions.get(value).push([i, j]);
            }
        }
        const sortedValues = Array.from(valueToPositions.keys()).sort((a, b) => a - b);
        const rowMaxRank = new Array(m).fill(0);
        const colMaxRank = new Array(n).fill(0);
        const answer = Array.from({ length: m }, () => new Array(n).fill(0));
        for (const value of sortedValues) {
            const positions = valueToPositions.get(value);
            const parent = new Array(m + n).fill(0).map((_, index) => index);
            const rank = new Array(m + n).fill(0);
            const find = (x) => {
                if (parent[x] !== x) {
                    parent[x] = find(parent[x]);
                }
                return parent[x];
            }
            const union = (a, b) => {
                const rootA = find(a);
                const rootB = find(b);
                if (rootA !== rootB) {
                    parent[rootB] = rootA;
                    rank[rootA] = Math.max(rank[rootA], rank[rootB]);
                }
            }
            for (const [i, j] of positions) {
                const rowNode = i;
                const colNode = j + m;
                union(rowNode, colNode);
                rank[find(rowNode)] = Math.max(rank[find(rowNode)], Math.max(rowMaxRank[i], colMaxRank[j]));
            }
            for (const [i, j] of positions) {
                const rowNode = i;
                const colNode = j + m;
                const currentRank = rank[find(rowNode)] + 1;
                answer[i][j] = currentRank;
                rowMaxRank[i] = Math.max(rowMaxRank[i], currentRank);
                colMaxRank[j] = Math.max(colMaxRank[j], currentRank);
            }
        }
        return answer;
};
