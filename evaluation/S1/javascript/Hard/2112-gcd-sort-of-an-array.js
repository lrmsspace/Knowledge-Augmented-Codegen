// Source: https://leetcode.com/problems/gcd-sort-of-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums, and you can perform the following operation any number of times on nums:
//
//
// 	Swap the positions of two elements nums[i] and nums[j] if gcd(nums[i], nums[j]) > 1 where gcd(nums[i], nums[j]) is the greatest common divisor of nums[i] and nums[j].
//
//
// Return true if it is possible to sort nums in non-decreasing order using the above swap method, or false otherwise.
//
// Example:
// Input: nums = [7,21,3]
// Output: true
// Explanation: We can sort [7,21,3] by performing the following operations:
// - Swap 7 and 21 because gcd(7,21) = 7. nums = [21,7,3]
// - Swap 21 and 3 because gcd(21,3) = 3. nums = [3,7,21]
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	2 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Linear Sieve (array, sieve)
//   • When to use: Use when you need to find the smallest prime factor or full prime factorization for all numbers up to a given limit N in linear time. It's particularly useful for tasks requiring precomputed factorizations.
//   • Idea: The Linear Sieve computes the smallest prime factor for every number up to N, ensuring each composite number is marked exactly once by its smallest prime factor. It achieves this in O(N) time complexity.
//   • Invariants: Every number `i` from 2 to N has its `lp[i]` correctly set to its smallest prime factor.; The `primes` array contains all prime numbers less than or equal to the current iteration `i`.
//   • Tips: Stores the smallest prime factor (lp) for each number.; Efficiently generates all prime numbers up to N.
//   • Pitfalls: Higher memory usage compared to the classic Sieve of Eratosthenes due to storing lp array.; Can be slower in practice than optimized Sieve of Eratosthenes for merely generating primes.
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to efficiently manage a collection of disjoint sets, supporting operations to merge sets and determine if two elements belong to the same set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that maintains a collection of disjoint sets and supports two primary operations: union (merging two sets) and find (determining the representative of an element's set). With path compression and union by rank/size, operations achieve nearly O(1) amortized time complexity.
//   • Invariants: For any element `v`, `parent[v]` is either `v` itself (if `v` is a root) or an ancestor of `v`.; All elements belonging to the same set share a common root representative.
//   • Tips: Apply path compression during `find_set` to optimize future queries.; Utilize union by rank or size to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size results in poor performance.; Failing to correctly identify the root of a set in `find_set`.
// - Primitive Root (number, mod-exp, sieve, enumeration)
//   • When to use: Use when needing to find a generator for the multiplicative group of integers modulo n, or to check if a number is a primitive root. This is often required in number theory problems involving modular arithmetic and cyclic groups.
//   • Idea: This algorithm finds a primitive root modulo n by checking candidate numbers and verifying their order using Euler's totient function and its prime factors. The optimized approach significantly reduces checks from O(phi(n)) to O(k * log(n)) for each candidate, where k is the number of distinct prime factors of phi(n).
//   • Invariants: The current candidate g is coprime to n.; The order of g modulo n is being checked against divisors of phi(n).
//   • Tips: First, determine if a primitive root exists for the given n.; Calculate Euler's totient function phi(n) for the modulus n.
//   • Pitfalls: Forgetting to check the existence condition for primitive roots.; Incorrectly calculating Euler's totient function phi(n).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var gcdSort = function(nums) {
    const n = nums.length;
    const maxNum = Math.max(...nums);
    
    // Step 1: Linear Sieve to find smallest prime factors
    const lp = new Array(maxNum + 1).fill(0);
    const primes = [];
    for (let i = 2; i <= maxNum; i++) {
        if (lp[i] === 0) {
            lp[i] = i;
            primes.push(i);
        }
        for (const p of primes) {
            if (p > lp[i] || i * p > maxNum) break;
            lp[i * p] = p;
        }
    }
    
    // Step 2: Disjoint Set Union (DSU) for union-find operations
    const parent = new Array(maxNum + 1).fill(0).map((_, idx) => idx);
    
    function findSet(v) {
        if (v === parent[v]) return v;
        return parent[v] = findSet(parent[v]);
    }
    
    function unionSet(a, b) {
        a = findSet(a);
        b = findSet(b);
        if (a !== b) parent[a] = b;
    }
    
    // Step 3: Union indices based on GCD > 1
    for (const num of nums) {
        let x = num;
        while (x > 1) {
            const primeFactor = lp[x];
            unionSet(num, primeFactor);
            while (x % primeFactor === 0) {
                x /= primeFactor;
            }
        }
    }
    
    // Step 4: Check if nums can be sorted by checking their DSU representatives
    const sortedNums = [...nums].sort((a, b) => a - b);
    for (let i = 0; i < n; i++) {
        if (findSet(nums[i]) !== findSet(sortedNums[i])) {
            return false;
        }
    }
    
    return true;
};
