/*
http://blog.csdn.net/joylnwang/article/details/6769160
*/

unsigned int DroppingEggsPuzzle(unsigned int eggs, unsigned int floors)
{
	unsigned int i, j, k, t, max;

	unsigned int temp[eggs + 1][floors + 1];

	for (i = 0; i < floors + 1; ++i)
	{
		temp[0][i] = 0;
		temp[1][i] = i;
	}

	for (i = 2; i < eggs + 1; ++i)
	{
		temp[i][0] = 0;
		temp[i][1] = 1;
	}

	for (i = 2; i < eggs + 1; ++i)
	{
		for (j = 2; j < floors + 1; ++j)
		{
			for (k = 1, max = UINT_MAX; k < j; ++k)
			{
				t = temp[i][j - k] > temp[i - 1][k - 1] ? temp[i][j - k] : temp[i - 1][k - 1];

				if (max > t)
				{
					max = t;
				}
			}

			temp[i][j] = max + 1;
		}
	}

	return temp[eggs][floors];
}