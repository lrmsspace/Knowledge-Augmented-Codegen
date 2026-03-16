// Source: https://leetcode.com/problems/concatenated-divisibility/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums and a positive integer k.
//
// A permutation of nums is said to form a divisible concatenation if, when you concatenate the decimal representations of the numbers in the order specified by the permutation, the resulting number is divisible by k.
//
// Return the lexicographically smallest permutation (when considered as a list of integers) that forms a divisible concatenation. If no such permutation exists, return an empty list.
//
// Example:
// Input: nums = [3,12,45], k = 5
//
// Output: [3,12,45]
//
// Explanation:
//
//
// 	
// 		
// 			Permutation
// 			Concatenated Value
// 			Divisible by 5
// 		
// 	
// 	
// 		
// 			[3, 12, 45]
// 			31245
// 			Yes
// 		
// 		
// 			[3, 45, 12]
// 			34512
// 			No
// 		
// 		
// 			[12, 3, 45]
// 			12345
// 			Yes
// 		
// 		
// 			[12, 45, 3]
// 			12453
// 			No
// 		
// 		
// 			[45, 3, 12]
// 			45312
// 			No
// 		
// 		
// 			[45, 12, 3]
// 			45123
// 			No
// 		
// 	
//
//
// The lexicographically smallest permutation that forms a divisible concatenation is [3,12,45].
//
// Constraints:
// 1 <= nums.length <= 13
// 	1 <= nums[i] <= 105
// 	1 <= k <= 100
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] concatenatedDivisibility(int[] nums, int k) {
        int n = nums.length;
        int[] mod = new int[n];
        int[] pow10 = new int[n];
        for (int i = 0; i < n; i++) {
            mod[i] = nums[i] % k;
            pow10[i] = 1;
            for (int j = 0; j < String.valueOf(nums[i]).length(); j++) {
                pow10[i] = (pow10[i] * 10) % k;
            }
        }

        List<Integer> result = new ArrayList<>();
        boolean[] used = new boolean[n];
        backtrack(nums, mod, pow10, k, used, 0, 0, result);
        return result.stream().mapToInt(i -> i).toArray();          
    }
}
