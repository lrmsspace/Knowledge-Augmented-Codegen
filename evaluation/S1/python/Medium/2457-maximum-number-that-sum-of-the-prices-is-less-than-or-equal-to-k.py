# Source: https://leetcode.com/problems/maximum-number-that-sum-of-the-prices-is-less-than-or-equal-to-k/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer k and an integer x. The price of a number num is calculated by the count of set bits at positions x, 2x, 3x, etc., in its binary representation, starting from the least significant bit. The following table contains examples of how price is calculated.
#
#
# 	
# 		
# 			x
# 			num
# 			Binary Representation
# 			Price
# 		
# 		
# 			1
# 			13
# 			000001101
# 			3
# 		
# 		
# 			2
# 			13
# 			000001101
# 			1
# 		
# 		
# 			2
# 			233
# 			011101001
# 			3
# 		
# 		
# 			3
# 			13
# 			000001101
# 			1
# 		
# 		
# 			3
# 			362
# 			101101010
# 			2
# 		
# 	
#
#
# The accumulated price of num is the total price of numbers from 1 to num. num is considered cheap if its accumulated price is less than or equal to k.
#
# Return the greatest cheap number.
#
# Example:
# Input: k = 9, x = 1
#
# Output: 6
#
# Explanation:
#
# As shown in the table below, 6 is the greatest cheap number.
#
#
# 	
# 		
# 			x
# 			num
# 			Binary Representation
# 			Price
# 			Accumulated Price
# 		
# 		
# 			1
# 			1
# 			001
# 			1
# 			1
# 		
# 		
# 			1
# 			2
# 			010
# 			1
# 			2
# 		
# 		
# 			1
# 			3
# 			011
# 			2
# 			4
# 		
# 		
# 			1
# 			4
# 			100
# 			1
# 			5
# 		
# 		
# 			1
# 			5
# 			101
# 			2
# 			7
# 		
# 		
# 			1
# 			6
# 			110
# 			2
# 			9
# 		
# 		
# 			1
# 			7
# 			111
# 			3
# 			12
#
# Constraints:
# 1 <= k <= 1015
# 	1 <= x <= 8
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# -  
# Kth order statistic in O(N) (array, quickselect, randomized)
#   • When to use: When you need to efficiently find the Kth smallest or largest element in an unsorted array. It is ideal when a full sort is unnecessary and average linear time performance is acceptable.
#   • Idea: Quickselect is a selection algorithm that finds the Kth smallest element in an unsorted list by repeatedly partitioning the array around a pivot. It achieves an average time complexity of O(N) and a worst-case complexity of O(N^2).
#   • Invariants: All elements in the left partition are less than or equal to the pivot element.; All elements in the right partition are greater than or equal to the pivot element.
#   • Tips: Shuffle the input array or choose a random pivot to achieve average O(N) performance.; The algorithm modifies the input array in place, so a copy might be needed if the original must be preserved.
#   • Pitfalls: A consistently bad pivot choice (e.g., always smallest/largest) leads to O(N^2) worst-case time.; Not suitable if the relative order of other elements needs to be preserved (it's not a stable algorithm).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findMaximumNumber(self, k, x):
        """
        :type k: int
        :type x: int
        :rtype: int
        """
        def price(num, x):
            cnt = 0
            pos = 1
            while num > 0:
                if pos % x == 0 and (num & 1) == 1:
                    cnt += 1
                num >>= 1
                pos += 1
            return cnt

        def accumulated_price(num, x):
            total = 0
            for i in range(1, num + 1):
                total += price(i, x)
            return total

        left, right = 1, 10**15
        answer = 0

        while left <= right:
            mid = (left + right) // 2
            if accumulated_price(mid, x) <= k:
                answer = mid
                left = mid + 1
            else:
                right = mid - 1

        return answer