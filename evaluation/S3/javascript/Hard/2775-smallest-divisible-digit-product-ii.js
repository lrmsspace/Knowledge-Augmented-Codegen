// Source: https://leetcode.com/problems/smallest-divisible-digit-product-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string num which represents a positive integer, and an integer t.
//
// A number is called zero-free if none of its digits are 0.
//
// Return a string representing the smallest zero-free number greater than or equal to num such that the product of its digits is divisible by t. If no such number exists, return "-1".
//
// Example:
// Input: num = "1234", t = 256
//
// Output: "1488"
//
// Explanation:
//
// The smallest zero-free number that is greater than 1234 and has the product of its digits divisible by 256 is 1488, with the product of its digits equal to 256.
//
// Constraints:
// 2 <= num.length <= 2 * 105
// 	num consists only of digits in the range ['0', '9'].
// 	num does not contain leading zeros.
// 	1 <= t <= 1014
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Integer factorization (number, array, enumeration, sieve, counting)
//   • When to use: Use when needing to find the prime factors of a composite number, especially for relatively small numbers or as a base case for more advanced algorithms.
//   • Idea: This algorithm finds the prime factorization of an integer by iteratively dividing it by its smallest prime factors. It typically checks divisors up to the square root of the number, achieving an O(sqrt(N)) time complexity.
//   • Invariants: The product of all found prime factors multiplied by the current remaining number equals the original input number.; All prime factors found so far are less than or equal to the current divisor being tested.
//   • Tips: Perform a primality test first to avoid unnecessary factorization attempts.; Only check divisors up to the square root of the number.
//   • Pitfalls: Trial division is pseudo-polynomial time, making it inefficient for very large numbers.; Forgetting to handle the case where the remaining number after division is itself a prime greater than its original square root.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} num
 * @param {number} t
 * @return {string}
 */
var smallestNumber = function(num, t) {
    // Factor t into its prime factors and count their occurrences
    const primeFactors = {};
    let tempT = t;
    for (let i = 2; i * i <= tempT; i++) {
        while (tempT % i === 0) {
            primeFactors[i] = (primeFactors[i] || 0) + 1;
            tempT /= i;
        }
    }
    if (tempT > 1) {
        primeFactors[tempT] = (primeFactors[tempT] || 0) + 1;
    }

    // Calculate the required counts of digits to satisfy the divisibility by t
    const digitCounts = new Array(10).fill(0);
    for (const [prime, count] of Object.entries(primeFactors)) {
        let remainingCount = count;
        for (let digit = 9; digit >= 2; digit--) {
            while (remainingCount > 0 && isDivisibleByDigit(prime, digit)) {
                const factorCount = countFactorsOfDigit(prime, digit);
                if (factorCount > 0) {
                    const times = Math.min(Math.floor(remainingCount / factorCount), 1);
                    digitCounts[digit] += times;
                    remainingCount -= times * factorCount;
                } else {
                    break;
                }
            }
        }
        if (remainingCount > 0) {
            return "-1"; // Not possible to satisfy the condition
        }
    }

    // Construct the smallest number based on the required digit counts
    let result = '';
    for (let digit = 1; digit <= 9; digit++) {
        result += digit.toString().repeat(digitCounts[digit]);
    }

    // Ensure the constructed number is greater than or equal to num
    if (result.length < num.length || (result.length === num.length && result < num)) {
        return "-1";
    }

    return result;

    function isDivisibleByDigit(prime, digit) {
        let product = 1;
        for (let d = 2; d <= digit; d++) {
            product *= d;
            if (product % prime === 0) {
                return true;
            }
        }
        return false;
    }

    function countFactorsOfDigit(prime, digit) {
        let count = 0;
        let product = 1;
        for (let d = 2; d <= digit; d++) {
            product *= d;
            while (product % prime === 0) {
                count++;
                product /= prime;
            }
        }
        return count;
    }
    
};
