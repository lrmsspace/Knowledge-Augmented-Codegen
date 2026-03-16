// Source: https://leetcode.com/problems/maximum-white-tiles-covered-by-a-carpet/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array tiles where tiles[i] = [li, ri] represents that every tile j in the range li <= j <= ri is colored white.
//
// You are also given an integer carpetLen, the length of a single carpet that can be placed anywhere.
//
// Return the maximum number of white tiles that can be covered by the carpet.
//
// Example:
// Input: tiles = [[1,5],[10,11],[12,18],[20,25],[30,32]], carpetLen = 10
// Output: 9
// Explanation: Place the carpet starting on tile 10. 
// It covers 9 white tiles, so we return 9.
// Note that there may be other places where the carpet covers 9 white tiles.
// It can be shown that the carpet cannot cover more than 9 white tiles.
//
// Constraints:
// 1 <= tiles.length <= 5 * 104
// 	tiles[i].length == 2
// 	1 <= li <= ri <= 109
// 	1 <= carpetLen <= 109
// 	The tiles are non-overlapping.
//

class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
        sort(tiles.begin(), tiles.end());

        int n = tiles.size();
        int maxCovered = 0;
        int currentCovered = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            currentCovered += tiles[right][1] - tiles[right][0] + 1;

            while (tiles[right][1] - tiles[left][0] + 1 > carpetLen) {
                int overlap = tiles[right][1] - (tiles[left][0] + carpetLen - 1);
                if (overlap > 0) {
                    currentCovered -= overlap;
                }
                currentCovered -= tiles[left][1] - tiles[left][0] + 1;
                left++;
            }

            maxCovered = max(maxCovered, currentCovered);
        }

        return maxCovered;          
    }
};
