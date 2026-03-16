# Source: https://leetcode.com/problems/reorder-data-in-log-files/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of logs. Each log is a space-delimited string of words, where the first word is the identifier.
#
# There are two types of logs:
#
#
# 	Letter-logs: All words (except the identifier) consist of lowercase English letters.
# 	Digit-logs: All words (except the identifier) consist of digits.
#
#
# Reorder these logs so that:
#
#
# 	The letter-logs come before all digit-logs.
# 	The letter-logs are sorted lexicographically by their contents. If their contents are the same, then sort them lexicographically by their identifiers.
# 	The digit-logs maintain their relative ordering.
#
#
# Return the final order of the logs.
#
# Example:
# Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"]
# Output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"]
# Explanation:
# The letter-log contents are all different, so their ordering is "art can", "art zero", "own kit dig".
# The digit-logs have a relative order of "dig1 8 1 5 1", "dig2 3 6".
#
# Constraints:
# 1 <= logs.length <= 100
# 	3 <= logs[i].length <= 100
# 	All the tokens of logs[i] are separated by a single space.
# 	logs[i] is guaranteed to have an identifier and at least one word after the identifier.
#

class Solution(object):
    def reorderLogFiles(self, logs):
        """
        :type logs: List[str]
        :rtype: List[str]
        """
        letter_logs = []
        digit_logs = []
        
        for log in logs:
            identifier, rest = log.split(" ", 1)
            if rest[0].isalpha():
                letter_logs.append((identifier, rest))
            else:
                digit_logs.append(log)
        
        # Sort letter logs first by content, then by identifier
        letter_logs.sort(key=lambda x: (x[1], x[0]))
        
        # Reconstruct the sorted letter logs
        sorted_letter_logs = [f"{identifier} {rest}" for identifier, rest in letter_logs]
        
        # Combine letter logs and digit logs
        return sorted_letter_logs + digit_logs