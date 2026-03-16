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
 * @param {string[]} words
 * @param {number} maxWidth
 * @return {string[]}
 */
var fullJustify = function(words, maxWidth) {
    const result = [];
    let index = 0;
    while (index < words.length) {
        let totalChars = words[index].length;
        let last = index + 1;
        while (last < words.length) {
            if (totalChars + 1 + words[last].length > maxWidth) break;
            totalChars += 1 + words[last].length;
            last++;
        }
        let line = '';
        const numberOfWords = last - index;
        if (last === words.length || numberOfWords === 1) {
            for (let i = index; i < last; i++) {
                line += words[i] + ' ';
            }
            line = line.trim();
            while (line.length < maxWidth) {
                line += ' ';
            }
        } else {
            const totalSpaces = maxWidth - totalChars + (numberOfWords - 1);
            const spaceBetweenWords = Math.floor(totalSpaces / (numberOfWords - 1));
            let extraSpaces = totalSpaces % (numberOfWords - 1);
            for (let i = index; i < last - 1; i++) {    
                line += words[i];
                line += ' '.repeat(spaceBetweenWords + (extraSpaces > 0 ? 1 : 0));
                if (extraSpaces > 0) extraSpaces--;
            }
            line += words[last - 1];
        }   
        
        result.push(line);
        index = last;
    }
    return result;  
    
};
