# Source: https://leetcode.com/problems/car-fleet-ii/   |   Difficulty: Hard
#
# Problem Description:
# There are n cars traveling at different speeds in the same direction along a one-lane road. You are given an array cars of length n, where cars[i] = [positioni, speedi] represents:
#
#
# 	positioni is the distance between the ith car and the beginning of the road in meters. It is guaranteed that positioni < positioni+1.
# 	speedi is the initial speed of the ith car in meters per second.
#
#
# For simplicity, cars can be considered as points moving along the number line. Two cars collide when they occupy the same position. Once a car collides with another car, they unite and form a single car fleet. The cars in the formed fleet will have the same position and the same speed, which is the initial speed of the slowest car in the fleet.
#
# Return an array answer, where answer[i] is the time, in seconds, at which the ith car collides with the next car, or -1 if the car does not collide with the next car. Answers within 10-5 of the actual answers are accepted.
#
# Example:
# Input: cars = [[1,2],[2,1],[4,3],[7,2]]
# Output: [1.00000,-1.00000,3.00000,-1.00000]
# Explanation: After exactly one second, the first car will collide with the second car, and form a car fleet with speed 1 m/s. After exactly 3 seconds, the third car will collide with the fourth car, and form a car fleet with speed 2 m/s.
#
# Constraints:
# 1 <= cars.length <= 105
# 	1 <= positioni, speedi <= 106
# 	positioni < positioni+1
#
# Helpful references (internal KB):
# - Minimum stack / Minimum queue (stack, simulation)
#   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
#   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
#   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
#   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
#   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
# - Convex Hull construction (geometry, array, stack, sweep-line, monotonic-stack)
#   • When to use: When you need to find the smallest convex polygon enclosing a given set of points. It's used for problems requiring the outermost boundary of a point set.
#   • Idea: Convex Hull construction algorithms, like Graham Scan or Monotone Chain, find the smallest convex polygon that encloses a given set of points. These algorithms typically have a time complexity of O(N log N) due to sorting.
#   • Invariants: The points currently on the stack form a convex chain in the desired direction.; For any three consecutive points A, B, C on the stack, the turn from AB to BC maintains convexity.
#   • Tips: Use an orientation test (cross product) to determine if points make a clockwise or counter-clockwise turn.; Handle collinear points carefully, especially if they need to be included in the hull.
#   • Pitfalls: Incorrectly handling collinear points can lead to an incomplete or incorrect hull.; Floating-point precision issues can affect orientation tests, leading to wrong turns.
# - Scheduling jobs on one machine (array, number, greedy, merge-sort)
#   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
#   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
#   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
#   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
#   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getCollisionTimes(self, cars):
        """
        :type cars: List[List[int]]
        :rtype: List[float]
        """
        n = len(cars)
        ans = [-1.0] * n
        stack = []  # Stack to keep track of car indices that haven't collided yet

        for i in range(n - 1, -1, -1):
            position, speed = cars[i]
            while stack:
                j = stack[-1]  # Index of the next car in the stack
                next_position, next_speed = cars[j]

                if speed <= next_speed:
                    # Current car will never catch up to the next car
                    stack.pop()
                else:
                    # Calculate collision time with the next car
                    collision_time = (next_position - position) / (speed - next_speed)
                    if ans[j] == -1 or collision_time < ans[j]:
                        ans[i] = collision_time
                        break
                    else:
                        stack.pop()

            stack.append(i)

        return ans