// Source: https://leetcode.com/problems/text-justification/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of strings words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.
//
// You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.
//
// Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line does not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.
//
// For the last line of text, it should be left-justified, and no extra space is inserted between words.
//
// Note:
//
//
// 	A word is defined as a character sequence consisting of non-space characters only.
// 	Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
// 	The input array words contains at least one word.
//
// Example:
// Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
// Output:
// [
//    "This    is    an",
//    "example  of text",
//    "justification.  "
// ]
//
// Constraints:
// 1 <= words.length <= 300
// 	1 <= words[i].length <= 20
// 	words[i] consists of only English letters and symbols.
// 	1 <= maxWidth <= 100
// 	words[i].length <= maxWidth
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize) {
    char** result = (char**)malloc(sizeof(char*) * 500); // Allocate space for up to 500 lines
    *returnSize = 0;

    int index = 0;
    while (index < wordsSize) {
        int totalChars = strlen(words[index]);
        int last = index + 1;

        while (last < wordsSize) {
            if (totalChars + 1 + strlen(words[last]) > maxWidth) break;
            totalChars += 1 + strlen(words[last]);
            last++;
        }

        int gaps = last - index - 1;
        char* line = (char*)malloc(sizeof(char) * (maxWidth + 1));
        line[0] = '\0';

        // If we're on the last line or the line has only one word, left-justify
        if (last == wordsSize || gaps == 0) {
            for (int i = index; i < last; i++) {
                strcat(line, words[i]);
                if (i < last - 1) {
                    strcat(line, " ");
                }
            }
            int remainingSpaces = maxWidth - strlen(line);
            for (int i = 0; i < remainingSpaces; i++) {
                strcat(line, " ");
            }
        } else {
            // Middle justify
            int totalSpaces = maxWidth - totalChars + gaps;
            int spaceBetweenWords = totalSpaces / gaps;
            int extraSpaces = totalSpaces % gaps;

            for (int i = index; i < last; i++) {
                strcat(line, words[i]);
                if (i < last - 1) {
                    for (int s = 0; s < spaceBetweenWords; s++) {
                        strcat(line, " ");
                    }
                    if (extraSpaces > 0) {
                        strcat(line, " ");
                        extraSpaces--;
                    }
                }
            }
        }

        result[*returnSize] = line;
        (*returnSize)++;
        index = last;
    }

    return result;
}
