// Source: https://leetcode.com/problems/abbreviating-the-product-of-a-range/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers left and right with left <= right. Calculate the product of all integers in the inclusive range [left, right].
//
// Since the product may be very large, you will abbreviate it following these steps:
//
//
// 	Count all trailing zeros in the product and remove them. Let us denote this count as C.
//
// 	
// 		For example, there are 3 trailing zeros in 1000, and there are 0 trailing zeros in 546.
// 	
// 	
// 	Denote the remaining number of digits in the product as d. If d > 10, then express the product as <pre>...<suf> where <pre> denotes the first 5 digits of the product, and <suf> denotes the last 5 digits of the product after removing all trailing zeros. If d <= 10, we keep it unchanged.
// 	
// 		For example, we express 1234567654321 as 12345...54321, but 1234567 is represented as 1234567.
// 	
// 	
// 	Finally, represent the product as a string "<pre>...<suf>eC".
// 	
// 		For example, 12345678987600000 will be represented as "12345...89876e5".
// 	
// 	
//
//
// Return a string denoting the abbreviated product of all integers in the inclusive range [left, right].
//
// Example:
// Input: left = 1, right = 4
// Output: "24e0"
// Explanation: The product is 1 × 2 × 3 × 4 = 24.
// There are no trailing zeros, so 24 remains the same. The abbreviation will end with "e0".
// Since the number of digits is 2, which is less than 10, we do not have to abbreviate it further.
// Thus, the final representation is "24e0".
//
// Constraints:
// 1 <= left <= right <= 104
//
// Helpful references (internal KB):
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} left
 * @param {number} right
 * @return {string}
 */
var abbreviateProduct = function(left, right) {
    let trailingZeros = 0;
    let leadingDigits = 1;
    let trailingDigits = 1;

    for (let i = left; i <= right; i++) {
        let num = i;

        while (num % 10 === 0) {
            trailingZeros++;
            num /= 10;
        }

        leadingDigits = (leadingDigits * num) % 100000;
        trailingDigits = (trailingDigits * num) % 100000;
    }

    const leadingStr = leadingDigits.toString().padStart(5, '0');
    const trailingStr = trailingDigits.toString().padStart(5, '0');
    return `${leadingStr}...${trailingStr}e${trailingZeros}`;
};
