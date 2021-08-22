class Solution:
    def minimizeTheDifference(self, mat, target):
        v = {0}
        for line in mat:
            vn = set()
            for n in line:
                for vt in v:
                    vn.add(vt + n)
            v = vn
        mint = 1e99
        for t in v:
            mint = min(mint, abs(t - target))
        return mint
