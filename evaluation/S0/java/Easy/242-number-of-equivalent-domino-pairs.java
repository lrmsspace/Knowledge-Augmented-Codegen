// Source: https://leetcode.com/problems/number-of-equivalent-domino-pairs/   |   Difficulty: Easy
//
// Problem Description:
// Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d] if and only if either (a == c and b == d), or (a == d and b == c) - that is, one domino can be rotated to be equal to another domino.
//
// Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length, and dominoes[i] is equivalent to dominoes[j].
//
// Example:
// Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
// Output: 1
//
// Constraints:
// 1 <= dominoes.length <= 4 * 104
// 	dominoes[i].length == 2
// 	1 <= dominoes[i][j] <= 9
//

class Solution {
    public int numEquivDominoPairs(int[][] dominoes) {
        int[] count = new int[100];
        int result = 0;

        for (int[] domino : dominoes) {
            int a = Math.min(domino[0], domino[1]);
            int b = Math.max(domino[0], domino[1]);
            int key = a * 10 + b;

            result += count[key];
            count[key]++;
        }

        return result;          
    }
}
