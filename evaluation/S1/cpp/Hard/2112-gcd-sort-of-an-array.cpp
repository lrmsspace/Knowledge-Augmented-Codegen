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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool gcdSort(vector<int>& nums) {
        int n = nums.size();
        vector<int> sortedNums(nums);
        sort(sortedNums.begin(), sortedNums.end());

        const int MAX_VAL = 100000;
        vector<int> spf(MAX_VAL + 1, 0); // smallest prime factor
        for (int i = 2; i <= MAX_VAL; ++i) {
            if (spf[i] == 0) {
                spf[i] = i;
                for (long long j = (long long)i * i; j <= MAX_VAL; j += i) {
                    if (spf[j] == 0) {
                        spf[j] = i;
                    }
                }
            }
        }

        vector<int> parent(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }

        function<int(int)> findSet = [&](int v) {
            if (parent[v] != v) {
                parent[v] = findSet(parent[v]);
            }
            return parent[v];
        };

        auto unionSets = [&](int a, int b) {
            a = findSet(a);
            b = findSet(b);
            if (a != b) {
                parent[b] = a;
            }
        };

        unordered_map<int, int> primeToIndex;

        for (int i = 0; i < n; ++i) {
            int num = nums[i];
            unordered_set<int> primes;
            while (num > 1) {
                primes.insert(spf[num]);
                num /= spf[num];
            }
            for (int prime : primes) {
                if (primeToIndex.count(prime)) {
                    unionSets(i, primeToIndex[prime]);
                } else {
                    primeToIndex[prime] = i;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (findSet(i) != findSet(distance(nums.begin(), find(sortedNums.begin(), sortedNums.end(), nums[i])))) {
                return false;
            }
        }

        return true;            
    }
};
