# Source: https://leetcode.com/problems/statistics-from-a-large-sample/   |   Difficulty: Medium
#
# Problem Description:
# You are given a large sample of integers in the range [0, 255]. Since the sample is so large, it is represented by an array count where count[k] is the number of times that k appears in the sample.
#
# Calculate the following statistics:
#
#
# 	minimum: The minimum element in the sample.
# 	maximum: The maximum element in the sample.
# 	mean: The average of the sample, calculated as the total sum of all elements divided by the total number of elements.
# 	median:
# 	
# 		If the sample has an odd number of elements, then the median is the middle element once the sample is sorted.
# 		If the sample has an even number of elements, then the median is the average of the two middle elements once the sample is sorted.
# 	
# 	
# 	mode: The number that appears the most in the sample. It is guaranteed to be unique.
#
#
# Return the statistics of the sample as an array of floating-point numbers [minimum, maximum, mean, median, mode]. Answers within 10-5 of the actual answer will be accepted.
#
# Example:
# Input: count = [0,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
# Output: [1.00000,3.00000,2.37500,2.50000,3.00000]
# Explanation: The sample represented by count is [1,2,2,2,3,3,3,3].
# The minimum and maximum are 1 and 3 respectively.
# The mean is (1+2+2+2+3+3+3+3) / 8 = 19 / 8 = 2.375.
# Since the size of the sample is even, the median is the average of the two middle elements 2 and 3, which is 2.5.
# The mode is 3 as it appears the most in the sample.
#
# Constraints:
# count.length == 256
# 	0 <= count[i] <= 109
# 	1 <= sum(count) <= 109
# 	The mode of the sample that count represents is unique.
#

class Solution(object):
    def sampleStats(self, count):
        """
        :type count: List[int]
        :rtype: List[float]
        """
        minimum = None
        maximum = None
        total_sum = 0
        total_count = 0
        mode = 0
        mode_count = 0
        
        for i in range(256):
            if count[i] > 0:
                if minimum is None:
                    minimum = i
                maximum = i
                total_sum += i * count[i]
                total_count += count[i]
                if count[i] > mode_count:
                    mode_count = count[i]
                    mode = i
        
        mean = total_sum / total_count
        
        # Calculate median
        mid1 = (total_count + 1) // 2
        mid2 = (total_count + 2) // 2
        median1 = None
        median2 = None
        cumulative_count = 0
        
        for i in range(256):
            cumulative_count += count[i]
            if median1 is None and cumulative_count >= mid1:
                median1 = i
            if median2 is None and cumulative_count >= mid2:
                median2 = i
            if median1 is not None and median2 is not None:
                break
        
        median = (median1 + median2) / 2.0
        
        return [float(minimum), float(maximum), float(mean), float(median), float(mode)]