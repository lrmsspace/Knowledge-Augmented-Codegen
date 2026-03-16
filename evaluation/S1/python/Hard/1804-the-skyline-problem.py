# Source: https://leetcode.com/problems/the-skyline-problem/   |   Difficulty: Hard
#
# Problem Description:
# A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return the skyline formed by these buildings collectively.
#
# The geometric information of each building is given in the array buildings where buildings[i] = [lefti, righti, heighti]:
#
#
# 	lefti is the x coordinate of the left edge of the ith building.
# 	righti is the x coordinate of the right edge of the ith building.
# 	heighti is the height of the ith building.
#
#
# You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.
#
# The skyline should be represented as a list of "key points" sorted by their x-coordinate in the form [[x1,y1],[x2,y2],...]. Each key point is the left endpoint of some horizontal segment in the skyline except the last point in the list, which always has a y-coordinate 0 and is used to mark the skyline's termination where the rightmost building ends. Any ground between the leftmost and rightmost buildings should be part of the skyline's contour.
#
# Note: There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...,[2 3],[4 5],[12 7],...]
#
# Example:
# Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
# Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
# Explanation:
# Figure A shows the buildings of the input.
# Figure B shows the skyline formed by those buildings. The red points in figure B represent the key points in the output list.
#
# Constraints:
# 1 <= buildings.length <= 104
# 	0 <= lefti < righti <= 231 - 1
# 	1 <= heighti <= 231 - 1
# 	buildings is sorted by lefti in non-decreasing order.
#
# Helpful references (internal KB):
# - Point location in O(logn) (geometry, sweep-line, enumeration)
#   • When to use: Use when needing to efficiently determine which region or geometric primitive a given query point belongs to within a static set of geometric objects, such as polygons or diagrams.
#   • Idea: This algorithm efficiently locates query points within a geometric structure by processing events along a sweep line. It typically achieves O(log N) query time after an initial preprocessing phase.
#   • Invariants: All events with x-coordinate less than the current sweep line position have been processed.; The active set of edges contains all segments currently intersected by the sweep line, ordered by their y-intercept.
#   • Tips: Sort all event points by x-coordinate, then by event type for consistent processing.; Maintain an ordered data structure (e.g., balanced BST) for active edges intersected by the sweep line.
#   • Pitfalls: Incorrectly handling edge cases like vertical edges or points exactly on edges.; Maintaining the active edge set inefficiently, leading to higher than O(log N) complexity.
# - Priority Queues (array, heap, heap-select)
#   • When to use: Use when you need to efficiently retrieve the highest or lowest priority item from a dynamic collection. It's ideal for scenarios requiring frequent insertions and extractions of extreme values without full sorting.
#   • Idea: A Priority Queue is an abstract data type that provides efficient retrieval of the maximum or minimum element. It is typically implemented using a binary heap, which stores elements in an array representing a complete binary tree, maintaining the heap-ordered property for O(log N) insertion and deletion.
#   • Invariants: For a max-heap, every parent node's key is greater than or equal to its children's keys.; The heap structure is always a complete binary tree, represented contiguously in an array.
#   • Tips: Represent the complete binary tree using an array, often 1-indexed for simpler parent/child calculations.; Use 'swim' (bottom-up reheapify) after insertion to restore heap order.
#   • Pitfalls: Forgetting to handle 0-indexed vs 1-indexed array representations correctly (parent/child formulas differ).; Violating the heap-ordered property during updates or custom operations.
# - Scheduling jobs on one machine (array, number, greedy, merge-sort)
#   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
#   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
#   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
#   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
#   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getSkyline(self, buildings):
        """
        :type buildings: List[List[int]]
        :rtype: List[List[int]]
        """


        # Create a list of all critical points (start and end of buildings)
        events = []
        for left, right, height in buildings:
            events.append((left, -height))  # Building start
            events.append((right, height))  # Building end

        # Sort events by x-coordinate, and then by height
        events.sort(key=lambda x: (x[0], x[1]))

        result = []
        heap = [0]  # Max-heap (using negative heights)
        prev_max_height = 0
        active_heights = {0: 1}  # Dictionary to count active heights

        for x, h in events:
            if h < 0:  # Building start
                heapq.heappush(heap, h)
                active_heights[-h] = active_heights.get(-h, 0) + 1
            else:  # Building end
                active_heights[h] -= 1
                if active_heights[h] == 0:
                    del active_heights[h]

            # Remove inactive heights from the heap top
            while heap and -heap[0] not in active_heights:
                heapq.heappop(heap)

            current_max_height = -heap[0]
            if current_max_height != prev_max_height:
                result.append([x, current_max_height])
                prev_max_height = current_max_height

        return result       