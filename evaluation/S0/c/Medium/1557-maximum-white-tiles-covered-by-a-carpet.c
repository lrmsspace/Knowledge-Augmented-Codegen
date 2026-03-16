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

int maximumWhiteTiles(int** tiles, int tilesSize, int* tilesColSize, int carpetLen) {
    // Sort the tiles based on their starting position
    int cmp(const void* a, const void* b) {
        return ((int*)a)[0] - ((int*)b)[0];
    }
    qsort(tiles, tilesSize, sizeof(int*), cmp);

    int maxCovered = 0;
    int left = 0, right = 0;
    int currentCovered = 0;

    while (right < tilesSize) {
        int carpetEnd = tiles[left][0] + carpetLen - 1;

        // Expand the right pointer to cover as many tiles as possible
        while (right < tilesSize && tiles[right][1] <= carpetEnd) {
            currentCovered += (tiles[right][1] - tiles[right][0] + 1);
            right++;
        }

        // Check if the carpet partially covers the next tile
        if (right < tilesSize && tiles[right][0] <= carpetEnd) {
            currentCovered += (carpetEnd - tiles[right][0] + 1);
        }

        maxCovered = fmax(maxCovered, currentCovered);

        // Move the left pointer to the next tile
        currentCovered -= (tiles[left][1] - tiles[left][0] + 1);
        left++;
    }

    return maxCovered;      
}
