# Source: https://leetcode.com/problems/most-popular-video-creator/   |   Difficulty: Medium
#
# Problem Description:
# You are given two string arrays creators and ids, and an integer array views, all of length n. The ith video on a platform was created by creators[i], has an id of ids[i], and has views[i] views.
#
# The popularity of a creator is the sum of the number of views on all of the creator's videos. Find the creator with the highest popularity and the id of their most viewed video.
#
#
# 	If multiple creators have the highest popularity, find all of them.
# 	If multiple videos have the highest view count for a creator, find the lexicographically smallest id.
#
#
# Note: It is possible for different videos to have the same id, meaning that ids do not uniquely identify a video. For example, two videos with the same ID are considered as distinct videos with their own viewcount.
#
# Return a 2D array of strings answer where answer[i] = [creatorsi, idi] means that creatorsi has the highest popularity and idi is the id of their most popular video. The answer can be returned in any order.
#
# Example:
# Input: creators = ["alice","bob","alice","chris"], ids = ["one","two","three","four"], views = [5,10,5,4]
#
# Output: [["alice","one"],["bob","two"]]
#
# Explanation:
#
# The popularity of alice is 5 + 5 = 10.
# The popularity of bob is 10.
# The popularity of chris is 4.
# alice and bob are the most popular creators.
# For bob, the video with the highest view count is "two".
# For alice, the videos with the highest view count are "one" and "three". Since "one" is lexicographically smaller than "three", it is included in the answer.
#
# Constraints:
# n == creators.length == ids.length == views.length
# 	1 <= n <= 105
# 	1 <= creators[i].length, ids[i].length <= 5
# 	creators[i] and ids[i] consist only of lowercase English letters.
# 	0 <= views[i] <= 105
#

class Solution(object):
    def mostPopularCreator(self, creators, ids, views):
        """
        :type creators: List[str]
        :type ids: List[str]
        :type views: List[int]
        :rtype: List[List[str]]
        """
        from collections import defaultdict

        creator_popularity = defaultdict(int)
        creator_top_video = {}

        for creator, vid_id, view_count in zip(creators, ids, views):
            creator_popularity[creator] += view_count

            if (creator not in creator_top_video or
                view_count > creator_top_video[creator][1] or
                (view_count == creator_top_video[creator][1] and vid_id < creator_top_video[creator][0])):
                creator_top_video[creator] = (vid_id, view_count)

        max_popularity = max(creator_popularity.values())
        result = []

        for creator, popularity in creator_popularity.items():
            if popularity == max_popularity:
                result.append([creator, creator_top_video[creator][0]])

        return result