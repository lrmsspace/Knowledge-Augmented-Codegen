// Source: https://leetcode.com/problems/integer-to-english-words/   |   Difficulty: Hard
//
// Problem Description:
// Convert a non-negative integer num to its English words representation.
//
// Example:
// Input: num = 123
// Output: "One Hundred Twenty Three"
//
// Constraints:
// 0 <= num <= 231 - 1
//

char* numberToWords(int num) {
    if (num == 0) return "Zero";

    const char *below_20[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                               "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen",
                               "Seventeen", "Eighteen", "Nineteen" };
    const char *tens[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
    const char *thousands[] = { "", "Thousand", "Million", "Billion" };

    char buffer[512] = {0};
    char *p = buffer;

    int chunkIndex = 0;

    while (num > 0) {
        int chunk = num % 1000;
        if (chunk > 0) {
            char chunkBuffer[128] = {0};
            char *cp = chunkBuffer;

            int hundred = chunk / 100;
            int rest = chunk % 100;

            if (hundred > 0) {
                cp += sprintf(cp, "%s Hundred ", below_20[hundred]);
            }
            if (rest >= 20) {
                int ten = rest / 10;
                int unit = rest % 10;
                cp += sprintf(cp, "%s ", tens[ten]);
                if (unit > 0) {
                    cp += sprintf(cp, "%s ", below_20[unit]);
                }
            } else if (rest > 0) {
                cp += sprintf(cp, "%s ", below_20[rest]);
            }

            if (thousands[chunkIndex][0] != '\0') {
                cp += sprintf(cp, "%s ", thousands[chunkIndex]);
            }

            // Prepend the chunkBuffer to buffer
            size_t chunkLen = strlen(chunkBuffer);
            memmove(buffer + chunkLen, buffer, p - buffer + 1); // +1 for null terminator
            memcpy(buffer, chunkBuffer, chunkLen);
            p += chunkLen;
        }
        num /= 1000;
        chunkIndex++;
    }

    // Remove trailing space
    if (p > buffer && *(p - 1) == ' ') {
        *(p - 1) = '\0';
    }
    return strdup(buffer);
      
}
