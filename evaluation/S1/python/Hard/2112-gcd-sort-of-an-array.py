# Source: https://leetcode.com/problems/gcd-sort-of-an-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums, and you can perform the following operation any number of times on nums:
#
#
# 	Swap the positions of two elements nums[i] and nums[j] if gcd(nums[i], nums[j]) > 1 where gcd(nums[i], nums[j]) is the greatest common divisor of nums[i] and nums[j].
#
#
# Return true if it is possible to sort nums in non-decreasing order using the above swap method, or false otherwise.
#
# Example:
# Input: nums = [7,21,3]
# Output: true
# Explanation: We can sort [7,21,3] by performing the following operations:
# - Swap 7 and 21 because gcd(7,21) = 7. nums = [21,7,3]
# - Swap 21 and 3 because gcd(21,3) = 3. nums = [3,7,21]
#
# Constraints:
# 1 <= nums.length <= 3 * 104
# 	2 <= nums[i] <= 105
#
# Helpful references (internal KB):
# - Linear Sieve (array, sieve)
#   • When to use: Use when you need to find the smallest prime factor or full prime factorization for all numbers up to a given limit N in linear time. It's particularly useful for tasks requiring precomputed factorizations.
#   • Idea: The Linear Sieve computes the smallest prime factor for every number up to N, ensuring each composite number is marked exactly once by its smallest prime factor. It achieves this in O(N) time complexity.
#   • Invariants: Every number `i` from 2 to N has its `lp[i]` correctly set to its smallest prime factor.; The `primes` array contains all prime numbers less than or equal to the current iteration `i`.
#   • Tips: Stores the smallest prime factor (lp) for each number.; Efficiently generates all prime numbers up to N.
#   • Pitfalls: Higher memory usage compared to the classic Sieve of Eratosthenes due to storing lp array.; Can be slower in practice than optimized Sieve of Eratosthenes for merely generating primes.
# - Disjoint Set Union (ds, tree, array, union-find)
#   • When to use: Use when you need to efficiently manage a collection of disjoint sets, supporting operations to merge sets and determine if two elements belong to the same set.
#   • Idea: Disjoint Set Union (DSU) is a data structure that maintains a collection of disjoint sets and supports two primary operations: union (merging two sets) and find (determining the representative of an element's set). With path compression and union by rank/size, operations achieve nearly O(1) amortized time complexity.
#   • Invariants: For any element `v`, `parent[v]` is either `v` itself (if `v` is a root) or an ancestor of `v`.; All elements belonging to the same set share a common root representative.
#   • Tips: Apply path compression during `find_set` to optimize future queries.; Utilize union by rank or size to maintain balanced trees.
#   • Pitfalls: Omitting path compression or union by rank/size results in poor performance.; Failing to correctly identify the root of a set in `find_set`.
# - Primitive Root (number, mod-exp, sieve, enumeration)
#   • When to use: Use when needing to find a generator for the multiplicative group of integers modulo n, or to check if a number is a primitive root. This is often required in number theory problems involving modular arithmetic and cyclic groups.
#   • Idea: This algorithm finds a primitive root modulo n by checking candidate numbers and verifying their order using Euler's totient function and its prime factors. The optimized approach significantly reduces checks from O(phi(n)) to O(k * log(n)) for each candidate, where k is the number of distinct prime factors of phi(n).
#   • Invariants: The current candidate g is coprime to n.; The order of g modulo n is being checked against divisors of phi(n).
#   • Tips: First, determine if a primitive root exists for the given n.; Calculate Euler's totient function phi(n) for the modulus n.
#   • Pitfalls: Forgetting to check the existence condition for primitive roots.; Incorrectly calculating Euler's totient function phi(n).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def gcdSort(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        # Step 1: Find the maximum number in nums to limit our sieve
        max_num = max(nums)
        
        # Step 2: Create a linear sieve to find the smallest prime factor for each number up to max_num
        lp = [0] * (max_num + 1)  # lp[i] will store the smallest prime factor of i
        primes = []
        
        for i in range(2, max_num + 1):
            if lp[i] == 0:
                lp[i] = i
                primes.append(i)
            for p in primes:
                if p > lp[i] or i * p > max_num:
                    break
                lp[i * p] = p
        
        # Step 3: Use Disjoint Set Union (DSU) to group numbers by their prime factors
        parent = list(range(max_num + 1))
        
        def find_set(v):
            if parent[v] != v:
                parent[v] = find_set(parent[v])  # Path compression
            return parent[v]
        
        def union_set(a, b):
            a_root = find_set(a)
            b_root = find_set(b)
            if a_root != b_root:
                parent[b_root] = a_root
        
        # Step 4: Union numbers that share a common prime factor
        for num in nums:
            x = num
            while x > 1:
                prime_factor = lp[x]
                union_set(num, prime_factor)
                while x % prime_factor == 0:
                    x //= prime_factor
        
        # Step 5: Check if the sorted version of nums can be achieved by swapping within the same DSU sets
        sorted_nums = sorted(nums)
        
        for original, sorted_val in zip(nums, sorted_nums):
            if find_set(original) != find_set(sorted_val):
                return False
        
        return True