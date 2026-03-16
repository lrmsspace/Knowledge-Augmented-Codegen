# Source: https://leetcode.com/problems/find-the-k-or-of-an-array/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums, and an integer k. Let's introduce K-or operation by extending the standard bitwise OR. In K-or, a bit position in the result is set to 1 if at least k numbers in nums have a 1 in that position.
#
# Return the K-or of nums.
#
# Example:
# Input: nums = [7,12,9,8,9,15], k = 4 
#
# Output: 9 
#
# Explanation: 
#
# Represent numbers in binary:
#
#
# 	
# 		
# 			Number
# 			Bit 3
# 			Bit 2
# 			Bit 1
# 			Bit 0
# 		
# 		
# 			7
# 			0
# 			1
# 			1
# 			1
# 		
# 		
# 			12
# 			1
# 			1
# 			0
# 			0
# 		
# 		
# 			9
# 			1
# 			0
# 			0
# 			1
# 		
# 		
# 			8
# 			1
# 			0
# 			0
# 			0
# 		
# 		
# 			9
# 			1
# 			0
# 			0
# 			1
# 		
# 		
# 			15
# 			1
# 			1
# 			1
# 			1
# 		
# 		
# 			Result = 9
# 			1
# 			0
# 			0
# 			1
# 		
# 	
#
#
# Bit 0 is set in 7, 9, 9, and 15. Bit 3 is set in 12, 9, 8, 9, and 15.
# Only bits 0 and 3 qualify. The result is (1001)2 = 9.
#
# Constraints:
# 1 <= nums.length <= 50
# 	0 <= nums[i] < 231
# 	1 <= k <= nums.length
#
# Helpful references (internal KB):
# - Generating all K-combinations (bitset, enumeration)
#   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
#   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
#   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
#   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
#   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Generating all K-combinations (bitset, recursion, enumeration)
#   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
#   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
#   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
#   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
#   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findKOr(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        bit_count = [0] * 31  # Since nums[i] < 2^31

        for num in nums:
            for i in range(31):
                if num & (1 << i):
                    bit_count[i] += 1

        result = 0
        for i in range(31):
            if bit_count[i] >= k:
                result |= (1 << i)

        return result