// Source: https://leetcode.com/problems/number-of-burgers-with-no-waste-of-ingredients/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers tomatoSlices and cheeseSlices. The ingredients of different burgers are as follows:
//
//
// 	Jumbo Burger: 4 tomato slices and 1 cheese slice.
// 	Small Burger: 2 Tomato slices and 1 cheese slice.
//
//
// Return [total_jumbo, total_small] so that the number of remaining tomatoSlices equal to 0 and the number of remaining cheeseSlices equal to 0. If it is not possible to make the remaining tomatoSlices and cheeseSlices equal to 0 return [].
//
// Example:
// Input: tomatoSlices = 16, cheeseSlices = 7
// Output: [1,6]
// Explantion: To make one jumbo burger and 6 small burgers we need 4*1 + 2*6 = 16 tomato and 1 + 6 = 7 cheese.
// There will be no remaining ingredients.
//
// Constraints:
// 0 <= tomatoSlices, cheeseSlices <= 107
//

class Solution {
public:
    vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices) {
        // Let x be the number of jumbo burgers and y be the number of small burgers
        // We have the following equations:
        // 4x + 2y = tomatoSlices  (1)
        // x + y = cheeseSlices     (2)
        //
        // From (2), we can express y as:
        // y = cheeseSlices - x
        //
        // Substituting y in (1):
        // 4x + 2(cheeseSlices - x) = tomatoSlices
        // 4x + 2cheeseSlices - 2x = tomatoSlices
        // 2x + 2cheeseSlices = tomatoSlices
        // 2x = tomatoSlices - 2cheeseSlices
        // x = (tomatoSlices - 2cheeseSlices) / 2
        //
        // Now substituting x back to find y:
        // y = cheeseSlices - (tomatoSlices - 2cheeseSlices) / 2
        // y = (2cheeseSlices - (tomatoSlices - 2cheeseSlices)) / 2
        // y = (4cheeseSlices - tomatoSlices) / 2

        if (tomatoSlices % 2 != 0) {
            return {};
        }

        int x = (tomatoSlices - 2 * cheeseSlices) / 2;
        int y = (4 * cheeseSlices - tomatoSlices) / 2;

        if (x < 0 || y < 0) {
            return {};
        }

        return {x, y};          
    }
};
