class Solution(object):
    def getHint(self, secret, guess):
        """
        :type secret: str
        :type guess: str
        :rtype: str
        """
        n = len(secret)
        bull = cow = 0
        cs = [0] * 10
        cg = [0] * 10
        for i in xrange(n):
            if secret[i] == guess[i]:
                bull += 1
            else:
                cs[int(secret[i])] += 1
                cg[int(guess[i])] += 1
        for i in xrange(10):
            cow += min(cs[i], cg[i])
        return '%dA%dB' % (bull, cow)
        