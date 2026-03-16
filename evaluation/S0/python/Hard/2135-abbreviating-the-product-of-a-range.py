# Source: https://leetcode.com/problems/abbreviating-the-product-of-a-range/   |   Difficulty: Hard
#
# Problem Description:
# You are given two positive integers left and right with left <= right. Calculate the product of all integers in the inclusive range [left, right].
#
# Since the product may be very large, you will abbreviate it following these steps:
#
#
# 	Count all trailing zeros in the product and remove them. Let us denote this count as C.
#
# 	
# 		For example, there are 3 trailing zeros in 1000, and there are 0 trailing zeros in 546.
# 	
# 	
# 	Denote the remaining number of digits in the product as d. If d > 10, then express the product as <pre>...<suf> where <pre> denotes the first 5 digits of the product, and <suf> denotes the last 5 digits of the product after removing all trailing zeros. If d <= 10, we keep it unchanged.
# 	
# 		For example, we express 1234567654321 as 12345...54321, but 1234567 is represented as 1234567.
# 	
# 	
# 	Finally, represent the product as a string "<pre>...<suf>eC".
# 	
# 		For example, 12345678987600000 will be represented as "12345...89876e5".
# 	
# 	
#
#
# Return a string denoting the abbreviated product of all integers in the inclusive range [left, right].
#
# Example:
# Input: left = 1, right = 4
# Output: "24e0"
# Explanation: The product is 1 × 2 × 3 × 4 = 24.
# There are no trailing zeros, so 24 remains the same. The abbreviation will end with "e0".
# Since the number of digits is 2, which is less than 10, we do not have to abbreviate it further.
# Thus, the final representation is "24e0".
#
# Constraints:
# 1 <= left <= right <= 104
#

class Solution(object):
    def abbreviateProduct(self, left, right):
        """
        :type left: int
        :type right: int
        :rtype: str
        """
        mod = 10**10
        trailing_zeros = 0
        product = 1
        
        for num in range(left, right + 1):
            n = num
            while n % 10 == 0:
                trailing_zeros += 1
                n //= 10
            while n % 2 == 0:
                n //= 2
            while n % 5 == 0:
                n //= 5
            product = (product * n) % mod
        
        product_str = str(product)
        if len(product_str) > 10:
            first_five = product_str[:5]
            last_five = product_str[-5:]
            return f"{first_five}...{last_five}e{trailing_zeros}"
        else:
            return f"{product_str}e{trailing_zeros}"