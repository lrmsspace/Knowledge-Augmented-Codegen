// Source: https://leetcode.com/problems/minimum-number-of-groups-to-create-a-valid-assignment/   |   Difficulty: Medium
//
// Problem Description:
// You are given a collection of numbered balls and instructed to sort them into boxes for a nearly balanced distribution. There are two rules you must follow:
//
//
// 	Balls with the same box must have the same value. But, if you have more than one ball with the same number, you can put them in different boxes.
// 	The biggest box can only have one more ball than the smallest box.
//
//
// ​Return the fewest number of boxes to sort these balls following these rules.
//
// Example:
// Input:   balls = [3,2,3,2,3] 
//
// Output:   2 
//
// Explanation:
//
// We can sort balls into boxes as follows:
//
//
// 	[3,3,3]
// 	[2,2]
//
//
// The size difference between the two boxes doesn't exceed one.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
public:
    int minGroupsForValidAssignment(vector<int>& balls) {
        unordered_map<int, int> frequencyMap;
        int maxFrequency = 0;

        // Count the frequency of each ball number
        for (int ball : balls) {
            frequencyMap[ball]++;
            maxFrequency = max(maxFrequency, frequencyMap[ball]);
        }

        // Count how many numbers have the maximum frequency
        int countMaxFrequency = 0;
        for (const auto& entry : frequencyMap) {
            if (entry.second == maxFrequency) {
                countMaxFrequency++;
            }
        }

        // The minimum number of boxes needed is equal to the maximum frequency
        return maxFrequency;            
    }
};
