// Source: https://leetcode.com/problems/sender-with-largest-word-count/   |   Difficulty: Medium
//
// Problem Description:
// You have a chat log of n messages. You are given two string arrays messages and senders where messages[i] is a message sent by senders[i].
//
// A message is list of words that are separated by a single space with no leading or trailing spaces. The word count of a sender is the total number of words sent by the sender. Note that a sender may send more than one message.
//
// Return the sender with the largest word count. If there is more than one sender with the largest word count, return the one with the lexicographically largest name.
//
// Note:
//
//
// 	Uppercase letters come before lowercase letters in lexicographical order.
// 	"Alice" and "alice" are distinct.
//
// Example:
// Input: messages = ["Hello userTwooo","Hi userThree","Wonderful day Alice","Nice day userThree"], senders = ["Alice","userTwo","userThree","Alice"]
// Output: "Alice"
// Explanation: Alice sends a total of 2 + 3 = 5 words.
// userTwo sends a total of 2 words.
// userThree sends a total of 3 words.
// Since Alice has the largest word count, we return "Alice".
//
// Constraints:
// n == messages.length == senders.length
// 	1 <= n <= 104
// 	1 <= messages[i].length <= 100
// 	1 <= senders[i].length <= 10
// 	messages[i] consists of uppercase and lowercase English letters and ' '.
// 	All the words in messages[i] are separated by a single space.
// 	messages[i] does not have leading or trailing spaces.
// 	senders[i] consists of uppercase and lowercase English letters only.
//

/**
 * @param {string[]} messages
 * @param {string[]} senders
 * @return {string}
 */
var largestWordCount = function(messages, senders) {
    const wordCountMap = new Map();

    for (let i = 0; i < messages.length; i++) {
        const wordCount = messages[i].split(' ').length;
        const sender = senders[i];
        wordCountMap.set(sender, (wordCountMap.get(sender) || 0) + wordCount);
    }

    let maxWordCount = 0;
    let resultSender = "";

    for (const [sender, count] of wordCountMap.entries()) {
        if (count > maxWordCount || (count === maxWordCount && sender > resultSender)) {
            maxWordCount = count;
            resultSender = sender;
        }
    }

    return resultSender;
};