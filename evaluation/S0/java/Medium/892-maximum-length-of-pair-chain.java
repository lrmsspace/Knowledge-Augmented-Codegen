// Source: https://leetcode.com/problems/maximum-length-of-pair-chain/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of n pairs pairs where pairs[i] = [lefti, righti] and lefti < righti.
//
// A pair p2 = [c, d] follows a pair p1 = [a, b] if b < c. A chain of pairs can be formed in this fashion.
//
// Return the length longest chain which can be formed.
//
// You do not need to use up all the given intervals. You can select pairs in any order.
//
// Example:
// Input: pairs = [[1,2],[2,3],[3,4]]
// Output: 2
// Explanation: The longest chain is [1,2] -> [3,4].
//
// Constraints:
// n == pairs.length
// 	1 <= n <= 1000
// 	-1000 <= lefti < righti <= 1000
//

class Solution {
    public int findLongestChain(int[][] pairs) {
        // Sort pairs based on their second element
        Arrays.sort(pairs, (a, b) -> Integer.compare(a[1], b[1]));

        int count = 0;
        int currentEnd = Integer.MIN_VALUE;

        for (int[] pair : pairs) {
            // If the current pair can be chained
            if (pair[0] > currentEnd) {
                count++;
                currentEnd = pair[1]; // Update the end to the current pair's end
            }
        }

        return count;           
    }
}
