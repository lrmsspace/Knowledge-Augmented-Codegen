// Source: https://leetcode.com/problems/image-overlap/   |   Difficulty: Medium
//
// Problem Description:
// You are given two images, img1 and img2, represented as binary, square matrices of size n x n. A binary matrix has only 0s and 1s as values.
//
// We translate one image however we choose by sliding all the 1 bits left, right, up, and/or down any number of units. We then place it on top of the other image. We can then calculate the overlap by counting the number of positions that have a 1 in both images.
//
// Note also that a translation does not include any kind of rotation. Any 1 bits that are translated outside of the matrix borders are erased.
//
// Return the largest possible overlap.
//
// Example:
// Input: img1 = [[1,1,0],[0,1,0],[0,1,0]], img2 = [[0,0,0],[0,1,1],[0,0,1]]
// Output: 3
// Explanation: We translate img1 to right by 1 unit and down by 1 unit.
//
// The number of positions that have a 1 in both images is 3 (shown in red).
//
// Constraints:
// n == img1.length == img1[i].length
// 	n == img2.length == img2[i].length
// 	1 <= n <= 30
// 	img1[i][j] is either 0 or 1.
// 	img2[i][j] is either 0 or 1.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Finding the equation of a line for a segment (geometry, number, enumeration)
//   • When to use: Use when the problem asks to count or list all possible combinations, permutations, or arrangements of elements. It's suitable when a brute-force check of all possibilities is feasible.
//   • Idea: Enumeration systematically generates and examines all possible solutions to a problem. This approach guarantees finding the correct answer if one exists, typically with exponential time complexity O(k^N) or O(N!).
//   • Invariants: At each step, the current partial solution is valid according to problem constraints.; All previously explored partial solutions have been processed or discarded.
//   • Tips: Clearly define the search space and the properties of valid solutions.; Use recursion or iterative loops to explore all branches of the solution space.
//   • Pitfalls: Overlooking edge cases or constraints that limit the search space.; Generating duplicate solutions if not handled carefully.
// - Submask Enumeration
//  (number, bitset, enumeration)
//   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
//   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
//   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
//   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
//   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} img1
 * @param {number[][]} img2
 * @return {number}
 */
var largestOverlap = function(img1, img2) {
    const n = img1.length;
    let maxOverlap = 0;

    const countOverlap = (xShift, yShift) => {
        let overlap = 0;
        for (let i = 0; i < n; i++) {
            for (let j = 0; j < n; j++) {
                const img1X = i + xShift;
                const img1Y = j + yShift;
                if (img1X >= 0 && img1X < n && img1Y >= 0 && img1Y < n) {
                    overlap += img1[img1X][img1Y] * img2[i][j];
                }
            }
        }
        return overlap;
    };

    for (let xShift = -n + 1; xShift < n; xShift++) {
        for (let yShift = -n + 1; yShift < n; yShift++) {
            maxOverlap = Math.max(maxOverlap, countOverlap(xShift, yShift));
        }
    }

    return maxOverlap;
};
