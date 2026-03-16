// Source: https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given three positive integers: n, index, and maxSum. You want to construct an array nums (0-indexed) that satisfies the following conditions:
//
//
// 	nums.length == n
// 	nums[i] is a positive integer where 0 <= i < n.
// 	abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
// 	The sum of all the elements of nums does not exceed maxSum.
// 	nums[index] is maximized.
//
//
// Return nums[index] of the constructed array.
//
// Note that abs(x) equals x if x >= 0, and -x otherwise.
//
// Example:
// Input: n = 4, index = 2,  maxSum = 6
// Output: 2
// Explanation: nums = [1,2,2,1] is one array that satisfies all the conditions.
// There are no arrays that satisfy all the conditions and have nums[2] == 3, so 2 is the maximum nums[2].
//
// Constraints:
// 1 <= n <= maxSum <= 109
// 	0 <= index < n
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxValue(int n, int index, int maxSum) {
    long left = 1, right = maxSum;
    long result = 0;

    while (left <= right) {
        long mid = left + (right - left) / 2;
        long total = mid;

        // Calculate left side sum
        if (mid > index) {
            long first = mid - index;
            long last = mid - 1;
            total += (first + last) * index / 2;
        } else {
            long first = 1;
            long last = mid - 1;
            total += (first + last) * (mid - 1) / 2;
            total += index - (mid - 1);
        }

        // Calculate right side sum
        if (mid > n - index - 1) {
            long first = mid - (n - index - 1);
            long last = mid - 1;
            total += (first + last) * (n - index - 1) / 2;
        } else {
            long first = 1;
            long last = mid - 1;
            total += (first + last) * (mid - 1) / 2;
            total += (n - index - 1) - (mid - 1);
        }

        if (total <= maxSum) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return (int)result;     
}
