# Source: https://leetcode.com/problems/maximum-score-words-formed-by-letters/   |   Difficulty: Hard
#
# Problem Description:
# Given a list of words, list of  single letters (might be repeating) and score of every character.
#
# Return the maximum score of any valid set of words formed by using the given letters (words[i] cannot be used two or more times).
#
# It is not necessary to use all characters in letters and each letter can only be used once. Score of letters 'a', 'b', 'c', ... ,'z' is given by score[0], score[1], ... , score[25] respectively.
#
# Example:
# Input: words = ["dog","cat","dad","good"], letters = ["a","a","c","d","d","d","g","o","o"], score = [1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]
# Output: 23
# Explanation:
# Score  a=1, c=9, d=5, g=3, o=2
# Given letters, we can form the words "dad" (5+1+5) and "good" (3+2+2+5) with a score of 23.
# Words "dad" and "dog" only get a score of 21.
#
# Constraints:
# 1 <= words.length <= 14
# 	1 <= words[i].length <= 15
# 	1 <= letters.length <= 100
# 	letters[i].length == 1
# 	score.length == 26
# 	0 <= score[i] <= 10
# 	words[i], letters[i] contains only lower case English letters.
#

class Solution(object):
    def maxScoreWords(self, words, letters, score):
        """
        :type words: List[str]
        :type letters: List[str]
        :type score: List[int]
        :rtype: int
        """
        from collections import Counter

        letter_count = Counter(letters)
        n = len(words)
        max_score = 0

        def backtrack(index, current_count, current_score):
            nonlocal max_score
            if index == n:
                max_score = max(max_score, current_score)
                return

            # Skip the current word
            backtrack(index + 1, current_count, current_score)

            # Try to include the current word
            word = words[index]
            word_count = Counter(word)
            can_use_word = True
            word_score = 0

            for char, cnt in word_count.items():
                if current_count[char] < cnt:
                    can_use_word = False
                    break
                word_score += score[ord(char) - ord('a')] * cnt

            if can_use_word:
                for char, cnt in word_count.items():
                    current_count[char] -= cnt

                backtrack(index + 1, current_count, current_score + word_score)

                for char, cnt in word_count.items():
                    current_count[char] += cnt

        backtrack(0, letter_count, 0)
        return max_score