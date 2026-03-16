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

class Solution(object):
    def rearrangeBarcodes(self, barcodes):
        """
        :type barcodes: List[int]
        :rtype: List[int]
        """
        from collections import Counter
        import heapq

        count = Counter(barcodes)
        max_heap = [(-freq, num) for num, freq in count.items()]
        heapq.heapify(max_heap)

        result = []
        prev_freq, prev_num = 0, None

        while max_heap:
            freq, num = heapq.heappop(max_heap)
            result.append(num)

            if prev_freq < 0:
                heapq.heappush(max_heap, (prev_freq, prev_num))

            prev_freq, prev_num = freq + 1, num

        return result