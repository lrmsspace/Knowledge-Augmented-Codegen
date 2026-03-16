# Source: https://leetcode.com/problems/number-of-flowers-in-full-bloom/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed 2D integer array flowers, where flowers[i] = [starti, endi] means the ith flower will be in full bloom from starti to endi (inclusive). You are also given a 0-indexed integer array people of size n, where people[i] is the time that the ith person will arrive to see the flowers.
#
# Return an integer array answer of size n, where answer[i] is the number of flowers that are in full bloom when the ith person arrives.
#
# Example:
# Input: flowers = [[1,6],[3,7],[9,12],[4,13]], people = [2,3,7,11]
# Output: [1,2,2,2]
# Explanation: The figure above shows the times when the flowers are in full bloom and when the people arrive.
# For each person, we return the number of flowers in full bloom during their arrival.
#
# Constraints:
# 1 <= flowers.length <= 5 * 104
# 	flowers[i].length == 2
# 	1 <= starti <= endi <= 109
# 	1 <= people.length <= 5 * 104
# 	1 <= people[i] <= 109
#
# Helpful references (internal KB):
# - Sparse Table (array, sparse-table, enumeration)
#   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
#   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
#   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
#   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
#   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
# - Sqrt Decomposition (array, enumeration, prefix-sum)
#   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
#   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
#   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
#   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
#   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
# - Length of the union of segments (array, interval, sweep-line, counting)
#   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
#   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
#   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
#   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
#   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def fullBloomFlowers(self, flowers, people):
        """
        :type flowers: List[List[int]]
        :type people: List[int]
        :rtype: List[int]
        """
        # Step 1: Create event points for the start and end of each flower's bloom
        events = []
        for start, end in flowers:
            events.append((start, 1))   # Flower starts blooming
            events.append((end + 1, -1)) # Flower stops blooming (end + 1 to handle inclusive range)

        # Step 2: Sort events by time; if times are equal, prioritize start over end
        events.sort(key=lambda x: (x[0], -x[1]))

        # Step 3: Create a list of people with their original indices and sort by arrival time
        people_with_index = sorted([(time, i) for i, time in enumerate(people)], key=lambda x: x[0])

        # Step 4: Traverse the events and count the number of blooming flowers at each person's arrival time
        result = [0] * len(people)
        current_blooming = 0
        event_index = 0

        for arrival_time, original_index in people_with_index:
            # Process all events that occur before or at the arrival time
            while event_index < len(events) and events[event_index][0] <= arrival_time:
                current_blooming += events[event_index][1]
                event_index += 1
            
            result[original_index] = current_blooming

        return result