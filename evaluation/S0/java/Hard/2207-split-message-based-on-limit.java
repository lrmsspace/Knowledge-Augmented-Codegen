// Source: https://leetcode.com/problems/split-message-based-on-limit/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string, message, and a positive integer, limit.
//
// You must split message into one or more parts based on limit. Each resulting part should have the suffix "<a/b>", where "b" is to be replaced with the total number of parts and "a" is to be replaced with the index of the part, starting from 1 and going up to b. Additionally, the length of each resulting part (including its suffix) should be equal to limit, except for the last part whose length can be at most limit.
//
// The resulting parts should be formed such that when their suffixes are removed and they are all concatenated in order, they should be equal to message. Also, the result should contain as few parts as possible.
//
// Return the parts message would be split into as an array of strings. If it is impossible to split message as required, return an empty array.
//
// Example:
// Input: message = "this is really a very awesome message", limit = 9
// Output: ["thi<1/14>","s i<2/14>","s r<3/14>","eal<4/14>","ly <5/14>","a v<6/14>","ery<7/14>"," aw<8/14>","eso<9/14>","me<10/14>"," m<11/14>","es<12/14>","sa<13/14>","ge<14/14>"]
// Explanation:
// The first 9 parts take 3 characters each from the beginning of message.
// The next 5 parts take 2 characters each to finish splitting message. 
// In this example, each part, including the last, has length 9. 
// It can be shown it is not possible to split message into less than 14 parts.
//
// Constraints:
// 1 <= message.length <= 104
// 	message consists only of lowercase English letters and ' '.
// 	1 <= limit <= 104
//

class Solution {
    public String[] splitMessage(String message, int limit) {
        int n = message.length();
        for (int b = 1; b <= n; b++) {
            int totalSuffixLength = String.valueOf(b).length() * 2 + 3;
            int contentLimit = limit - totalSuffixLength;
            if (contentLimit <= 0) continue;

            int requiredParts = (n + contentLimit - 1) / contentLimit;
            if (requiredParts > b) continue;

            String[] result = new String[requiredParts];
            int index = 0;
            for (int a = 1; a <= requiredParts; a++) {
                int end = Math.min(index + contentLimit, n);
                String partContent = message.substring(index, end);
                String suffix = "<" + a + "/" + b + ">";
                result[a - 1] = partContent + suffix;
                index = end;
            }
            return result;
        }
        return new String[0];           
    }
}
