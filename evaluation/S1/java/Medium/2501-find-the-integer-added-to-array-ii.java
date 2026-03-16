// Source: https://leetcode.com/problems/find-the-integer-added-to-array-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2.
//
// From nums1 two elements have been removed, and all other elements have been increased (or decreased in the case of negative) by an integer, represented by the variable x.
//
// As a result, nums1 becomes equal to nums2. Two arrays are considered equal when they contain the same integers with the same frequencies.
//
// Return the minimum possible integer x that achieves this equivalence.
//
// Example:
// Input: nums1 = [4,20,16,12,8], nums2 = [14,18,10]
//
// Output: -2
//
// Explanation:
//
// After removing elements at indices [0,4] and adding -2, nums1 becomes [18,14,10].
//
// Constraints:
// 3 <= nums1.length <= 200
// 	nums2.length == nums1.length - 2
// 	0 <= nums1[i], nums2[i] <= 1000
// 	The test cases are generated in a way that there is an integer x such that nums1 can become equal to nums2 by removing two elements and adding x to each element of nums1.
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Circle-Circle Intersection (geometry, number, simulation, enumeration)
//   • When to use: Use this algorithm to find the common points where two circles intersect on a 2D plane, handling cases from no intersection to infinite points.
//   • Idea: This algorithm determines the intersection points of two circles by algebraically transforming their equations into a system involving one circle and one line. It typically achieves O(1) time complexity for finding the intersection points.
//   • Invariants: The relative positions and radii of the circles remain unchanged after coordinate translation.; The derived linear equation represents the radical axis of the two circles.
//   • Tips: Translate one circle to the origin to simplify the equations.; Subtract the two circle equations to derive a linear equation (the radical axis).
//   • Pitfalls: Numerical instability due to floating-point arithmetic, especially for tangent cases.; Forgetting to translate the resulting intersection points back to the original coordinate system.
// - Stars and bars (number, counting)
//   • When to use: Use when counting the number of ways to distribute identical items into distinct bins, or finding the number of non-negative integer solutions to a linear equation. It is also applicable for problems with lower bounds on variables.
//   • Idea: Stars and bars is a combinatorial technique used to count the number of ways to place 'n' identical items into 'k' distinct bins, or equivalently, to find the number of non-negative integer solutions to x1 + ... + xk = n.
//   • Invariants: The total number of 'stars' (items) remains constant throughout any transformation.; The number of 'bars' (separators) is always one less than the number of bins (variables).
//   • Tips: Visualize items as 'stars' and separators as 'bars' to understand the arrangement.; Transform problems with lower bounds (x_i >= a_i) into non-negative solutions (x_i' >= 0).
//   • Pitfalls: Confusing identical items with distinct items, which requires a different counting method.; Incorrectly applying the formula when variables have lower bounds other than zero without transformation.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumAddedInteger(int[] nums1, int[] nums2) {
        java.util.Arrays.sort(nums1);
        java.util.Arrays.sort(nums2);

        int n = nums1.length;
        int m = nums2.length;

        int minX = Integer.MAX_VALUE;

        // Try removing every pair of elements from nums1
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // Calculate the potential x
                int x = nums2[0] - nums1[(i == 0 ? 1 : 0)];

                // Create a frequency map for nums2
                java.util.Map<Integer, Integer> freqMap = new java.util.HashMap<>();
                for (int num : nums2) {
                    freqMap.put(num, freqMap.getOrDefault(num, 0) + 1);
                }

                // Check if removing nums1[i] and nums1[j] and adding x makes nums1 equal to nums2
                boolean valid = true;
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) continue;
                    int transformedValue = nums1[k] + x;
                    if (!freqMap.containsKey(transformedValue) || freqMap.get(transformedValue) == 0) {
                        valid = false;
                        break;
                    }
                    freqMap.put(transformedValue, freqMap.get(transformedValue) - 1);
                }
                if (valid) {
                    minX = Math.min(minX, x);
                }
            }
        }
        return minX;
    }
}
