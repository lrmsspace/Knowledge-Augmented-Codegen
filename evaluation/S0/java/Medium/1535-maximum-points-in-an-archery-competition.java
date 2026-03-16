// Source: https://leetcode.com/problems/maximum-points-in-an-archery-competition/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob are opponents in an archery competition. The competition has set the following rules:
//
//
// 	Alice first shoots numArrows arrows and then Bob shoots numArrows arrows.
// 	The points are then calculated as follows:
// 	
// 		The target has integer scoring sections ranging from 0 to 11 inclusive.
// 		For each section of the target with score k (in between 0 to 11), say Alice and Bob have shot ak and bk arrows on that section respectively. If ak >= bk, then Alice takes k points. If ak < bk, then Bob takes k points.
// 		However, if ak == bk == 0, then nobody takes k points.
// 	
// 	
//
//
//
// 	
// 	For example, if Alice and Bob both shot 2 arrows on the section with score 11, then Alice takes 11 points. On the other hand, if Alice shot 0 arrows on the section with score 11 and Bob shot 2 arrows on that same section, then Bob takes 11 points.
// 	
//
//
// You are given the integer numArrows and an integer array aliceArrows of size 12, which represents the number of arrows Alice shot on each scoring section from 0 to 11. Now, Bob wants to maximize the total number of points he can obtain.
//
// Return the array bobArrows which represents the number of arrows Bob shot on each scoring section from 0 to 11. The sum of the values in bobArrows should equal numArrows.
//
// If there are multiple ways for Bob to earn the maximum total points, return any one of them.
//
// Example:
// Input: numArrows = 9, aliceArrows = [1,1,0,1,0,0,2,1,0,1,2,0]
// Output: [0,0,0,0,1,1,0,0,1,2,3,1]
// Explanation: The table above shows how the competition is scored. 
// Bob earns a total point of 4 + 5 + 8 + 9 + 10 + 11 = 47.
// It can be shown that Bob cannot obtain a score higher than 47 points.
//
// Constraints:
// 1 <= numArrows <= 105
// 	aliceArrows.length == bobArrows.length == 12
// 	0 <= aliceArrows[i], bobArrows[i] <= numArrows
// 	sum(aliceArrows[i]) == numArrows
//

class Solution {
    public int[] maximumBobPoints(int numArrows, int[] aliceArrows) {
        int n = 12;
        int maxScore = 0;
        int bestMask = 0;

        for (int mask = 0; mask < (1 << n); mask++) {
            int arrowsUsed = 0;
            int score = 0;

            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) != 0) {
                    arrowsUsed += aliceArrows[i] + 1;
                    score += i;
                }
            }

            if (arrowsUsed <= numArrows && score > maxScore) {
                maxScore = score;
                bestMask = mask;
            }
        }

        int[] bobArrows = new int[n];
        int arrowsLeft = numArrows;

        for (int i = 0; i < n; i++) {
            if ((bestMask & (1 << i)) != 0) {
                bobArrows[i] = aliceArrows[i] + 1;
                arrowsLeft -= bobArrows[i];
            }
        }

        bobArrows[0] += arrowsLeft; // Assign any remaining arrows to section 0

        return bobArrows;           
    }
}
