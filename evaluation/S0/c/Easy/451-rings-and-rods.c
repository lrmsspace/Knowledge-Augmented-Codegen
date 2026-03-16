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

int countPoints(char* rings) {
    int rods[10] = {0}; // Each rod will use 3 bits to represent R, G, B presence
    int n = strlen(rings);

    for (int i = 0; i < n; i += 2) {
        char color = rings[i];
        int rodIndex = rings[i + 1] - '0';

        if (color == 'R') {
            rods[rodIndex] |= 1; // Set bit 0 for Red
        } else if (color == 'G') {
            rods[rodIndex] |= 2; // Set bit 1 for Green
        } else if (color == 'B') {
            rods[rodIndex] |= 4; // Set bit 2 for Blue
        }
    }

    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (rods[i] == 7) { // Check if all three bits are set (1 | 2 | 4 = 7)
            count++;
        }
    }

    return count;       
}
