# Source: https://leetcode.com/problems/count-pairs-with-xor-in-a-range/   |   Difficulty: Hard
#
# Problem Description:
# Given a (0-indexed) integer array nums and two integers low and high, return the number of nice pairs.
#
# A nice pair is a pair (i, j) where 0 <= i < j < nums.length and low <= (nums[i] XOR nums[j]) <= high.
#
# Example:
# Input: nums = [1,4,2,7], low = 2, high = 6
# Output: 6
# Explanation: All nice pairs (i, j) are as follows:
#     - (0, 1): nums[0] XOR nums[1] = 5 
#     - (0, 2): nums[0] XOR nums[2] = 3
#     - (0, 3): nums[0] XOR nums[3] = 6
#     - (1, 2): nums[1] XOR nums[2] = 6
#     - (1, 3): nums[1] XOR nums[3] = 3
#     - (2, 3): nums[2] XOR nums[3] = 5
#
# Constraints:
# 1 <= nums.length <= 2 * 104
# 	1 <= nums[i] <= 2 * 104
# 	1 <= low <= high <= 2 * 104
#

class Solution(object):
    def countPairs(self, nums, low, high):
        """
        :type nums: List[int]
        :type low: int
        :type high: int
        :rtype: int
        """
        def countLessThanK(nums, k):
            trie = {}
            count = 0
            for num in nums:
                node = trie
                xor_node = trie
                for i in range(14, -1, -1):
                    bit = (num >> i) & 1
                    k_bit = (k >> i) & 1

                    if k_bit == 1:
                        if bit ^ 0 in xor_node:
                            count += xor_node[bit ^ 0].get('count', 0)
                        if bit ^ 1 in xor_node:
                            xor_node = xor_node[bit ^ 1]
                        else:
                            break
                    else:
                        if bit ^ 0 in xor_node:
                            xor_node = xor_node[bit ^ 0]
                        else:
                            break

                for i in range(14, -1, -1):
                    bit = (num >> i) & 1
                    if bit not in node:
                        node[bit] = {}
                    node = node[bit]
                    node['count'] = node.get('count', 0) + 1

            return count

        return countLessThanK(nums, high + 1) - countLessThanK(nums, low)