# Source: https://leetcode.com/problems/minimum-operations-to-make-character-frequencies-equal/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s.
#
# A string t is called good if all characters of t occur the same number of times.
#
# You can perform the following operations any number of times:
#
#
#  Delete a character from s.
#  Insert a character in s.
#  Change a character in s to its next letter in the alphabet.
#
#
# Note that you cannot change 'z' to 'a' using the third operation.
#
# Return the minimum number of operations required to make s good.
#
# Example:
# Input: s = "acab"
#
# Output: 1
#
# Explanation:
#
# We can make s good by deleting one occurrence of character 'a'.
#
# Constraints:
# 3 <= s.length <= 2 * 104
#  s contains only lowercase English letters.
#

class Solution(object):
    def makeStringGood(self, s):
        """
        :type s: str
        :rtype: int
        """
        from collections import Counter
        freq = Counter(s)
        counts = list(freq.values())
        unique_counts = set(counts)
        min_operations = float('inf')

        for target in range(1, max(counts) + 1):
            operations = 0
            for count in counts:
                if count < target:
                    operations += target - count  # Insertions
                elif count > target:
                    operations += count - target  # Deletions
            min_operations = min(min_operations, operations)

        return min_operations