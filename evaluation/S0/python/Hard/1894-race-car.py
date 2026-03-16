# Source: https://leetcode.com/problems/race-car/   |   Difficulty: Hard
#
# Problem Description:
# Your car starts at position 0 and speed +1 on an infinite number line. Your car can go into negative positions. Your car drives automatically according to a sequence of instructions 'A' (accelerate) and 'R' (reverse):
#
#
# 	When you get an instruction 'A', your car does the following:
#
# 	
# 		position += speed
# 		speed *= 2
# 	
# 	
# 	When you get an instruction 'R', your car does the following:
# 	
# 		If your speed is positive then speed = -1
# 		otherwise speed = 1
# 	
# 	Your position stays the same.
#
#
# For example, after commands "AAR", your car goes to positions 0 --> 1 --> 3 --> 3, and your speed goes to 1 --> 2 --> 4 --> -1.
#
# Given a target position target, return the length of the shortest sequence of instructions to get there.
#
# Example:
# Input: target = 3
# Output: 2
# Explanation: 
# The shortest instruction sequence is "AA".
# Your position goes from 0 --> 1 --> 3.
#
# Constraints:
# 1 <= target <= 104
#

class Solution(object):
    def racecar(self, target):
        """
        :type target: int
        :rtype: int
        """
        from collections import deque

        queue = deque([(0, 1)])  # (position, speed)
        visited = set((0, 1))
        steps = 0

        while queue:
            for _ in range(len(queue)):
                position, speed = queue.popleft()

                if position == target:
                    return steps

                # Accelerate
                new_position = position + speed
                new_speed = speed * 2
                if (new_position, new_speed) not in visited and 0 < new_position < 2 * target:
                    visited.add((new_position, new_speed))
                    queue.append((new_position, new_speed))

                # Reverse
                new_speed = -1 if speed > 0 else 1
                if (position, new_speed) not in visited:
                    visited.add((position, new_speed))
                    queue.append((position, new_speed))

            steps += 1

        return -1