// Source: https://leetcode.com/problems/verbal-arithmetic-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// Given an equation, represented by words on the left side and the result on the right side.
//
// You need to check if the equation is solvable under the following rules:
//
//
// 	Each character is decoded as one digit (0 - 9).
// 	No two characters can map to the same digit.
// 	Each words[i] and result are decoded as one number without leading zeros.
// 	Sum of numbers on the left side (words) will equal to the number on the right side (result).
//
//
// Return true if the equation is solvable, otherwise return false.
//
// Example:
// Input: words = ["SEND","MORE"], result = "MONEY"
// Output: true
// Explanation: Map 'S'-> 9, 'E'->5, 'N'->6, 'D'->7, 'M'->1, 'O'->0, 'R'->8, 'Y'->'2'
// Such that: "SEND" + "MORE" = "MONEY" ,  9567 + 1085 = 10652
//
// Constraints:
// 2 <= words.length <= 5
// 	1 <= words[i].length, result.length <= 7
// 	words[i], result contain only uppercase English letters.
// 	The number of different characters used in the expression is at most 10.
//

bool isSolvable(char** words, int wordsSize, char* result) {
    int charToDigit[26];
    bool usedDigits[10];
    bool leadingChar[26];
    int charCount = 0;
    int wordCount = wordsSize + 1; // including result
    char* allWords[wordCount];
    int lengths[wordCount];

    for (int i = 0; i < 26; i++) {
        charToDigit[i] = -1;
        leadingChar[i] = false;
    }
    for (int i = 0; i < 10; i++) {
        usedDigits[i] = false;
    }

    for (int i = 0; i < wordsSize; i++) {
        allWords[i] = words[i];
        lengths[i] = strlen(words[i]);
        if (lengths[i] > 0) {
            leadingChar[words[i][0] - 'A'] = true;
        }
    }
    allWords[wordsSize] = result;
    lengths[wordsSize] = strlen(result);
    if (lengths[wordsSize] > 0) {
        leadingChar[result[0] - 'A'] = true;
    }

    for (int i = 0; i < wordCount; i++) {
        for (int j = 0; j < lengths[i]; j++) {
            int idx = allWords[i][j] - 'A';
            if (charToDigit[idx] == -1) {
                charToDigit[idx] = charCount++;
            }
        }
    }

    if (charCount > 10) {
        return false;
    }

    int digits[10];
    for (int i = 0; i < 10; i++) {
        digits[i] = i;
    }

    bool backtrack(int pos) {
        if (pos == charCount) {
            long long sum = 0;
            for (int i = 0; i < wordsSize; i++) {
                long long num = 0;
                for (int j = 0; j < lengths[i]; j++) {
                    num = num * 10 + charToDigit[allWords[i][j] - 'A'];
                }
                sum += num;
            }
            long long resultNum = 0;
            for (int j = 0; j < lengths[wordsSize]; j++) {
                resultNum = resultNum * 10 + charToDigit[allWords[wordsSize][j] - 'A'];
            }
            return sum == resultNum;
        }

        for (int d = 0; d < 10; d++) {
            if (!usedDigits[d]) {
                int chIdx;
                for (chIdx = 0; chIdx < 26; chIdx++) {
                    if (charToDigit[chIdx] == pos) {
                        break;
                    }
                }
                if (leadingChar[chIdx] && d == 0) {
                    continue;
                }

                usedDigits[d] = true;
                charToDigit[chIdx] = d;

                if (backtrack(pos + 1)) {
                    return true;
                }

                usedDigits[d] = false;
                charToDigit[chIdx] = pos;
            }
        }
        return false;
    }
    return backtrack(0);
            
}
