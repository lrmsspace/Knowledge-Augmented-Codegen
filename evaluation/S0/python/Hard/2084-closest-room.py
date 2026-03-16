# Source: https://leetcode.com/problems/closest-room/   |   Difficulty: Hard
#
# Problem Description:
# There is a hotel with n rooms. The rooms are represented by a 2D integer array rooms where rooms[i] = [roomIdi, sizei] denotes that there is a room with room number roomIdi and size equal to sizei. Each roomIdi is guaranteed to be unique.
#
# You are also given k queries in a 2D array queries where queries[j] = [preferredj, minSizej]. The answer to the jth query is the room number id of a room such that:
#
#
# 	The room has a size of at least minSizej, and
# 	abs(id - preferredj) is minimized, where abs(x) is the absolute value of x.
#
#
# If there is a tie in the absolute difference, then use the room with the smallest such id. If there is no such room, the answer is -1.
#
# Return an array answer of length k where answer[j] contains the answer to the jth query.
#
# Example:
# Input: rooms = [[2,2],[1,2],[3,2]], queries = [[3,1],[3,3],[5,2]]
# Output: [3,-1,3]
# Explanation: The answers to the queries are as follows:
# Query = [3,1]: Room number 3 is the closest as abs(3 - 3) = 0, and its size of 2 is at least 1. The answer is 3.
# Query = [3,3]: There are no rooms with a size of at least 3, so the answer is -1.
# Query = [5,2]: Room number 3 is the closest as abs(3 - 5) = 2, and its size of 2 is at least 2. The answer is 3.
#
# Constraints:
# n == rooms.length
# 	1 <= n <= 105
# 	k == queries.length
# 	1 <= k <= 104
# 	1 <= roomIdi, preferredj <= 107
# 	1 <= sizei, minSizej <= 107
#

class Solution(object):
    def closestRoom(self, rooms, queries):
        """
        :type rooms: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        import bisect

        rooms.sort(key=lambda x: -x[1])
        sorted_ids = []
        res = [-1] * len(queries)
        queries = sorted([(pref, min_size, i) for i, (pref, min_size) in enumerate(queries)], key=lambda x: -x[1])

        idx = 0
        for pref, min_size, q_idx in queries:
            while idx < len(rooms) and rooms[idx][1] >= min_size:
                bisect.insort(sorted_ids, rooms[idx][0])
                idx += 1

            if not sorted_ids:
                continue

            pos = bisect.bisect_left(sorted_ids, pref)
            candidates = []
            if pos < len(sorted_ids):
                candidates.append(sorted_ids[pos])
            if pos > 0:
                candidates.append(sorted_ids[pos - 1])

            closest_id = min(candidates, key=lambda x: (abs(x - pref), x))
            res[q_idx] = closest_id

        return res