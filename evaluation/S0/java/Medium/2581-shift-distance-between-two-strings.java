// Source: https://leetcode.com/problems/shift-distance-between-two-strings/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s and t of the same length, and two integer arrays nextCost and previousCost.
//
// In one operation, you can pick any index i of s, and perform either one of the following actions:
//
//
// 	Shift s[i] to the next letter in the alphabet. If s[i] == 'z', you should replace it with 'a'. This operation costs nextCost[j] where j is the index of s[i] in the alphabet.
// 	Shift s[i] to the previous letter in the alphabet. If s[i] == 'a', you should replace it with 'z'. This operation costs previousCost[j] where j is the index of s[i] in the alphabet.
//
//
// The shift distance is the minimum total cost of operations required to transform s into t.
//
// Return the shift distance from s to t.
//
// Example:
// Input: s = "abab", t = "baba", nextCost = [100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0], previousCost = [1,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
//
// Output: 2
//
// Explanation:
//
//
// 	We choose index i = 0 and shift s[0] 25 times to the previous character for a total cost of 1.
// 	We choose index i = 1 and shift s[1] 25 times to the next character for a total cost of 0.
// 	We choose index i = 2 and shift s[2] 25 times to the previous character for a total cost of 1.
// 	We choose index i = 3 and shift s[3] 25 times to the next character for a total cost of 0.
//
// Constraints:
// 1 <= s.length == t.length <= 105
// 	s and t consist only of lowercase English letters.
// 	nextCost.length == previousCost.length == 26
// 	0 <= nextCost[i], previousCost[i] <= 109
//

class Solution {
    public long shiftDistance(String s, String t, int[] nextCost, int[] previousCost) {
        long totalCost = 0;
        int n = s.length();

        for (int i = 0; i < n; i++) {
            char charS = s.charAt(i);
            char charT = t.charAt(i);

            if (charS == charT) {
                continue;
            }

            int indexS = charS - 'a';
            int indexT = charT - 'a';

            long costForward = 0;
            long costBackward = 0;

            // Calculate cost for forward shifts
            int currentIndex = indexS;
            while (currentIndex != indexT) {
                costForward += nextCost[currentIndex];
                currentIndex = (currentIndex + 1) % 26;
            }

            // Calculate cost for backward shifts
            currentIndex = indexS;
            while (currentIndex != indexT) {
                costBackward += previousCost[currentIndex];
                currentIndex = (currentIndex - 1 + 26) % 26;
            }

            totalCost += Math.min(costForward, costBackward);
        }

        return totalCost;           
    }
}
