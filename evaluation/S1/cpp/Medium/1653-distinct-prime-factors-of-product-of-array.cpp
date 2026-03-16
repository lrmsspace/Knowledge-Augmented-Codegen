// Source: https://leetcode.com/problems/distinct-prime-factors-of-product-of-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of positive integers nums, return the number of distinct prime factors in the product of the elements of nums.
//
// Note that:
//
//
// 	A number greater than 1 is called prime if it is divisible by only 1 and itself.
// 	An integer val1 is a factor of another integer val2 if val2 / val1 is an integer.
//
// Example:
// Input: nums = [2,4,3,7,10,6]
// Output: 4
// Explanation:
// The product of all the elements in nums is: 2 * 4 * 3 * 7 * 10 * 6 = 10080 = 25 * 32 * 5 * 7.
// There are 4 distinct prime factors so we return 4.
//
// Constraints:
// 1 <= nums.length <= 104
// 	2 <= nums[i] <= 1000
//
// Helpful references (internal KB):
// - Integer factorization (number, array, enumeration, sieve, counting)
//   • When to use: Use when needing to find the prime factors of a composite number, especially for relatively small numbers or as a base case for more advanced algorithms.
//   • Idea: This algorithm finds the prime factorization of an integer by iteratively dividing it by its smallest prime factors. It typically checks divisors up to the square root of the number, achieving an O(sqrt(N)) time complexity.
//   • Invariants: The product of all found prime factors multiplied by the current remaining number equals the original input number.; All prime factors found so far are less than or equal to the current divisor being tested.
//   • Tips: Perform a primality test first to avoid unnecessary factorization attempts.; Only check divisors up to the square root of the number.
//   • Pitfalls: Trial division is pseudo-polynomial time, making it inefficient for very large numbers.; Forgetting to handle the case where the remaining number after division is itself a prime greater than its original square root.
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
//   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
//   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
//   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
// - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
//   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
//   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
//   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
//   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int distinctPrimeFactors(vector<int>& nums) {
        const int MAX_N = 1000;
        // Sieve of Eratosthenes to find all primes up to MAX_N
        bool is_prime[MAX_N + 1];
        for (int i = 0; i <= MAX_N; ++i) is_prime[i] = true;
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i <= MAX_N; ++i) {
            if (is_prime[i]) {
                for (int j = i * i; j <= MAX_N; j += i) {
                    is_prime[j] = false;
                }
            }
        }

        // Collect all primes up to MAX_N
        int primes[MAX_N];
        int prime_count = 0;
        for (int i = 2; i <= MAX_N; ++i) {
            if (is_prime[i]) {
                primes[prime_count++] = i;
            }
        }

        // Use a boolean array to track distinct prime factors
        bool has_prime_factor[MAX_N + 1];
        for (int i = 0; i <= MAX_N; ++i) has_prime_factor[i] = false;

        // Factor each number in nums and mark its prime factors
        for (int num : nums) {
            int temp = num;
            for (int i = 0; i < prime_count && primes[i] * primes[i] <= temp; ++i) {
                if (temp % primes[i] == 0) {
                    has_prime_factor[primes[i]] = true;
                    while (temp % primes[i] == 0) {
                        temp /= primes[i];
                    }
                }
            }
            if (temp > 1) {
                has_prime_factor[temp] = true;
            }
        }

        // Count distinct prime factors
        int distinct_count = 0;
        for (int i = 2; i <= MAX_N; ++i) {
            if (has_prime_factor[i]) {
                distinct_count++;
            }
        }

        return distinct_count;          
    }
};
