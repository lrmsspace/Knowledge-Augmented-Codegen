# Source: https://leetcode.com/problems/get-watched-videos-by-your-friends/   |   Difficulty: Medium
#
# Problem Description:
# There are n people, each person has a unique id between 0 and n-1. Given the arrays watchedVideos and friends, where watchedVideos[i] and friends[i] contain the list of watched videos and the list of friends respectively for the person with id = i.
#
# Level 1 of videos are all watched videos by your friends, level 2 of videos are all watched videos by the friends of your friends and so on. In general, the level k of videos are all watched videos by people with the shortest path exactly equal to k with you. Given your id and the level of videos, return the list of videos ordered by their frequencies (increasing). For videos with the same frequency order them alphabetically from least to greatest.
#
# Example:
# Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
# Output: ["B","C"] 
# Explanation: 
# You have id = 0 (green color in the figure) and your friends are (yellow color in the figure):
# Person with id = 1 -> watchedVideos = ["C"] 
# Person with id = 2 -> watchedVideos = ["B","C"] 
# The frequencies of watchedVideos by your friends are: 
# B -> 1 
# C -> 2
#
# Constraints:
# n == watchedVideos.length == friends.length
# 	2 <= n <= 100
# 	1 <= watchedVideos[i].length <= 100
# 	1 <= watchedVideos[i][j].length <= 8
# 	0 <= friends[i].length < n
# 	0 <= friends[i][j] < n
# 	0 <= id < n
# 	1 <= level < n
# 	if friends[i] contains j, then friends[j] contains i
#

class Solution(object):
    def watchedVideosByFriends(self, watchedVideos, friends, id, level):
        """
        :type watchedVideos: List[List[str]]
        :type friends: List[List[int]]
        :type id: int
        :type level: int
        :rtype: List[str]
        """
        from collections import deque, defaultdict

        n = len(watchedVideos)
        visited = [False] * n
        queue = deque()
        queue.append((id, 0))
        visited[id] = True
        freq = defaultdict(int)

        while queue:
            person, curr_level = queue.popleft()

            if curr_level == level:
                for video in watchedVideos[person]:
                    freq[video] += 1
            elif curr_level < level:
                for friend in friends[person]:
                    if not visited[friend]:
                        visited[friend] = True
                        queue.append((friend, curr_level + 1))

        sorted_videos = sorted(freq.items(), key=lambda x: (x[1], x[0]))
        return [video for video, count in sorted_videos]