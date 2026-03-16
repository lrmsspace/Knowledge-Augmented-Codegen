// Source: https://leetcode.com/problems/minimum-number-of-frogs-croaking/   |   Difficulty: Medium
//
// Problem Description:
// You are given the string croakOfFrogs, which represents a combination of the string "croak" from different frogs, that is, multiple frogs can croak at the same time, so multiple "croak" are mixed.
//
// Return the minimum number of different frogs to finish all the croaks in the given string.
//
// A valid "croak" means a frog is printing five letters 'c', 'r', 'o', 'a', and 'k' sequentially. The frogs have to print all five letters to finish a croak. If the given string is not a combination of a valid "croak" return -1.
//
// Example:
// Input: croakOfFrogs = "croakcroak"
// Output: 1 
// Explanation: One frog yelling "croak" twice.
//
// Constraints:
// 1 <= croakOfFrogs.length <= 105
// 	croakOfFrogs is either 'c', 'r', 'o', 'a', or 'k'.
//

class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        vector<int> count(5, 0); // c, r, o, a, k
        int frogs = 0;
        int maxFrogs = 0;

        for (char ch : croakOfFrogs) {
            int idx = getIndex(ch);
            if (idx == 0) {
                count[0]++;
                frogs++;
                maxFrogs = max(maxFrogs, frogs);
            } else {
                if (count[idx - 1] == 0) {
                    return -1; // Invalid sequence
                }
                count[idx - 1]--;
                if (idx == 4) {
                    frogs--; // A frog finished croaking
                } else {
                    count[idx]++;
                }
            }
        }

        // Check if all counts except for 'k' are zero
        for (int i = 0; i < 4; ++i) {
            if (count[i] != 0) {
                return -1; // Incomplete croak sequences
            }
        }

        return maxFrogs;            
    }
};
