// Source: https://leetcode.com/problems/number-of-beautiful-integers-in-the-range/   |   Difficulty: Hard
//
// Problem Description:
// You are given positive integers low, high, and k.
//
// A number is beautiful if it meets both of the following conditions:
//
//
// 	The count of even digits in the number is equal to the count of odd digits.
// 	The number is divisible by k.
//
//
// Return the number of beautiful integers in the range [low, high].
//
// Example:
// Input: low = 10, high = 20, k = 3
// Output: 2
// Explanation: There are 2 beautiful integers in the given range: [12,18]. 
// - 12 is beautiful because it contains 1 odd digit and 1 even digit, and is divisible by k = 3.
// - 18 is beautiful because it contains 1 odd digit and 1 even digit, and is divisible by k = 3.
// Additionally we can see that:
// - 16 is not beautiful because it is not divisible by k = 3.
// - 15 is not beautiful because it does not contain equal counts even and odd digits.
// It can be shown that there are only 2 beautiful integers in the given range.
//
// Constraints:
// 0 < low <= high <= 109
// 	0 < k <= 20
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} low
 * @param {number} high
 * @param {number} k
 * @return {number}
 */
var numberOfBeautifulIntegers = function(low, high, k) {
    const countBeautiful = (num) => {
        const digits = String(num).split('').map(Number);
        const memo = new Map();
        
        const dfs = (index, evenCount, oddCount, mod, isTight) => {
            if (index === digits.length) {
                return evenCount === oddCount && mod === 0 ? 1 : 0;
            }
            
            const key = `${index}-${evenCount}-${oddCount}-${mod}-${isTight}`;
            if (memo.has(key)) return memo.get(key);
            
            const limit = isTight ? digits[index] : 9;
            let total = 0;
            
            for (let d = 0; d <= limit; d++) {
                total += dfs(
                    index + 1,
                    evenCount + (d % 2 === 0 ? 1 : 0),
                    oddCount + (d % 2 === 1 ? 1 : 0),
                    (mod * 10 + d) % k,
                    isTight && d === limit
                );
            }
            
            memo.set(key, total);
            return total;
        };
        
        return dfs(0, 0, 0, 0, true);
    };
    
    return countBeautiful(high) - countBeautiful(low - 1);
};
