// Source: https://leetcode.com/problems/minimum-operations-to-make-array-equal/   |   Difficulty: Medium
//
// Problem Description:
// You have an array arr of length n where arr[i] = (2 * i) + 1 for all valid values of i (i.e., 0 <= i < n).
//
// In one operation, you can select two indices x and y where 0 <= x, y < n and subtract 1 from arr[x] and add 1 to arr[y] (i.e., perform arr[x] -=1 and arr[y] += 1). The goal is to make all the elements of the array equal. It is guaranteed that all the elements of the array can be made equal using some operations.
//
// Given an integer n, the length of the array, return the minimum number of operations needed to make all the elements of arr equal.
//
// Example:
// Input: n = 3
// Output: 2
// Explanation: arr = [1, 3, 5]
// First operation choose x = 2 and y = 0, this leads arr to be [2, 3, 4]
// In the second operation choose x = 2 and y = 0 again, thus arr = [3, 3, 3].
//
// Constraints:
// 1 <= n <= 104
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @return {number}
 */
var minOperations = function(n) {
	const target = n; // Since the array elements are (2*i + 1), the target value for all elements will be n.
	let operations = 0;

	for (let i = 0; i < n; i++) {
		const currentValue = (2 * i) + 1;
		if (currentValue < target) {
			operations += target - currentValue; // Only consider operations for elements less than the target.
		}
	}

	return operations;
};
