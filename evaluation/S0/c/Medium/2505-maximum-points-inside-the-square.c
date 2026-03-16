// Source: https://leetcode.com/problems/maximum-points-inside-the-square/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D array points and a string s where, points[i] represents the coordinates of point i, and s[i] represents the tag of point i.
//
// A valid square is a square centered at the origin (0, 0), has edges parallel to the axes, and does not contain two points with the same tag.
//
// Return the maximum number of points contained in a valid square.
//
// Note:
//
//
// 	A point is considered to be inside the square if it lies on or within the square's boundaries.
// 	The side length of the square can be zero.
//
// Example:
// Input: points = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], s = "abdca"
//
// Output: 2
//
// Explanation:
//
// The square of side length 4 covers two points points[0] and points[1].
//
// Constraints:
// 1 <= s.length, points.length <= 105
// 	points[i].length == 2
// 	-109 <= points[i][0], points[i][1] <= 109
// 	s.length == points.length
// 	points consists of distinct coordinates.
// 	s consists only of lowercase English letters.
//

int maxPointsInsideSquare(int** points, int pointsSize, int* pointsColSize, char* s) {
    // Create an array to hold the maximum distance for each character
    int maxDist[26];
    for (int i = 0; i < 26; i++) {
        maxDist[i] = -1; // Initialize with -1 to indicate no point found yet
    }

    // Iterate through all points to find the maximum distance for each character
    for (int i = 0; i < pointsSize; i++) {
        int x = points[i][0];
        int y = points[i][1];
        char tag = s[i];
        int dist = fmax(abs(x), abs(y)); // Calculate the distance from origin

        int index = tag - 'a'; // Map character to index (0-25)
        if (dist > maxDist[index]) {
            maxDist[index] = dist; // Update maximum distance for this character
        }
    }

    // Count how many characters have at least one point inside the square
    int count = 0;
    for (int i = 0; i < 26; i++) {
        if (maxDist[i] != -1) {
            count++;
        }
    }

    return count; // Return the total count of unique characters with points inside the square      
}
