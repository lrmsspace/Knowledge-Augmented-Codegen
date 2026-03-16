// Source: https://leetcode.com/problems/minimum-swaps-to-sort-by-digit-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of distinct positive integers. You need to sort the array in increasing order based on the sum of the digits of each number. If two numbers have the same digit sum, the smaller number appears first in the sorted order.
//
// Return the minimum number of swaps required to rearrange nums into this sorted order.
//
// A swap is defined as exchanging the values at two distinct positions in the array.
//
// Example:
// Input: nums = [37,100]
//
// Output: 1
//
// Explanation:
//
//
// 	Compute the digit sum for each integer: [3 + 7 = 10, 1 + 0 + 0 = 1] → [10, 1]
// 	Sort the integers based on digit sum: [100, 37]. Swap 37 with 100 to obtain the sorted order.
// 	Thus, the minimum number of swaps required to rearrange nums is 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	nums consists of distinct positive integers.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Elementary Sorts (array, enumeration)
//   • When to use: Selection sort is simple but inefficient. It's suitable for very small datasets or educational purposes where simplicity of implementation is prioritized over performance.
//   • Idea: Selection sort repeatedly finds the minimum element from the unsorted portion of the array and places it at the beginning of the sorted portion. It has a time complexity of O(N^2) and a space complexity of O(1).
//   • Invariants: The elements in the prefix of the array are sorted.; All elements in the sorted prefix are less than or equal to all elements in the unsorted suffix.
//   • Tips: Easy to understand and implement.; Performs a minimal number of swaps (exactly N-1 swaps).
//   • Pitfalls: Inefficient for large datasets due to O(N^2) time complexity.; Performance is not affected by the initial order of elements.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var minSwaps = function(nums) {
    const n = nums.length;
    // Create an array of objects with original index and digit sum
    const arr = nums.map((num, index) => {
        const digitSum = num.toString().split('').reduce((sum, digit) => sum + parseInt(digit), 0);
        return { index, digitSum, value: num };
    });

    // Sort the array based on digit sum and then by value
    arr.sort((a, b) => {
        if (a.digitSum === b.digitSum) {
            return a.value - b.value; // If digit sums are equal, sort by value
        }
        return a.digitSum - b.digitSum; // Sort by digit sum
    });

    // Create an array to track visited elements for cycle detection
    const visited = new Array(n).fill(false);
    let swaps = 0;

    for (let i = 0; i < n; i++) {
        if (visited[i] || arr[i].index === i) {
            continue; // Skip already visited or correctly placed elements
        }

        let cycleSize = 0;
        let j = i;

        // Count the size of the cycle
        while (!visited[j]) {
            visited[j] = true;
            j = arr[j].index; // Move to the next index in the cycle
            cycleSize++;
        }

        // If there is a cycle of size k, we need k-1 swaps to arrange it
        if (cycleSize > 1) {
            swaps += (cycleSize - 1);
        }
    }

    return swaps;
};
