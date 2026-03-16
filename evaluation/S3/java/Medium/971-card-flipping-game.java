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
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
// - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
//   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
//   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
//   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
//   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int flipgame(int[] fronts, int[] backs) {
        // Step 1: Identify numbers that are the same on both sides of any card, as they cannot be good integers.
        Set<Integer> sameNumbers = new HashSet<>();
        for (int i = 0; i < fronts.length; i++) {
            if (fronts[i] == backs[i]) {
                sameNumbers.add(fronts[i]);
            }
        }

        // Step 2: Find the minimum good integer that is not in the sameNumbers set.
        int minGoodInteger = Integer.MAX_VALUE;
        for (int num : fronts) {
            if (!sameNumbers.contains(num)) {
                minGoodInteger = Math.min(minGoodInteger, num);
            }
        }
        for (int num : backs) {
            if (!sameNumbers.contains(num)) {
                minGoodInteger = Math.min(minGoodInteger, num);
            }
        }

        // Step 3: Return the minimum good integer or 0 if none found.
        return minGoodInteger == Integer.MAX_VALUE ? 0 : minGoodInteger;            
    }
}
