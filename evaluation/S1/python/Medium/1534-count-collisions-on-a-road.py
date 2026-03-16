# Source: https://leetcode.com/problems/count-collisions-on-a-road/   |   Difficulty: Medium
#
# Problem Description:
# There are n cars on an infinitely long road. The cars are numbered from 0 to n - 1 from left to right and each car is present at a unique point.
#
# You are given a 0-indexed string directions of length n. directions[i] can be either 'L', 'R', or 'S' denoting whether the ith car is moving towards the left, towards the right, or staying at its current point respectively. Each moving car has the same speed.
#
# The number of collisions can be calculated as follows:
#
#
# 	When two cars moving in opposite directions collide with each other, the number of collisions increases by 2.
# 	When a moving car collides with a stationary car, the number of collisions increases by 1.
#
#
# After a collision, the cars involved can no longer move and will stay at the point where they collided. Other than that, cars cannot change their state or direction of motion.
#
# Return the total number of collisions that will happen on the road.
#
# Example:
# Input: directions = "RLRSLL"
# Output: 5
# Explanation:
# The collisions that will happen on the road are:
# - Cars 0 and 1 will collide with each other. Since they are moving in opposite directions, the number of collisions becomes 0 + 2 = 2.
# - Cars 2 and 3 will collide with each other. Since car 3 is stationary, the number of collisions becomes 2 + 1 = 3.
# - Cars 3 and 4 will collide with each other. Since car 3 is stationary, the number of collisions becomes 3 + 1 = 4.
# - Cars 4 and 5 will collide with each other. After car 4 collides with car 3, it will stay at the point of collision and get hit by car 5. The number of collisions becomes 4 + 1 = 5.
# Thus, the total number of collisions that will happen on the road is 5.
#
# Constraints:
# 1 <= directions.length <= 105
# 	directions[i] is either 'L', 'R', or 'S'.
#
# Helpful references (internal KB):
# - Minimum stack / Minimum queue (stack, simulation)
#   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
#   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
#   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
#   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
#   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
# - Suffix Automaton (string, simulation)
#   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
#   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
#   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
#   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
#   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
# - Circle-Circle Intersection (geometry, number, simulation, enumeration)
#   • When to use: Use this algorithm to find the common points where two circles intersect on a 2D plane, handling cases from no intersection to infinite points.
#   • Idea: This algorithm determines the intersection points of two circles by algebraically transforming their equations into a system involving one circle and one line. It typically achieves O(1) time complexity for finding the intersection points.
#   • Invariants: The relative positions and radii of the circles remain unchanged after coordinate translation.; The derived linear equation represents the radical axis of the two circles.
#   • Tips: Translate one circle to the origin to simplify the equations.; Subtract the two circle equations to derive a linear equation (the radical axis).
#   • Pitfalls: Numerical instability due to floating-point arithmetic, especially for tangent cases.; Forgetting to translate the resulting intersection points back to the original coordinate system.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countCollisions(self, directions):
        """
        :type directions: str
        :rtype: int
        """
        n = len(directions)
        directions = list(directions)
        collisions = 0

        changed = True
        while changed:
            changed = False
            i = 0
            while i < n - 1:
                if directions[i] == 'R' and directions[i + 1] == 'L':
                    directions[i] = 'S'
                    directions[i + 1] = 'S'
                    collisions += 2
                    changed = True
                    i += 2
                elif directions[i] == 'R' and directions[i + 1] == 'S':
                    directions[i] = 'S'
                    collisions += 1
                    changed = True
                    i += 1
                elif directions[i] == 'S' and directions[i + 1] == 'L':
                    directions[i + 1] = 'S'
                    collisions += 1
                    changed = True
                    i += 1
                else:
                    i += 1

        return collisions