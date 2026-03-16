// Source: https://leetcode.com/problems/count-square-sum-triples/   |   Difficulty: Easy
//
// Problem Description:
// A square triple (a,b,c) is a triple where a, b, and c are integers and a2 + b2 = c2.
//
// Given an integer n, return the number of square triples such that 1 <= a, b, c <= n.
//
// Example:
// Input: n = 5
// Output: 2
// Explanation: The square triples are (3,4,5) and (4,3,5).
//
// Constraints:
// 1 <= n <= 250
//

class Solution {
    public int countTriples(int n) {
        int count = 0;
        for (int a = 1; a <= n; a++) {
            for (int b = 1; b <= n; b++) {
                int cSquare = a * a + b * b;
                int c = (int) Math.sqrt(cSquare);
                if (c * c == cSquare && c <= n) {
                    count++;
                }
            }
        }
        return count;           
    }
}
