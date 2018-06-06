#ifndef API_H_
#define API_H_

#include "vibe-background-sequential.h"

#ifndef __cplusplus
typedef int bool;
#define true 1
#define false 0
#endif

extern int m_width, m_height;
extern int m_rows, m_cols;
extern int m_x1, m_y1, m_x2, m_y2;
extern int m_threshold, m_sensity;

void set_resolution(int width, int height);

void set_cell_split(int row, int col);

void set_detection_region(int x1, int y1, int x2, int y2);

void set_threshold_sensity(int t, int s);

void yuv_process(const char *data,
	char result_matrix[128][128], bool *alarm);

#endif