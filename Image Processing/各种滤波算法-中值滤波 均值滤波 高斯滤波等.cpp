template <class T>
static inline T EnforceRange(const T& x, const int& MaxValue) 
{ return __min(__max(x, 0), MaxValue - 1); };

template <class T1, class T2>
void ImageProcessing::filtering(const T1* pSrcImage, T2* pDstImage,
	int width, int height, int nChannels,
	const float* pfilter2D, int fsize)
{
	float w;
	int i, j, u, v, k, ii, jj, wsize, offset;
	wsize = fsize * 2 + 1;
	float* pBuffer = new float[nChannels];
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			for (k = 0; k < nChannels; k++)
				pBuffer[k] = 0;
			for (u = -fsize; u <= fsize; u++)
				for (v = -fsize; v <= fsize; v++)
				{
					w = pfilter2D[(u + fsize)*wsize + v + fsize];
					ii = EnforceRange(i + u, height);
					jj = EnforceRange(j + v, width);
					offset = (ii*width + jj)*nChannels;
					for (k = 0; k < nChannels; k++)
						pBuffer[k] += pSrcImage[offset + k] * w;
				}
			offset = (i*width + j)*nChannels;
			for (k = 0; k < nChannels; k++)
				pDstImage[offset + k] = pBuffer[k];
		}
	delete pBuffer;
}