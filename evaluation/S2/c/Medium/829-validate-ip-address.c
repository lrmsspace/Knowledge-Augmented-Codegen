// Source: https://leetcode.com/problems/validate-ip-address/   |   Difficulty: Medium
//
// Problem Description:
// Given a string queryIP, return "IPv4" if IP is a valid IPv4 address, "IPv6" if IP is a valid IPv6 address or "Neither" if IP is not a correct IP of any type.
//
// A valid IPv4 address is an IP in the form "x1.x2.x3.x4" where 0 <= xi <= 255 and xi cannot contain leading zeros. For example, "192.168.1.1" and "192.168.1.0" are valid IPv4 addresses while "192.168.01.1", "192.168.1.00", and "192.168@1.1" are invalid IPv4 addresses.
//
// A valid IPv6 address is an IP in the form "x1:x2:x3:x4:x5:x6:x7:x8" where:
//
//
// 	1 <= xi.length <= 4
// 	xi is a hexadecimal string which may contain digits, lowercase English letter ('a' to 'f') and upper-case English letters ('A' to 'F').
// 	Leading zeros are allowed in xi.
//
//
// For example, "2001:0db8:85a3:0000:0000:8a2e:0370:7334" and "2001:db8:85a3:0:0:8A2E:0370:7334" are valid IPv6 addresses, while "2001:0db8:85a3::8A2E:037j:7334" and "02001:0db8:85a3:0000:0000:8a2e:0370:7334" are invalid IPv6 addresses.
//
// Example:
// Input: queryIP = "172.16.254.1"
// Output: "IPv4"
// Explanation: This is a valid IPv4 address, return "IPv4".
//
// Constraints:
// queryIP consists only of English letters, digits and the characters '.' and ':'.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* validIPAddress(char* queryIP) {
    int i, j, len = strlen(queryIP), dotCount = 0, colonCount = 0;
    for (i = 0; i < len; i++) {
        if (queryIP[i] == '.') dotCount++;
        else if (queryIP[i] == ':') colonCount++;
    }
    
    if (dotCount == 3 && colonCount == 0) {
        char *token, *rest = queryIP;
        for (i = 0; i < 4; i++) {
            token = strtok_r(rest, ".", &rest);
            if (!token || strlen(token) > 3 || (token[0] == '0' && strlen(token) > 1)) return "Neither";
            for (j = 0; j < strlen(token); j++) {
                if (!isdigit(token[j])) return "Neither";
            }
            if (atoi(token) > 255) return "Neither";
        }
        return "IPv4";
    } else if (colonCount == 7 && dotCount == 0) {
        char *token, *rest = queryIP;
        for (i = 0; i < 8; i++) {
            token = strtok_r(rest, ":", &rest);
            if (!token || strlen(token) > 4) return "Neither";
            for (j = 0; j < strlen(token); j++) {
                if (!isxdigit(token[j])) return "Neither";
            }
        }
        return "IPv6";
    }
    
    return "Neither";       
}
