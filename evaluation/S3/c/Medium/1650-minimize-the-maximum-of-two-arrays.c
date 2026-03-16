// Source: https://leetcode.com/problems/minimize-the-maximum-of-two-arrays/   |   Difficulty: Medium
//
// Problem Description:
// We have two arrays arr1 and arr2 which are initially empty. You need to add positive integers to them such that they satisfy all the following conditions:
//
//
// 	arr1 contains uniqueCnt1 distinct positive integers, each of which is not divisible by divisor1.
// 	arr2 contains uniqueCnt2 distinct positive integers, each of which is not divisible by divisor2.
// 	No integer is present in both arr1 and arr2.
//
//
// Given divisor1, divisor2, uniqueCnt1, and uniqueCnt2, return the minimum possible maximum integer that can be present in either array.
//
// Example:
// Input: divisor1 = 2, divisor2 = 7, uniqueCnt1 = 1, uniqueCnt2 = 3
// Output: 4
// Explanation: 
// We can distribute the first 4 natural numbers into arr1 and arr2.
// arr1 = [1] and arr2 = [2,3,4].
// We can see that both arrays satisfy all the conditions.
// Since the maximum value is 4, we return it.
//
// Constraints:
// 2 <= divisor1, divisor2 <= 105
// 	1 <= uniqueCnt1, uniqueCnt2 < 109
// 	2 <= uniqueCnt1 + uniqueCnt2 <= 109
//
// Helpful references (internal KB):
// - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
//   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
//   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
//   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
//   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
//   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimizeSet(int divisor1, int divisor2, int uniqueCnt1, int uniqueCnt2) {
    long long lcm = (long long)divisor1 * divisor2 / gcd(divisor1, divisor2);
    long long low = 1, high = 2LL * (uniqueCnt1 + uniqueCnt2);
    
    while (low < high) {
        long long mid = low + (high - low) / 2;
        long long count1 = mid - mid / divisor1 - mid / lcm;
        long long count2 = mid - mid / divisor2 - mid / lcm;
        
        if (count1 >= uniqueCnt1 && count2 >= uniqueCnt2) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    return (int)low;        
}
