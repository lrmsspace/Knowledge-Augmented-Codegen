# Source: https://leetcode.com/problems/construct-the-rectangle/   |   Difficulty: Easy
#
# Problem Description:
# A web developer needs to know how to design a web page's size. So, given a specific rectangular web page’s area, your job by now is to design a rectangular web page, whose length L and width W satisfy the following requirements:
#
#
# 	The area of the rectangular web page you designed must equal to the given target area.
# 	The width W should not be larger than the length L, which means L >= W.
# 	The difference between length L and width W should be as small as possible.
#
#
# Return an array [L, W] where L and W are the length and width of the web page you designed in sequence.
#
# Example:
# Input: area = 4
# Output: [2,2]
# Explanation: The target area is 4, and all the possible ways to construct it are [1,4], [2,2], [4,1]. 
# But according to requirement 2, [1,4] is illegal; according to requirement 3,  [4,1] is not optimal compared to [2,2]. So the length L is 2, and the width W is 2.
#
# Constraints:
# 1 <= area <= 107
#
# Helpful references (internal KB):
# - Integer factorization (number, array, enumeration, sieve, counting)
#   • When to use: Use when needing to find the prime factors of a composite number, especially for relatively small numbers or as a base case for more advanced algorithms.
#   • Idea: This algorithm finds the prime factorization of an integer by iteratively dividing it by its smallest prime factors. It typically checks divisors up to the square root of the number, achieving an O(sqrt(N)) time complexity.
#   • Invariants: The product of all found prime factors multiplied by the current remaining number equals the original input number.; All prime factors found so far are less than or equal to the current divisor being tested.
#   • Tips: Perform a primality test first to avoid unnecessary factorization attempts.; Only check divisors up to the square root of the number.
#   • Pitfalls: Trial division is pseudo-polynomial time, making it inefficient for very large numbers.; Forgetting to handle the case where the remaining number after division is itself a prime greater than its original square root.
# - Finding the equation of a line for a segment (number, geometry, gcd)
#   • When to use: Use this method when you need to represent a line segment's equation using integer coefficients, especially to avoid floating-point inaccuracies in geometric computations.
#   • Idea: This method derives the general form of a line equation (Ax + By + C = 0) from two points, ensuring integer coefficients if input coordinates are integers. It then normalizes these coefficients using GCD to achieve a unique representation, typically in O(log(max(|A|,|B|,|C|))) time due to GCD.
#   • Invariants: The calculated coefficients A, B, C always satisfy A*Px + B*Py + C = 0 for point P(Px, Py).; After GCD division, the absolute values of A, B, C are coprime (unless all are zero).
#   • Tips: Always compute A, B, C using the given formulas for P(Px, Py) and Q(Qx, Qy).; Use absolute values of A, B, C when calculating their greatest common divisor.
#   • Pitfalls: Forgetting to normalize coefficients leads to non-unique representations for the same line.; Incorrectly handling signs during the final normalization step can result in inconsistent forms.
# - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
#   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
#   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
#   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
#   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
#   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def constructRectangle(self, area):
        """
        :type area: int
        :rtype: List[int]
        """
        import math
        
        # Start from the largest possible width (the square root of the area)
        width = int(math.sqrt(area))
        
        while width > 0:
            if area % width == 0:  # Check if it divides the area evenly
                length = area // width
                return [length, width]  # Return [L, W]
            width -= 1  # Decrease width and check again
        
        return [area, 1]  # Fallback case, should never reach here for valid input 
                