// Source: https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums where the ith bag contains nums[i] balls. You are also given an integer maxOperations.
//
// You can perform the following operation at most maxOperations times:
//
//
// 	Take any bag of balls and divide it into two new bags with a positive number of balls.
//
// 	
// 		For example, a bag of 5 balls can become two new bags of 1 and 4 balls, or two new bags of 2 and 3 balls.
// 	
// 	
//
//
// Your penalty is the maximum number of balls in a bag. You want to minimize your penalty after the operations.
//
// Return the minimum possible penalty after performing the operations.
//
// Example:
// Input: nums = [9], maxOperations = 2
// Output: 3
// Explanation: 
// - Divide the bag with 9 balls into two bags of sizes 6 and 3. [9] -> [6,3].
// - Divide the bag with 6 balls into two bags of sizes 3 and 3. [6,3] -> [3,3,3].
// The bag with the most number of balls has 3 balls, so your penalty is 3 and you should return 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= maxOperations, nums[i] <= 109
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Finding the equation of a line for a segment (geometry, number, enumeration)
//   • When to use: Use when the problem asks to count or list all possible combinations, permutations, or arrangements of elements. It's suitable when a brute-force check of all possibilities is feasible.
//   • Idea: Enumeration systematically generates and examines all possible solutions to a problem. This approach guarantees finding the correct answer if one exists, typically with exponential time complexity O(k^N) or O(N!).
//   • Invariants: At each step, the current partial solution is valid according to problem constraints.; All previously explored partial solutions have been processed or discarded.
//   • Tips: Clearly define the search space and the properties of valid solutions.; Use recursion or iterative loops to explore all branches of the solution space.
//   • Pitfalls: Overlooking edge cases or constraints that limit the search space.; Generating duplicate solutions if not handled carefully.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumSize(int* nums, int numsSize, int maxOperations) {
    int left = 1, right = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > right) {
            right = nums[i];
        }
    }

    while (left < right) {
        int mid = left + (right - left) / 2;
        long operationsNeeded = 0;

        for (int i = 0; i < numsSize; i++) {
            operationsNeeded += (nums[i] - 1) / mid; // Calculate the number of operations needed for this bag
            if (operationsNeeded > maxOperations) { // Early exit if we already exceed maxOperations
                break;
            }
        }

        if (operationsNeeded > maxOperations) {
            left = mid + 1; // Need a larger maximum bag size
        } else {
            right = mid; // Try a smaller maximum bag size
        }
    }

    return left; // At the end of the loop, left == right, which is the minimum possible penalty        
}
