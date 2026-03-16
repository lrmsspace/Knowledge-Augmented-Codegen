# Source: https://leetcode.com/problems/text-justification/   |   Difficulty: Hard
#
# Problem Description:
# Given an array of strings words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.
#
# You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.
#
# Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line does not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.
#
# For the last line of text, it should be left-justified, and no extra space is inserted between words.
#
# Note:
#
#
# 	A word is defined as a character sequence consisting of non-space characters only.
# 	Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
# 	The input array words contains at least one word.
#
# Example:
# Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
# Output:
# [
#    "This    is    an",
#    "example  of text",
#    "justification.  "
# ]
#
# Constraints:
# 1 <= words.length <= 300
# 	1 <= words[i].length <= 20
# 	words[i] consists of only English letters and symbols.
# 	1 <= maxWidth <= 100
# 	words[i].length <= maxWidth
#

class Solution(object):
    def fullJustify(self, words, maxWidth):
        """
        :type words: List[str]
        :type maxWidth: int
        :rtype: List[str]
        """
        res = []
        i = 0
        n = len(words)
        
        while i < n:
            j = i
            line_length = 0
            
            # Determine how many words can fit in the current line
            while j < n and line_length + len(words[j]) + (j - i) <= maxWidth:
                line_length += len(words[j])
                j += 1
            
            line = ""
            num_words = j - i
            
            # If it's the last line or contains only one word, left-justify
            if j == n or num_words == 1:
                for k in range(i, j):
                    line += words[k] + " "
                line = line.strip()
                line += " " * (maxWidth - len(line))
            else:
                total_spaces = maxWidth - line_length
                space_between_words = total_spaces // (num_words - 1)
                extra_spaces = total_spaces % (num_words - 1)
                
                for k in range(i, j - 1):
                    line += words[k]
                    line += " " * (space_between_words + (1 if k - i < extra_spaces else 0))
                line += words[j - 1]
            
            res.append(line)
            i = j
        
        return res