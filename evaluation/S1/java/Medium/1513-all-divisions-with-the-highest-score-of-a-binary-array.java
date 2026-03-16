// Source: https://leetcode.com/problems/all-divisions-with-the-highest-score-of-a-binary-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed binary array nums of length n. nums can be divided at index i (where 0 <= i <= n) into two arrays (possibly empty) numsleft and numsright:
//
//
// 	numsleft has all the elements of nums between index 0 and i - 1 (inclusive), while numsright has all the elements of nums between index i and n - 1 (inclusive).
// 	If i == 0, numsleft is empty, while numsright has all the elements of nums.
// 	If i == n, numsleft has all the elements of nums, while numsright is empty.
//
//
// The division score of an index i is the sum of the number of 0's in numsleft and the number of 1's in numsright.
//
// Return all distinct indices that have the highest possible division score. You may return the answer in any order.
//
// Example:
// Input: nums = [0,0,1,0]
// Output: [2,4]
// Explanation: Division at index
// - 0: numsleft is []. numsright is [0,0,1,0]. The score is 0 + 1 = 1.
// - 1: numsleft is [0]. numsright is [0,1,0]. The score is 1 + 1 = 2.
// - 2: numsleft is [0,0]. numsright is [1,0]. The score is 2 + 1 = 3.
// - 3: numsleft is [0,0,1]. numsright is [0]. The score is 2 + 0 = 2.
// - 4: numsleft is [0,0,1,0]. numsright is []. The score is 3 + 0 = 3.
// Indices 2 and 4 both have the highest possible division score 3.
// Note the answer [4,2] would also be accepted.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	nums[i] is either 0 or 1.
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Finding the nearest pair of points (geometry, array, divide-and-conquer)
//   • When to use: Use this algorithm to efficiently find the pair of points with the minimum Euclidean distance among a given set of N points in a 2D plane. It is particularly effective for large datasets where an O(N^2) approach is too slow.
//   • Idea: This divide-and-conquer algorithm finds the closest pair of points in a 2D plane by recursively splitting the set of points and merging results. It achieves an optimal time complexity of O(N log N).
//   • Invariants: At the start of any recursive call, the input point set is sorted by X-coordinate.; The returned minimum distance 'd' for a subproblem is the true minimum distance among its points.
//   • Tips: Initial sorting by X-coordinate is crucial for efficient division of the point set.; Handle base cases (e.g., 2 or 3 points) with a simple brute-force distance calculation.
//   • Pitfalls: Forgetting to sort points by Y-coordinate within the central strip can degrade performance to O(N^2).; Incorrectly defining the strip width or comparison range in the merge step can lead to incorrect results.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Integer> maxScoreIndices(int[] nums) {
        int n = nums.length;
        int totalOnes = 0;
        for (int num : nums) {
            if (num == 1) {
                totalOnes++;
            }
        }

        int maxScore = totalOnes; // Initial score when i = 0
        List<Integer> result = new ArrayList<>();
        result.add(0);

        int zerosCount = 0;
        int onesCount = totalOnes;

        for (int i = 1; i <= n; i++) {
            if (nums[i - 1] == 0) {
                zerosCount++;
            } else {
                onesCount--;
            }

            int currentScore = zerosCount + onesCount;

            if (currentScore > maxScore) {
                maxScore = currentScore;
                result.clear();
                result.add(i);
            } else if (currentScore == maxScore) {
                result.add(i);
            }
        }

        return result;          
    }
}
