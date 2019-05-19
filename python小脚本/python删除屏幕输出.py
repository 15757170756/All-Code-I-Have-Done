import time
s = "枝上柳绵吹又少，天涯何处无芳草"
l = len(s)
print(l)
for i in range(l):
    print("\r" + s[:l-1-i] + "|", end="")
    time.sleep(0.5)