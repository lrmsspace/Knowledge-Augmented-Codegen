# Source: https://leetcode.com/problems/video-stitching/   |   Difficulty: Medium
#
# Problem Description:
# You are given a series of video clips from a sporting event that lasted time seconds. These video clips can be overlapping with each other and have varying lengths.
#
# Each video clip is described by an array clips where clips[i] = [starti, endi] indicates that the ith clip started at starti and ended at endi.
#
# We can cut these clips into segments freely.
#
#
# 	For example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].
#
#
# Return the minimum number of clips needed so that we can cut the clips into segments that cover the entire sporting event [0, time]. If the task is impossible, return -1.
#
# Example:
# Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10
# Output: 3
# Explanation: We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
# Then, we can reconstruct the sporting event as follows:
# We cut [1,9] into segments [1,2] + [2,8] + [8,9].
# Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].
#
# Constraints:
# 1 <= clips.length <= 100
# 	0 <= starti <= endi <= 100
# 	1 <= time <= 100
#

class Solution(object):
    def videoStitching(self, clips, time):
        """
        :type clips: List[List[int]]
        :type time: int
        :rtype: int
        """
        dp = [float('inf')] * (time + 1)
        dp[0] = 0

        for t in range(1, time + 1):
            for start, end in clips:
                if start < t <= end:
                    dp[t] = min(dp[t], dp[start] + 1)

        return dp[time] if dp[time] != float('inf') else -1