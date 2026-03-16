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

class Solution {
public:
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> rank(m, vector<int>(n, 0));
        vector<int> rowMax(m, 0);
        vector<int> colMax(n, 0);
        
        map<int, vector<pair<int, int>>> valuePositions;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                valuePositions[matrix[i][j]].emplace_back(i, j);
            }
        }
        
        for (const auto& [value, positions] : valuePositions) {
            UnionFind uf(m + n);
            for (const auto& [i, j] : positions) {
                uf.unite(i, j + m);
            }
            
            unordered_map<int, vector<pair<int, int>>> groups;
            for (const auto& [i, j] : positions) {
                int parent = uf.find(i);
                groups[parent].emplace_back(i, j);
            }
            
            for (const auto& [parent, groupPositions] : groups) {
                int groupRank = 0;
                for (const auto& [i, j] : groupPositions) {
                    groupRank = max(groupRank, max(rowMax[i], colMax[j]));
                }
                groupRank++;
                
                for (const auto& [i, j] : groupPositions) {
                    rank[i][j] = groupRank;
                    rowMax[i] = max(rowMax[i], groupRank);
                    colMax[j] = max(colMax[j], groupRank);
                }
            }
        }
        
        return rank;            
    }
};
