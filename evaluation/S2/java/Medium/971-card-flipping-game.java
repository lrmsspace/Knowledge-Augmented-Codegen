// Source: https://leetcode.com/problems/card-flipping-game/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed integer arrays fronts and backs of length n, where the ith card has the positive integer fronts[i] printed on the front and backs[i] printed on the back. Initially, each card is placed on a table such that the front number is facing up and the other is facing down. You may flip over any number of cards (possibly zero).
//
// After flipping the cards, an integer is considered good if it is facing down on some card and not facing up on any card.
//
// Return the minimum possible good integer after flipping the cards. If there are no good integers, return 0.
//
// Example:
// Input: fronts = [1,2,4,4,7], backs = [1,3,4,1,3]
// Output: 2
// Explanation:
// If we flip the second card, the face up numbers are [1,3,4,4,7] and the face down are [1,2,4,1,3].
// 2 is the minimum good integer as it appears facing down but not facing up.
// It can be shown that 2 is the minimum possible good integer obtainable after flipping some cards.
//
// Constraints:
// n == fronts.length == backs.length
// 	1 <= n <= 1000
// 	1 <= fronts[i], backs[i] <= 2000
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int flipgame(int[] fronts, int[] backs) {
        int n = fronts.length;
        Set<Integer> same = new HashSet<>();
        for (int i = 0; i < n; i++) {
            if (fronts[i] == backs[i]) {
                same.add(fronts[i]);
            }
        }

        int ans = Integer.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            if (!same.contains(fronts[i])) {
                ans = Math.min(ans, fronts[i]);
            }
            if (!same.contains(backs[i])) {
                ans = Math.min(ans, backs[i]);
            }
        }

        return ans == Integer.MAX_VALUE ? 0 : ans;          
    }
}
