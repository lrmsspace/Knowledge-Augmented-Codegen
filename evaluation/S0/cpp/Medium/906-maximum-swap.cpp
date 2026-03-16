// Source: https://leetcode.com/problems/maximum-swap/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer num. You can swap two digits at most once to get the maximum valued number.
//
// Return the maximum valued number you can get.
//
// Example:
// Input: num = 2736
// Output: 7236
// Explanation: Swap the number 2 and the number 7.
//
// Constraints:
// 0 <= num <= 108
//

class Solution {
public:
    int maximumSwap(int num) {
        string numStr = to_string(num);
        int n = numStr.size();
        vector<int> last(10, -1);

        // Record the last occurrence of each digit
        for (int i = 0; i < n; ++i) {
            last[numStr[i] - '0'] = i;
        }

        // Try to find a swap that increases the number
        for (int i = 0; i < n; ++i) {
            for (int d = 9; d > numStr[i] - '0'; --d) {
                if (last[d] > i) {
                    swap(numStr[i], numStr[last[d]]);
                    return stoi(numStr);
                }
            }
        }

        return num; // No swap needed, return original number           
    }
};
