#include "vibe-background-sequential.h"
#include "API.h"



int main(int argc, char **argv)
{
	//const int FRAME_SIZE = 1920 * 1080 * 3 / 2;
	char yuvData[1280 * 720 * 3 / 2];
	bool alarm;
	char resultMatrix[128][128]; //检测区域最大128x128
	FILE *stream, *outputFile;

	set_resolution(1280, 720);
	set_cell_split(72, 128);
	set_detection_region(0, 0, 50, 80);
	set_threshold_sensity(5, 5);

	printf("frame width: %d\n", m_width);
	printf("frame height: %d\n", m_height);
	printf("cell split row: %d, col: %d\n", m_rows, m_cols);
	printf("detection region: (%d, %d) to (%d, %d)\n", m_x1, m_y1, m_x2, m_y2);
	printf("threshold: %d%%, sensity:%d\n", m_threshold, m_sensity);

	char *testVideoName = "../data/test_1_1280X720.yuv";
	char *saveFileName = "outputFile.txt";
	stream = fopen(testVideoName, "rb+"); //确保测试时文件打开成功
	outputFile = fopen(saveFileName, "wb");
	printf("test frame: %s\n", testVideoName);
 
	for (int i = 1; i <= 100; ++i) {
		fread(yuvData, sizeof(uint8_t), sizeof(yuvData), stream);
		yuv_process(yuvData, resultMatrix, &alarm);
		
		fprintf(outputFile, "frame: "); fprintf(outputFile, "%d\n", i);
		fprintf(outputFile, "resultMatrix:\n");

		int wx = m_width / m_cols;
		int wy = m_height / m_rows;
		for (int j1 = m_y1 * wy, j2 = 0; j1 < m_y2* wy; j1 += wy, ++j2) {
			for (int k1 = m_x1*wx, k2 = 0; k1 < m_x2*wx; k1 += wx, ++k2) {
				fprintf(outputFile, "%d ", resultMatrix[j2][k2]);
			}
			fprintf(outputFile, "\n");
		}
		fprintf(outputFile, "alarm: "); fprintf(outputFile, "%d\n", alarm);
		fprintf(outputFile, "\n");
	}

	printf("the result is in file: %s\n", saveFileName);
	fprintf(stderr, "\n");
	return(0);
}
