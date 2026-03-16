# Source: https://leetcode.com/problems/minimum-number-of-people-to-teach/   |   Difficulty: Medium
#
# Problem Description:
# On a social network consisting of m users and some friendships between users, two users can communicate with each other if they know a common language.
#
# You are given an integer n, an array languages, and an array friendships where:
#
#
# 	There are n languages numbered 1 through n,
# 	languages[i] is the set of languages the i​​​​​​th​​​​ user knows, and
# 	friendships[i] = [u​​​​​​i​​​, v​​​​​​i] denotes a friendship between the users u​​​​​​​​​​​i​​​​​ and vi.
#
#
# You can choose one language and teach it to some users so that all friends can communicate with each other. Return the minimum number of users you need to teach.
# Note that friendships are not transitive, meaning if x is a friend of y and y is a friend of z, this doesn't guarantee that x is a friend of z.
#
# Example:
# Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
# Output: 1
# Explanation: You can either teach user 1 the second language or user 2 the first language.
#
# Constraints:
# 2 <= n <= 500
# 	languages.length == m
# 	1 <= m <= 500
# 	1 <= languages[i].length <= n
# 	1 <= languages[i][j] <= n
# 	1 <= u​​​​​​i < v​​​​​​i <= languages.length
# 	1 <= friendships.length <= 500
# 	All tuples (u​​​​​i, v​​​​​​i) are unique
# 	languages[i] contains only unique values
#

class Solution(object):
    def minimumTeachings(self, n, languages, friendships):
        """
        :type n: int
        :type languages: List[List[int]]
        :type friendships: List[List[int]]
        :rtype: int
        """
        m = len(languages)
        lang_set = [set(languages[i]) for i in range(m)]
        need_teach = set()
        
        for u, v in friendships:
            if lang_set[u-1].intersection(lang_set[v-1]):
                continue
            need_teach.add(u-1)
            need_teach.add(v-1)
        
        if not need_teach:
            return 0
        
        lang_count = [0] * (n + 1)
        
        for person in need_teach:
            for lang in lang_set[person]:
                lang_count[lang] += 1
        
        max_known = max(lang_count)
        
        return len(need_teach) - max_known