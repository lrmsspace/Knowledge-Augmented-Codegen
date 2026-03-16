// Source: https://leetcode.com/problems/minimize-deviation-in-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n positive integers.
//
// You can perform two types of operations on any element of the array any number of times:
//
//
// 	If the element is even, divide it by 2.
//
// 	
// 		For example, if the array is [1,2,3,4], then you can do this operation on the last element, and the array will be [1,2,3,2].
// 	
// 	
// 	If the element is odd, multiply it by 2.
// 	
// 		For example, if the array is [1,2,3,4], then you can do this operation on the first element, and the array will be [2,2,3,4].
// 	
// 	
//
//
// The deviation of the array is the maximum difference between any two elements in the array.
//
// Return the minimum deviation the array can have after performing some number of operations.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 1
// Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2], then the deviation will be 3 - 2 = 1.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 5 * 104
// 	1 <= nums[i] <= 109
//

class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        priority_queue<int> maxHeap;
        int minVal = INT_MAX;
        
        // Preprocess: make all numbers even
        for (int num : nums) {
            if (num % 2 == 1) {
                num *= 2;
            }
            maxHeap.push(num);
            minVal = min(minVal, num);
        }
        
        int minDeviation = INT_MAX;
        
        while (!maxHeap.empty()) {
            int maxVal = maxHeap.top();
            maxHeap.pop();
            
            minDeviation = min(minDeviation, maxVal - minVal);
            
            // If maxVal is even, we can reduce it
            if (maxVal % 2 == 0) {
                int newVal = maxVal / 2;
                minVal = min(minVal, newVal);
                maxHeap.push(newVal);
            } else {
                // If maxVal is odd, we cannot reduce it further
                break;
            }
        }
        
        return minDeviation;            
    }
};
