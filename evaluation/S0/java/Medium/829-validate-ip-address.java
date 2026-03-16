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

class Solution {
    public String validIPAddress(String queryIP) {
        if (queryIP.chars().filter(ch -> ch == '.').count() == 3) {
            String[] parts = queryIP.split("\\.", -1);
            for (String part : parts) {
                if (part.length() == 0 || part.length() > 3) return "Neither";
                if (part.charAt(0) == '0' && part.length() != 1) return "Neither";
                for (char ch : part.toCharArray()) {
                    if (!Character.isDigit(ch)) return "Neither";
                }
                int num = Integer.parseInt(part);
                if (num < 0 || num > 255) return "Neither";
            }
            return "IPv4";
        } else if (queryIP.chars().filter(ch -> ch == ':').count() == 7) {
            String[] parts = queryIP.split(":", -1);
            for (String part : parts) {
                if (part.length() == 0 || part.length() > 4) return "Neither";
                for (char ch : part.toCharArray()) {
                    boolean isDigit = Character.isDigit(ch);
                    boolean isLowerHex = ch >= 'a' && ch <= 'f';
                    boolean isUpperHex = ch >= 'A' && ch <= 'F';
                    if (!isDigit && !isLowerHex && !isUpperHex) return "Neither";
                }
            }
            return "IPv6";
        } else {
            return "Neither";
        }           
    }
}
