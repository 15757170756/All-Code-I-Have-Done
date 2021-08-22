class Solution:
    def isPrefixString(self, s, words):
        sum_str = ''
        for word in words:
            sum_str += word
            if sum_str == s:
                return True
        return False