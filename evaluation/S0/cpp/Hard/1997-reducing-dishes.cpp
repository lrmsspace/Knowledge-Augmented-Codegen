// Source: https://leetcode.com/problems/reducing-dishes/   |   Difficulty: Hard
//
// Problem Description:
// A chef has collected data on the satisfaction level of his n dishes. Chef can cook any dish in 1 unit of time.
//
// Like-time coefficient of a dish is defined as the time taken to cook that dish including previous dishes multiplied by its satisfaction level i.e. time[i] * satisfaction[i].
//
// Return the maximum sum of like-time coefficient that the chef can obtain after preparing some amount of dishes.
//
// Dishes can be prepared in any order and the chef can discard some dishes to get this maximum value.
//
// Example:
// Input: satisfaction = [-1,-8,0,5,-9]
// Output: 14
// Explanation: After Removing the second and last dish, the maximum total like-time coefficient will be equal to (-1*1 + 0*2 + 5*3 = 14).
// Each dish is prepared in one unit of time.
//
// Constraints:
// n == satisfaction.length
// 	1 <= n <= 500
// 	-1000 <= satisfaction[i] <= 1000
//

class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        sort(satisfaction.begin(), satisfaction.end(), greater<int>());
        int n = satisfaction.size();
        int total = 0, curr = 0, result = 0;
        
        for (int i = 0; i < n; i++) {
            curr += satisfaction[i];
            if (curr <= 0) break;
            total += curr;
        }
        
        return total;           
    }
};
