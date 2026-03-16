// Source: https://leetcode.com/problems/set-intersection-size-at-least-two/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array intervals where intervals[i] = [starti, endi] represents all the integers from starti to endi inclusively.
//
// A containing set is an array nums where each interval from intervals has at least two integers in nums.
//
//
// 	For example, if intervals = [[1,3], [3,7], [8,9]], then [1,2,4,7,8,9] and [2,3,4,8,9] are containing sets.
//
//
// Return the minimum possible size of a containing set.
//
// Example:
// Input: intervals = [[1,3],[3,7],[8,9]]
// Output: 5
// Explanation: let nums = [2, 3, 4, 8, 9].
// It can be shown that there cannot be any containing array of size 4.
//
// Constraints:
// 1 <= intervals.length <= 3000
// 	intervals[i].length == 2
// 	0 <= starti < endi <= 108
//

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[1] == b[1]) return a[0] > b[0];
            return a[1] < b[1];
        });
        
        int n = intervals.size();
        vector<int> nums;
        
        // Add the last two elements of the first interval
        nums.push_back(intervals[0][1] - 1);
        nums.push_back(intervals[0][1]);
        
        for (int i = 1; i < n; i++) {
            int start = intervals[i][0];
            int end = intervals[i][1];
            
            int count = 0;
            for (int num : nums) {
                if (num >= start && num <= end) {
                    count++;
                }
            }
            
            if (count >= 2) continue;
            else if (count == 1) {
                // Add one more element
                int toAdd = end;
                if (nums.back() == end) {
                    toAdd = end - 1;
                }
                nums.push_back(toAdd);
            } else {
                // Add two elements
                nums.push_back(end - 1);
                nums.push_back(end);
            }
        }
        
        return nums.size();         
    }
};
