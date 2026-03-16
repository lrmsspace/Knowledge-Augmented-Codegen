# Source: https://leetcode.com/problems/compare-version-numbers/   |   Difficulty: Medium
#
# Problem Description:
# Given two version strings, version1 and version2, compare them. A version string consists of revisions separated by dots '.'. The value of the revision is its integer conversion ignoring leading zeros.
#
# To compare version strings, compare their revision values in left-to-right order. If one of the version strings has fewer revisions, treat the missing revision values as 0.
#
# Return the following:
#
#
# 	If version1 < version2, return -1.
# 	If version1 > version2, return 1.
# 	Otherwise, return 0.
#
# Example:
# Input: version1 = "1.2", version2 = "1.10"
#
# Output: -1
#
# Explanation:
#
# version1's second revision is "2" and version2's second revision is "10": 2 < 10, so version1 < version2.
#
# Constraints:
# 1 <= version1.length, version2.length <= 500
# 	version1 and version2 only contain digits and '.'.
# 	version1 and version2 are valid version numbers.
# 	All the given revisions in version1 and version2 can be stored in a 32-bit integer.
#

class Solution(object):
    def compareVersion(self, version1, version2):
        """
        :type version1: str
        :type version2: str
        :rtype: int
        """
        v1_parts = list(map(int, version1.split('.')))
        v2_parts = list(map(int, version2.split('.')))
        
        # Extend the shorter list with zeros
        max_length = max(len(v1_parts), len(v2_parts))
        v1_parts.extend([0] * (max_length - len(v1_parts)))
        v2_parts.extend([0] * (max_length - len(v2_parts)))
        
        for i in range(max_length):
            if v1_parts[i] < v2_parts[i]:
                return -1
            elif v1_parts[i] > v2_parts[i]:
                return 1
        
        return 0