# Source: https://leetcode.com/problems/expressive-words/   |   Difficulty: Medium
#
# Problem Description:
# Sometimes people repeat letters to represent extra feeling. For example:
#
#
# 	"hello" -> "heeellooo"
# 	"hi" -> "hiiii"
#
#
# In these strings like "heeellooo", we have groups of adjacent letters that are all the same: "h", "eee", "ll", "ooo".
#
# You are given a string s and an array of query strings words. A query word is stretchy if it can be made to be equal to s by any number of applications of the following extension operation: choose a group consisting of characters c, and add some number of characters c to the group so that the size of the group is three or more.
#
#
# 	For example, starting with "hello", we could do an extension on the group "o" to get "hellooo", but we cannot get "helloo" since the group "oo" has a size less than three. Also, we could do another extension like "ll" -> "lllll" to get "helllllooo". If s = "helllllooo", then the query word "hello" would be stretchy because of these two extension operations: query = "hello" -> "hellooo" -> "helllllooo" = s.
#
#
# Return the number of query strings that are stretchy.
#
# Example:
# Input: s = "heeellooo", words = ["hello", "hi", "helo"]
# Output: 1
# Explanation: 
# We can extend "e" and "o" in the word "hello" to get "heeellooo".
# We can't extend "helo" to get "heeellooo" because the group "ll" is not size 3 or more.
#
# Constraints:
# 1 <= s.length, words.length <= 100
# 	1 <= words[i].length <= 100
# 	s and words[i] consist of lowercase letters.
#

class Solution(object):
    def expressiveWords(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: int
        """
        def get_groups(word):
            groups = []
            i = 0
            while i < len(word):
                char = word[i]
                count = 0
                while i < len(word) and word[i] == char:
                    count += 1
                    i += 1
                groups.append((char, count))
            return groups

        s_groups = get_groups(s)
        stretchy_count = 0

        for word in words:
            w_groups = get_groups(word)
            if len(s_groups) != len(w_groups):
                continue

            is_stretchy = True
            for (s_char, s_count), (w_char, w_count) in zip(s_groups, w_groups):
                if s_char != w_char:
                    is_stretchy = False
                    break
                if s_count < 3 and s_count != w_count:
                    is_stretchy = False
                    break
                if s_count >= 3 and w_count > s_count:
                    is_stretchy = False
                    break

            if is_stretchy:
                stretchy_count += 1

        return stretchy_count