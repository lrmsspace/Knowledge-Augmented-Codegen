// Source: https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/   |   Difficulty: Hard
//
// Problem Description:
// Given an array nums that represents a permutation of integers from 1 to n. We are going to construct a binary search tree (BST) by inserting the elements of nums in order into an initially empty BST. Find the number of different ways to reorder nums so that the constructed BST is identical to that formed from the original array nums.
//
//
// 	For example, given nums = [2,1,3], we will have 2 as the root, 1 as a left child, and 3 as a right child. The array [2,3,1] also yields the same BST but [3,2,1] yields a different BST.
//
//
// Return the number of ways to reorder nums such that the BST formed is identical to the original BST formed from nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,1,3]
// Output: 1
// Explanation: We can reorder nums to be [2,3,1] which will yield the same BST. There are no other ways to reorder nums which will yield the same BST.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= nums.length
// 	All integers in nums are distinct.
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, number, mod-exp, enumeration)
//   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
//   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
//   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
//   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
//   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
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
var numOfWays = function(nums) {
    const mod = 1e9 + 7;

    const factorial = [1];
    for (let i = 1; i <= nums.length; i++) {
        factorial[i] = (factorial[i - 1] * i) % mod;
    }

    const inverseFactorial = [1];
    for (let i = 1; i <= nums.length; i++) {
        inverseFactorial[i] = modExp(factorial[i], mod - 2, mod);
    }

    const binomialCoefficient = (n, k) => {
        if (k > n || k < 0) return 0;
        return (factorial[n] * inverseFactorial[k] % mod) * inverseFactorial[n - k] % mod;
    };

    const countWays = (arr) => {
        if (arr.length <= 2) return 1;

        const root = arr[0];
        const leftSubtree = arr.filter(x => x < root);
        const rightSubtree = arr.filter(x => x > root);

        const leftWays = countWays(leftSubtree);
        const rightWays = countWays(rightSubtree);

        return (binomialCoefficient(leftSubtree.length + rightSubtree.length, leftSubtree.length) * leftWays % mod) * rightWays % mod;
    };

    return (countWays(nums) - 1 + mod) % mod;
};
