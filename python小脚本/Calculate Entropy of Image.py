from PIL import Image
import numpy as np
from matplotlib import pyplot as plt

def entropy(signal):
        '''
        function returns entropy of a signal
        signal must be a 1-D numpy array
        '''
        lensig=signal.size
        symset=list(set(signal))
        numsym=len(symset)
        propab=[np.size(signal[signal==i])/(1.0*lensig) for i in symset]
        ent=np.sum([p*np.log2(1.0/p) for p in propab])
        return ent

colorIm = Image.open('_stitch_out_voronoi.png')
greyIm = colorIm.convert('L')
colorIm = np.array(colorIm)
greyIm = np.array(greyIm)

N=5
S=greyIm.shape
E=np.array(greyIm)
en = entropy(colorIm.flatten())
print('Entroy is: %f' % en)
