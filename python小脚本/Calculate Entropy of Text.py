# https://www.hdm-stuttgart.de/~maucher/Python/MMCodecs/html/basicFunctions.html
import numpy as np
text="""In agreeing to settle a case brought by 38 states involving the project, the search company for the first time is required to aggressively police its own employees on privacy issues and to explicitly tell the public how to fend off privacy violations like this one."""
chars = list(text)
length = len(chars)
print ("Number of characters in text string: %d"%(length))
dec=[ord(c) for c in chars]
print(dec)
decset = set(dec)
print(decset)

freqdic={}
for c in decset:
        freqdic[c]=dec.count(c)

print ("\nAscii \t Char \t Count \t inform.")
Entropy=0
for c in decset:
        prop = freqdic[c]/(1.0*length) #propability of character
        informationContent = np.log2(1.0/prop) #infromation content of character
        Entropy += prop*informationContent
        print ("%5d \t %5s \t %5d \t %2.2f" % (c, chr(c), freqdic[c], informationContent))

print("\nEntropy of text: %2.2f" % (Entropy))