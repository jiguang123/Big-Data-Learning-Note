class Solution(object):
    def wordPattern(self, pattern, str):
        """
        :type pattern: str
        :type str: str
        :rtype: bool
        """
        m1 = {}
        m2 = {}
        n = len(pattern)
        words = re.split(r'\s+', str)
        if len(words) != n:
            return False
        for i in xrange(n):
            if not pattern[i] in m1:
                m1[pattern[i]] = words[i]
            elif m1[pattern[i]] != words[i]:
                return False
            if not words[i] in m2:
                m2[words[i]] = pattern[i]
            elif m2[words[i]] != pattern[i]:
                return False
        return True
        