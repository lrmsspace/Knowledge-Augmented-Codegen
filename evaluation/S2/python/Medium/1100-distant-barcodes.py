# Source: https://leetcode.com/problems/distant-barcodes/   |   Difficulty: Medium
#
# Problem Description:
# In a warehouse, there is a row of barcodes, where the ith barcode is barcodes[i].
#
# Rearrange the barcodes so that no two adjacent barcodes are equal. You may return any answer, and it is guaranteed an answer exists.
#
# Example:
# Input: barcodes = [1,1,1,2,2,2]
# Output: [2,1,2,1,2,1]
#
# Constraints:
# 1 <= barcodes.length <= 10000
# 	1 <= barcodes[i] <= 10000
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def rearrangeBarcodes(self, barcodes):
        """
        :type barcodes: List[int]
        :rtype: List[int]
        """

        count = Counter(barcodes)
        max_count = max(count.values())
        max_val = 0
        for val, cnt in count.items():
            if cnt == max_count:
                max_val = val
                break

        result = [0] * len(barcodes)
        idx = 0

        # Place the most frequent element first at even indices
        for i in range(0, len(barcodes), 2):
            if count[max_val] > 0:
                result[i] = max_val
                count[max_val] -= 1
            else:
                break

        # Fill remaining positions with other elements
        for val in count:
            while count[val] > 0:
                if idx % 2 == 1 or result[idx] != 0:
                    idx += 1
                else:
                    result[idx] = val
                    count[val] -= 1    
                    idx += 1
        return result 