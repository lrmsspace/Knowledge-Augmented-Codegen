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

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int n = words.size();
        int index = 0;
        
        while (index < n) {
            int totalChars = words[index].length();
            int last = index + 1;
            
            while (last < n) {
                if (totalChars + 1 + words[last].length() > maxWidth) break;
                totalChars += 1 + words[last].length();
                last++;
            }
            
            string line;
            int numberOfWords = last - index;
            // If last line or number of words in the line is 1, left-justified
            if (last == n || numberOfWords == 1) {
                for (int i = index; i < last; i++) {
                    line += words[i];
                    if (i < last - 1) line += " ";
                }
                line += string(maxWidth - line.length(), ' ');
            } else {
                int totalSpaces = maxWidth - totalChars + (numberOfWords - 1);
                int spaceBetweenWords = totalSpaces / (numberOfWords - 1);
                int extraSpaces = totalSpaces % (numberOfWords - 1);
                
                for (int i = index; i < last; i++) {
                    line += words[i];
                    if (i < last - 1) {
                        line += string(spaceBetweenWords + (i - index < extraSpaces ? 1 : 0), ' ');
                    }
                }
            }
            
            result.push_back(line);
            index = last;
        }
        
        return result;          
    }
};
