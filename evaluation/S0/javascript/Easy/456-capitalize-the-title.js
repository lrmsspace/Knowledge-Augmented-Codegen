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

/**
 * @param {string} title
 * @return {string}
 */
var capitalizeTitle = function(title) {
    const words = title.split(' ');
    for (let i = 0; i < words.length; i++) {
        if (words[i].length <= 2) {
            words[i] = words[i].toLowerCase();
        } else {
            words[i] = words[i][0].toUpperCase() + words[i].slice(1).toLowerCase();
        }
    }
    return words.join(' ');
};
