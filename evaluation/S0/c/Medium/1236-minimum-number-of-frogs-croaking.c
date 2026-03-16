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

int minNumberOfFrogs(char* croakOfFrogs) {
    int counts[5] = {0}; // counts for 'c', 'r', 'o', 'a', 'k'
    int maxFrogs = 0;
    int currentFrogs = 0;

    for (int i = 0; croakOfFrogs[i] != '\0'; i++) {
        char ch = croakOfFrogs[i];
        int index;

        switch (ch) {
            case 'c': index = 0; break;
            case 'r': index = 1; break;
            case 'o': index = 2; break;
            case 'a': index = 3; break;
            case 'k': index = 4; break;
            default: return -1; // invalid character
        }

        counts[index]++;

        // Check the sequence validity
        for (int j = 1; j < 5; j++) {
            if (counts[j] > counts[j - 1]) {
                return -1; // invalid sequence
            }
        }

        if (ch == 'c') {
            currentFrogs++;
            if (currentFrogs > maxFrogs) {
                maxFrogs = currentFrogs;
            }
        } else if (ch == 'k') {
            currentFrogs--;
        }
    }

    // At the end, all counts except for 'k' should be equal
    for (int j = 0; j < 4; j++) {
        if (counts[j] != counts[4]) {
            return -1; // incomplete croak
        }
    }

    return maxFrogs;        
}
