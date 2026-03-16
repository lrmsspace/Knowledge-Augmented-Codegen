# Source: https://leetcode.com/problems/minimum-moves-to-pick-k-ones/   |   Difficulty: Hard
#
# Problem Description:
# You are given a binary array nums of length n, a positive integer k and a non-negative integer maxChanges.
#
# Alice plays a game, where the goal is for Alice to pick up k ones from nums using the minimum number of moves. When the game starts, Alice picks up any index aliceIndex in the range [0, n - 1] and stands there. If nums[aliceIndex] == 1 , Alice picks up the one and nums[aliceIndex] becomes 0(this does not count as a move). After this, Alice can make any number of moves (including zero) where in each move Alice must perform exactly one of the following actions:
#
#
#  Select any index j != aliceIndex such that nums[j] == 0 and set nums[j] = 1. This action can be performed at most maxChanges times.
#  Select any two adjacent indices x and y (|x - y| == 1) such that nums[x] == 1, nums[y] == 0, then swap their values (set nums[y] = 1 and nums[x] = 0). If y == aliceIndex, Alice picks up the one after this move and nums[y] becomes 0.
#
#
# Return the minimum number of moves required by Alice to pick exactly k ones.
#
# Example:
# Input: nums = [1,1,0,0,0,1,1,0,0,1], k = 3, maxChanges = 1
#
# Output: 3
#
# Explanation: Alice can pick up 3 ones in 3 moves, if Alice performs the following actions in each move when standing at aliceIndex == 1:
#
#
#  At the start of the game Alice picks up the one and nums[1] becomes 0. nums becomes [1,0,0,0,0,1,1,0,0,1].
#  Select j == 2 and perform an action of the first type. nums becomes [1,0,1,0,0,1,1,0,0,1]
#  Select x == 2 and y == 1, and perform an action of the second type. nums becomes [1,1,0,0,0,1,1,0,0,1]. As y == aliceIndex, Alice picks up the one and nums becomes [1,0,0,0,0,1,1,0,0,1].
#  Select x == 0 and y == 1, and perform an action of the second type. nums becomes [0,1,0,0,0,1,1,0,0,1]. As y == aliceIndex, Alice picks up the one and nums becomes [0,0,0,0,0,1,1,0,0,1].
#
#
# Note that it may be possible for Alice to pick up 3 ones using some other sequence of 3 moves.
#
# Constraints:
# 2 <= n <= 105
#  0 <= nums[i] <= 1
#  1 <= k <= 105
#  0 <= maxChanges <= 105
#  maxChanges + sum(nums) >= k
#

class Solution(object):
    def minimumMoves(self, nums, k, maxChanges):
        """
        :type nums: List[int]
        :type k: int
        :type maxChanges: int
        :rtype: int
        """
        ones = [i for i, num in enumerate(nums) if num == 1]
        m = len(ones)
        if m < k:
            return -1

        prefix_sum = [0] * (m + 1)
        for i in range(m):
            prefix_sum[i + 1] = prefix_sum[i] + ones[i]

        def moves_needed(left, right):
            mid = (left + right) // 2
            median_pos = ones[mid]
            left_count = mid - left
            right_count = right - mid

            left_moves = median_pos * left_count - (prefix_sum[mid] - prefix_sum[left])
            right_moves = (prefix_sum[right + 1] - prefix_sum[mid + 1]) - median_pos * right_count

            return left_moves + right_moves

        min_moves = float('inf')
        for i in range(m - k + 1):
            j = i + k - 1
            total_moves = moves_needed(i, j)
            changes_needed = (ones[j] - ones[i] + 1) - k
            if changes_needed <= maxChanges:
                min_moves = min(min_moves, total_moves)

        return min_moves if min_moves != float('inf') else -1