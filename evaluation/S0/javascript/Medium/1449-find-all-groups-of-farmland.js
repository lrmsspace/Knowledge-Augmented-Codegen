// Source: https://leetcode.com/problems/find-all-groups-of-farmland/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed m x n binary matrix land where a 0 represents a hectare of forested land and a 1 represents a hectare of farmland.
//
// To keep the land organized, there are designated rectangular areas of hectares that consist entirely of farmland. These rectangular areas are called groups. No two groups are adjacent, meaning farmland in one group is not four-directionally adjacent to another farmland in a different group.
//
// land can be represented by a coordinate system where the top left corner of land is (0, 0) and the bottom right corner of land is (m-1, n-1). Find the coordinates of the top left and bottom right corner of each group of farmland. A group of farmland with a top left corner at (r1, c1) and a bottom right corner at (r2, c2) is represented by the 4-length array [r1, c1, r2, c2].
//
// Return a 2D array containing the 4-length arrays described above for each group of farmland in land. If there are no groups of farmland, return an empty array. You may return the answer in any order.
//
// Example:
// Input: land = [[1,0,0],[0,1,1],[0,1,1]]
// Output: [[0,0,0,0],[1,1,2,2]]
// Explanation:
// The first group has a top left corner at land[0][0] and a bottom right corner at land[0][0].
// The second group has a top left corner at land[1][1] and a bottom right corner at land[2][2].
//
// Constraints:
// m == land.length
// 	n == land[i].length
// 	1 <= m, n <= 300
// 	land consists of only 0's and 1's.
// 	Groups of farmland are rectangular in shape.
//

/**
 * @param {number[][]} land
 * @return {number[][]}
 */
var findFarmland = function(land) {
    const result = [];
    const rows = land.length;
    const cols = land[0].length;    
    const visited = Array.from({ length: rows }, () => Array(cols).fill(false));

    const directions = [
        [0, 1], // right
        [1, 0], // down
    ];
    const dfs = (r, c, bounds) => {
        visited[r][c] = true;
        bounds.minRow = Math.min(bounds.minRow, r);
        bounds.maxRow = Math.max(bounds.maxRow, r);
        bounds.minCol = Math.min(bounds.minCol, c);
        bounds.maxCol = Math.max(bounds.maxCol, c);
            
        for (const [dr, dc] of directions) {
            const newRow = r + dr;
            const newCol = c + dc;
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                land[newRow][newCol] === 1 && !visited[newRow][newCol]) {
                dfs(newRow, newCol, bounds);
            }
        }
    }
    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            if (land[r][c] === 1 && !visited[r][c]) {
                const bounds = { minRow: r, maxRow: r, minCol: c, maxCol: c };
                dfs(r, c, bounds);
                result.push([bounds.minRow, bounds.minCol, bounds.maxRow, bounds.maxCol]);
            }
        }
    }
    return result;  
    
};
