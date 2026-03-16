# Source: https://leetcode.com/problems/recover-the-original-array/   |   Difficulty: Hard
#
# Problem Description:
# Alice had a 0-indexed array arr consisting of n positive integers. She chose an arbitrary positive integer k and created two new 0-indexed integer arrays lower and higher in the following manner:
#
#
# 	lower[i] = arr[i] - k, for every index i where 0 <= i < n
# 	higher[i] = arr[i] + k, for every index i where 0 <= i < n
#
#
# Unfortunately, Alice lost all three arrays. However, she remembers the integers that were present in the arrays lower and higher, but not the array each integer belonged to. Help Alice and recover the original array.
#
# Given an array nums consisting of 2n integers, where exactly n of the integers were present in lower and the remaining in higher, return the original array arr. In case the answer is not unique, return any valid array.
#
# Note: The test cases are generated such that there exists at least one valid array arr.
#
# Example:
# Input: nums = [2,10,6,4,8,12]
# Output: [3,7,11]
# Explanation:
# If arr = [3,7,11] and k = 1, we get lower = [2,6,10] and higher = [4,8,12].
# Combining lower and higher gives us [2,6,10,4,8,12], which is a permutation of nums.
# Another valid possibility is that arr = [5,7,9] and k = 3. In that case, lower = [2,4,6] and higher = [8,10,12].
#
# Constraints:
# 2 * n == nums.length
# 	1 <= n <= 1000
# 	1 <= nums[i] <= 109
# 	The test cases are generated such that there exists at least one valid array arr.
#

class Solution(object):
    def recoverArray(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        nums.sort()
        n = len(nums)
        
        for i in range(1, n):
            diff = nums[i] - nums[0]
            if diff <= 0 or diff % 2 != 0:
                continue
            k = diff // 2
            
            lower = set()
            higher = set()
            original = []
            used = [False] * n
            
            for j in range(n):
                if used[j]:
                    continue
                if nums[j] - k in lower:
                    lower.remove(nums[j] - k)
                    higher.add(nums[j])
                    original.append(nums[j] - k + k)
                    used[j] = True
                elif nums[j] + k in higher:
                    higher.remove(nums[j] + k)
                    lower.add(nums[j])
                    original.append(nums[j] + k - k)
                    used[j] = True
                else:
                    lower.add(nums[j] - k)
                    higher.add(nums[j] + k)
            
            if len(original) * 2 == n:
                return original
        
        return None