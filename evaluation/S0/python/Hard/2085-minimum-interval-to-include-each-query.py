# Source: https://leetcode.com/problems/minimum-interval-to-include-each-query/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D integer array intervals, where intervals[i] = [lefti, righti] describes the ith interval starting at lefti and ending at righti (inclusive). The size of an interval is defined as the number of integers it contains, or more formally righti - lefti + 1.
#
# You are also given an integer array queries. The answer to the jth query is the size of the smallest interval i such that lefti <= queries[j] <= righti. If no such interval exists, the answer is -1.
#
# Return an array containing the answers to the queries.
#
# Example:
# Input: intervals = [[1,4],[2,4],[3,6],[4,4]], queries = [2,3,4,5]
# Output: [3,3,1,4]
# Explanation: The queries are processed as follows:
# - Query = 2: The interval [2,4] is the smallest interval containing 2. The answer is 4 - 2 + 1 = 3.
# - Query = 3: The interval [2,4] is the smallest interval containing 3. The answer is 4 - 2 + 1 = 3.
# - Query = 4: The interval [4,4] is the smallest interval containing 4. The answer is 4 - 4 + 1 = 1.
# - Query = 5: The interval [3,6] is the smallest interval containing 5. The answer is 6 - 3 + 1 = 4.
#
# Constraints:
# 1 <= intervals.length <= 105
# 	1 <= queries.length <= 105
# 	intervals[i].length == 2
# 	1 <= lefti <= righti <= 107
# 	1 <= queries[j] <= 107
#

class Solution(object):
    def minInterval(self, intervals, queries):
        """
        :type intervals: List[List[int]]
        :type queries: List[int]
        :rtype: List[int]
        """
        import heapq

        # Sort intervals by their starting point
        intervals.sort(key=lambda x: x[0])
        # Pair each query with its index and sort by query value
        sorted_queries = sorted((q, i) for i, q in enumerate(queries))
        
        result = [-1] * len(queries)
        min_heap = []
        interval_index = 0
        
        for query, original_index in sorted_queries:
            # Add all intervals that start before or at the query point
            while interval_index < len(intervals) and intervals[interval_index][0] <= query:
                start, end = intervals[interval_index]
                size = end - start + 1
                heapq.heappush(min_heap, (size, end))
                interval_index += 1
            
            # Remove intervals from the heap that end before the query point
            while min_heap and min_heap[0][1] < query:
                heapq.heappop(min_heap)
            
            # The smallest interval that contains the query point
            if min_heap:
                result[original_index] = min_heap[0][0]
        
        return result