// Source: https://leetcode.com/problems/path-crossing/   |   Difficulty: Easy
//
// Problem Description:
// Given a string path, where path[i] = 'N', 'S', 'E' or 'W', each representing moving one unit north, south, east, or west, respectively. You start at the origin (0, 0) on a 2D plane and walk on the path specified by path.
//
// Return true if the path crosses itself at any point, that is, if at any time you are on a location you have previously visited. Return false otherwise.
//
// Example:
// Input: path = "NES"
// Output: false 
// Explanation: Notice that the path doesn't cross any point more than once.
//
// Constraints:
// 1 <= path.length <= 104
// 	path[i] is either 'N', 'S', 'E', or 'W'.
//

bool isPathCrossing(char* path) {
    int x = 0, y = 0;
    int visited[20001][20001] = {0};
    visited[10000][10000] = 1; // Starting point

    for (int i = 0; path[i] != '\0'; i++) {
        switch (path[i]) {
            case 'N': y++; break;
            case 'S': y--; break;
            case 'E': x++; break;
            case 'W': x--; break;
        }

        if (visited[x + 10000][y + 10000]) {
            return true; // Path crosses itself
        }
        visited[x + 10000][y + 10000] = 1; // Mark the position as visited
    }

    return false; // No crossing found      
}
