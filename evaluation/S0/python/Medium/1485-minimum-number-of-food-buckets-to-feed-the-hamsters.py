# Source: https://leetcode.com/problems/minimum-number-of-food-buckets-to-feed-the-hamsters/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed string hamsters where hamsters[i] is either:
#
#
# 	'H' indicating that there is a hamster at index i, or
# 	'.' indicating that index i is empty.
#
#
# You will add some number of food buckets at the empty indices in order to feed the hamsters. A hamster can be fed if there is at least one food bucket to its left or to its right. More formally, a hamster at index i can be fed if you place a food bucket at index i - 1 and/or at index i + 1.
#
# Return the minimum number of food buckets you should place at empty indices to feed all the hamsters or -1 if it is impossible to feed all of them.
#
# Example:
# Input: hamsters = "H..H"
# Output: 2
# Explanation: We place two food buckets at indices 1 and 2.
# It can be shown that if we place only one food bucket, one of the hamsters will not be fed.
#
# Constraints:
# 1 <= hamsters.length <= 105
# 	hamsters[i] is either'H' or '.'.
#

class Solution(object):
    def minimumBuckets(self, hamsters):
        """
        :type hamsters: str
        :rtype: int
        """
        n = len(hamsters)
        buckets = 0
        i = 0
        
        while i < n:
            if hamsters[i] == 'H':
                if i + 1 < n and hamsters[i + 1] == '.':
                    buckets += 1
                    i += 3  # Skip the next position as we placed a bucket there
                elif i - 1 >= 0 and hamsters[i - 1] == '.':
                    buckets += 1
                    i += 1
                else:
                    return -1  # Impossible to feed this hamster
            else:
                i += 1
        
        return buckets