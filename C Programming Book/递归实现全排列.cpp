#include <iostream>
#include <cstring>

using namespace::std;

/*���к���*/
/*������c     Ϊ int ������ĵ�ַ
start Ϊ�����������ʼ�±�
end   Ϊ��������Ľ����±�+1
*/
void permute(int c[], int start, int end)
{
	if (start == end) {
		for (int i = 0; i < end; ++i)
			cout << c[i] << ' ';
		cout << endl;
	}
	else {
		for (int i = start; i < end; ++i) {
			swap(c[i], c[start]);//һ����ѡn����ĸ�е�һ��
			permute(c, start + 1, end);//�ٶ������n-1����ĸһ����ѡ
			swap(c[i], c[start]);//�ָ�ԭ�ַ���
		}
	}
}

///*��ϴ���(eg:5ѡ2)*/
//int a[5] = { 1, 2, 3, 4, 5 };//ԭʼ����
//int b[2];//��ѡ�Ľ��
//const int need = 2;//��Ҫѡ��ĸ���
//void combine(int start, int end, int x)
//{
//	if (x == need)
//	{
//		//��1����ӡ��ϵ�����
//		for (int i = 0; i < need; i++)
//		{
//			cout << b[i] << " ";
//		}
//		cout << endl;
//		//��2����ÿһ����Ͻ�������
//		//permute(b,0,2);//����
//		return;
//	}
//	if ((end - start) < (need - x))//���ʣ�µ�Ԫ�ظ�������Ҫ����
//	{
//		return;
//	}
//	b[x] = a[start];//��ѡ��һ��
//	combine(start + 1, end, x + 1);//�ٴ�ʣ�µļ�����ѡ��m-1��
//	combine(start + 1, end, x);//Ȼ���ٴ�ʣ�µļ��ϣ�����С�ļ�����ѡ��m����
//
//}

int main()
{
	int a[] = { 1, 2, 3, 4 };
	int arrLength = sizeof(a) / sizeof(int);
	permute(a, 0, arrLength);

	return 0;
}