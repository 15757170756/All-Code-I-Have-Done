#include "API.h"

int m_width, m_height;
int m_rows, m_cols;
int m_x1, m_y1, m_x2, m_y2;
int m_threshold, m_sensity;
vibeModel_Sequential_t *model = NULL;
uint8_t *initImage = NULL;
uint8_t *curImage = NULL;
uint8_t *segmentation_map = NULL;
int imgSize;
int API_FRAME_SIZE;

static int idx = 0;

void set_resolution(int width, int height)
{
	m_width = width;
	m_height = height;
	imgSize = m_width*m_height;
	API_FRAME_SIZE = m_width*m_height * 3 / 2;

	model = (vibeModel_Sequential_t *)libvibeModel_Sequential_New();

	initImage = (uint8_t*)malloc(m_width * m_height);
	memset(initImage, 0, imgSize*sizeof(uint8_t));

	curImage = (uint8_t*)malloc(m_width * m_height);
	memset(curImage, 0, imgSize*sizeof(uint8_t));

	segmentation_map = (uint8_t*)malloc(m_width * m_height);
	memset(segmentation_map, 0, imgSize*sizeof(uint8_t));
}

void set_cell_split(int row, int col)
{
	m_rows = row;
	m_cols = col;
}

void set_detection_region(int x1, int y1, int x2, int y2)
{
	m_x1 = x1, m_y1 = y1;
	m_x2 = x2, m_y2 = y2;
}

void set_threshold_sensity(int t, int s)
{
	m_threshold = t;
	m_sensity = s;

	libvibeModel_Sequential_SetMatchingThreshold(model, 30 - 2 * m_sensity);
	libvibeModel_Sequential_SetMatchingNumber(model, 3);
}

void yuv_process(const char *data,
	char result_matrix[128][128], bool *alarm)
{
	int equal1 = 0, equal0 = 0;

	int wx = m_width / m_cols;
	int wy = m_height / m_rows;

	if (idx == 0) {
		libvibeModel_Sequential_AllocInit_8u_C1R(model, (uint8_t*)data, m_width, m_height);
		++idx;
		memcpy(initImage, (uint8_t*)data, m_width*m_height);
		for (int i1 = m_y1 * wy, i2 = 0; i1 < m_y2 * wy; i1 += wy, ++i2) {
			for (int j1 = m_x1 * wx, j2 = 0; j1 < m_x2 * wx; j1 += wx, ++j2) {
				result_matrix[i2][j2] = 0;
			}
		}
		*alarm = false;
		return;
	}

	for (int j = 0; j < imgSize; ++j)
		curImage[j] = (uint8_t)data[j];

	libvibeModel_Sequential_Segmentation_8u_C1R(model, curImage, segmentation_map);
	libvibeModel_Sequential_Update_8u_C1R(model, curImage, segmentation_map);

	if (idx == 1 || idx == 2) {
		for (int j = 0; j < imgSize; ++j)
			initImage[j] = segmentation_map[j];
		++idx;

		for (int i1 = m_y1 * wy, i2 = 0; i1 < m_y2 * wy; i1 += wy, ++i2) {
			for (int j1 = m_x1 * wx, j2 = 0; j1 < m_x2 * wx; j1 += wx, ++j2) {
				result_matrix[i2][j2] = 0;
			}
		}
		*alarm = false;
		return;
	}

	for (int j = 0; j < imgSize; ++j) 
		segmentation_map[j] = segmentation_map[j] - initImage[j];
	

	for (int i1 = m_y1 * wy, i2 = 0; i1 < m_y2 * wy; i1 += wy, ++i2) {
		//printf("%d ", i1);
		for (int j1 = m_x1 * wx, j2 = 0; j1 < m_x2 * wx; j1 += wx, ++j2) {
			//printf("%d ", j1);
			int equal1Total = 0, equal0Total = 0;
			for (int m1 = i1; m1 < i1 + wy; ++m1) {
				for (int n1 = j1; n1 < j1 + wx; ++n1) {
					if (segmentation_map[m1*m_width + n1] >= 128) {
						++equal1Total;
					}
					else {
						++equal0Total;
					}
				}
			}
			if (equal1Total > wx*wy*0.3) {
				++equal1;
				result_matrix[i2][j2] = 1;
			}
			else {
				++equal0;
				result_matrix[i2][j2] = 0;
			}
		}
	}
	int size = (m_x2 - m_x1)*(m_y2 - m_y1);
	if (equal1 >= size * m_threshold * 1.0 / 100)
		*alarm = true;
	else
		*alarm = false;
}
