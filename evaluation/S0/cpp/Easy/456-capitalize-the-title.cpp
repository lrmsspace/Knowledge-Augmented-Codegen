// Source: https://leetcode.com/problems/capitalize-the-title/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string title consisting of one or more words separated by a single space, where each word consists of English letters. Capitalize the string by changing the capitalization of each word such that:
//
//
// 	If the length of the word is 1 or 2 letters, change all letters to lowercase.
// 	Otherwise, change the first letter to uppercase and the remaining letters to lowercase.
//
//
// Return the capitalized title.
//
// Example:
// Input: title = "capiTalIze tHe titLe"
// Output: "Capitalize The Title"
// Explanation:
// Since all the words have a length of at least 3, the first letter of each word is uppercase, and the remaining letters are lowercase.
//
// Constraints:
// 1 <= title.length <= 100
// 	title consists of words separated by a single space without any leading or trailing spaces.
// 	Each word consists of uppercase and lowercase English letters and is non-empty.
//

class Solution {
public:
    string capitalizeTitle(string title) {
        stringstream ss(title);
        string word;
        string result;

        while (ss >> word) {
            if (word.length() <= 2) {
                for (char &c : word) {
                    c = tolower(c);
                }
            } else {
                word[0] = toupper(word[0]);
                for (size_t i = 1; i < word.length(); ++i) {
                    word[i] = tolower(word[i]);
                }
            }
            if (!result.empty()) {
                result += " ";
            }
            result += word;
        }

        return result;          
    }
};
