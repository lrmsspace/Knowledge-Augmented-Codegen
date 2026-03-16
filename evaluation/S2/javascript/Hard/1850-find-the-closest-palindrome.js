// Source: https://leetcode.com/problems/find-the-closest-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.
//
// The closest is defined as the absolute difference minimized between two integers.
//
// Example:
// Input: n = "123"
// Output: "121"
//
// Constraints:
// 1 <= n.length <= 18
// 	n consists of only digits.
// 	n does not have leading zeros.
// 	n is representing an integer in the range [1, 1018 - 1].
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Gray code (number, prefix-xor)
//   • When to use: Use when a sequence of binary numbers is needed where successive values differ by only one bit. This is useful for error detection in digital systems or position encoders.
//   • Idea: Gray code is a binary numeral system where two successive values differ in only one bit position. Conversion from a binary number `n` to its Gray code `G(n)` is `n ^ (n >> 1)`, and the inverse operation can also be performed efficiently in O(log N) time.
//   • Invariants: For binary to Gray: The resulting Gray code `G(n)` differs from `n` by exactly one bit for each `n`.; For inverse Gray to binary: The variable `n` accumulates the correct binary value from MSB to LSB.
//   • Tips: Understand the core `n ^ (n >> 1)` transformation for binary to Gray.; The inverse Gray code conversion involves iteratively XORing with right-shifted values.
//   • Pitfalls: Confusing Gray code with standard binary representation.; Incorrectly implementing the iterative inverse transformation logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} n
 * @return {string}
 */
var nearestPalindromic = function(n) {
    const length = n.length;
    const candidates = new Set();
    
    // Edge cases: 10...0, 9...9, 100...001
    candidates.add(String(BigInt(10) ** BigInt(length - 1) - BigInt(1))); // 999...9
    candidates.add(String(BigInt(10) ** BigInt(length) + BigInt(1)));     // 100...001
    
    const prefix = n.slice(0, Math.ceil(length / 2));
    const prefixNum = BigInt(prefix);
    
    for (let i = -1; i <= 1; i++) {
        const newPrefix = String(prefixNum + BigInt(i));
        let candidate;
        
        if (length % 2 === 0) {
            candidate = newPrefix + newPrefix.split('').reverse().join('');
        } else {
            candidate = newPrefix + newPrefix.slice(0, -1).split('').reverse().join('');
        }
        
        candidates.add(candidate);
    }
    
    let closest = null;
    const nNum = BigInt(n);
    
    for (const candidate of candidates) {
        if (candidate === n) continue;
        
        const candidateNum = BigInt(candidate);
        const diff = candidateNum > nNum ? candidateNum - nNum : nNum - candidateNum;
        
        if (closest === null || diff < closest.diff || (diff === closest.diff && candidateNum < closest.num)) {
            closest = { num: candidateNum, diff };
        }
    }
    
    return String(closest.num);
};
