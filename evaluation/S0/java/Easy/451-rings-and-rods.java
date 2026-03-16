// Source: https://leetcode.com/problems/rings-and-rods/   |   Difficulty: Easy
//
// Problem Description:
// There are n rings and each ring is either red, green, or blue. The rings are distributed across ten rods labeled from 0 to 9.
//
// You are given a string rings of length 2n that describes the n rings that are placed onto the rods. Every two characters in rings forms a color-position pair that is used to describe each ring where:
//
//
// 	The first character of the ith pair denotes the ith ring's color ('R', 'G', 'B').
// 	The second character of the ith pair denotes the rod that the ith ring is placed on ('0' to '9').
//
//
// For example, "R3G2B1" describes n == 3 rings: a red ring placed onto the rod labeled 3, a green ring placed onto the rod labeled 2, and a blue ring placed onto the rod labeled 1.
//
// Return the number of rods that have all three colors of rings on them.
//
// Example:
// Input: rings = "B0B6G0R6R0R6G9"
// Output: 1
// Explanation: 
// - The rod labeled 0 holds 3 rings with all colors: red, green, and blue.
// - The rod labeled 6 holds 3 rings, but it only has red and blue.
// - The rod labeled 9 holds only a green ring.
// Thus, the number of rods with all three colors is 1.
//
// Constraints:
// rings.length == 2 * n
// 	1 <= n <= 100
// 	rings[i] where i is even is either 'R', 'G', or 'B' (0-indexed).
// 	rings[i] where i is odd is a digit from '0' to '9' (0-indexed).
//

class Solution {
    public int countPoints(String rings) {
        // Create an array to track colors on each rod
        int[][] rods = new int[10][3]; // 10 rods, 3 colors (R, G, B)

        // Map colors to indices
        for (int i = 0; i < rings.length(); i += 2) {
            char color = rings.charAt(i);
            int rodIndex = rings.charAt(i + 1) - '0';

            if (color == 'R') {
                rods[rodIndex][0] = 1; // Red
            } else if (color == 'G') {
                rods[rodIndex][1] = 1; // Green
            } else if (color == 'B') {
                rods[rodIndex][2] = 1; // Blue
            }
        }

        // Count rods with all three colors
        int count = 0;
        for (int i = 0; i < 10; i++) {
            if (rods[i][0] == 1 && rods[i][1] == 1 && rods[i][2] == 1) {
                count++;
            }
        }

        return count;           
    }
}
