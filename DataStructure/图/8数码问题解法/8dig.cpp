#include<iostream>
using namespace std;

int nGoalStatus;  //Ŀ��״̬
unsigned char szFlag[48427562]; //�ڵ��Ƿ���չ�ı��
char szResult[400000];   //���
char szMoves[400000]; //�ƶ����� �� u/d/r/l 
int anFather[400000]; //���ڵ�ָ��
int MyQueue[400000];  //״̬���У�״̬����362880
int nQHead; 
int nQTail;
char sz4Moves[] = "udrl";//���ֶ���
int NineToTen( char * s ) {
//�Ž����ַ���תʮ����
	int nResult = 0;
	for( int i = 0; s[i]; i ++ ) {
		nResult *= 9;
		nResult += s[i] - '0';
	}
	return nResult;
}
int GetBit( unsigned char c, int n)  {

	return ( c >> n ) & 1;

}
void SetBit( unsigned char & c, int n, int v)  {
	if( v )
		c |= (1 << n);
	else
		c &= ~(1 << n);

}
int TenToNine( int n, char * s) {
//ʮ������ת�Ž����ַ�����������ǰ��0������0��λ��
	int nZeroPos;
	int nBase = 1;
	int j = 0;
	while( nBase <= n) /*�Ӹ�λ��ʼ�Ľ���ת��*/
		nBase *= 9;
	nBase /= 9;
	do {
		s[j] = n/nBase + '0';
		if( s[j] == '0' )
			nZeroPos = j;
		j ++;
		n %= nBase;
		nBase /= 9;
	}while( nBase >= 1 );
	s[j] = 0;//��������
	//�ж��Ƿ�Ҫ��ǰ��0����ʱ��0λ��Ϊ0
	if( j < 9 ) {
		for( int i = j + 1; i > 0; i --)
			s[i] = s[i-1];
		s[0] = '0';
		return 0;
	}
	return nZeroPos;
}
int NewStatus( int nStatus, char cMove) {
//���nStatus���� cMove �ƶ���õ�����״̬�����ƶ��������򷵻�-1
	char szTmp[20];
	int nZeroPos = TenToNine(nStatus,szTmp);//���ؿո��λ��
	switch( cMove) {
		case 'u': if( nZeroPos - 3 < 0 )  return -1; //�ո��ڵ�һ��
			else {	szTmp[nZeroPos] = szTmp[nZeroPos - 3];
				szTmp[nZeroPos - 3] = '0';	}
			break;
		case 'd':	if( nZeroPos + 3 > 8 )  return -1; //�ո��ڵ�����
			else {     szTmp[nZeroPos] = szTmp[nZeroPos + 3];
				szTmp[nZeroPos + 3] = '0';	}
			break;
		case 'l':	if( nZeroPos % 3 == 0)  return -1; //�ո��ڵ�һ��
			else {	szTmp[nZeroPos] = szTmp[nZeroPos -1];
				szTmp[nZeroPos -1 ] = '0';	}
			break;
		case 'r':	if( nZeroPos % 3 == 2)  return -1; //�ո��ڵ�����
			else {	szTmp[nZeroPos] = szTmp[nZeroPos + 1];
				szTmp[nZeroPos + 1 ] = '0';	}
			break;
	}
	return NineToTen(szTmp);
}
bool Bfs(int nStatus){
	int nNewStatus;
	nQHead = 0;	nQTail = 1;
	MyQueue[nQHead] = nStatus;
	while ( nQHead != nQTail) { //���в�Ϊ��
		nStatus = MyQueue[nQHead];
		if( nStatus == nGoalStatus ) //�ҵ�Ŀ��״̬ 
			return true;
		for( int i = 0;i < 4;i ++ ) { //����4���ƶ�
			nNewStatus = NewStatus(nStatus,sz4Moves[i]);	
			if( nNewStatus == -1 ) 	continue; //�����ƣ�����һ��			
            int nByteNo = nNewStatus / 8;
			int nBitNo = nNewStatus % 8;
			if( GetBit( szFlag[nByteNo],nBitNo)) 
			       continue; //�����չ����Ѿ����ڣ��������
			SetBit( szFlag[nByteNo],nBitNo,1); //��������չ���
			MyQueue[nQTail] = nNewStatus; //�½ڵ������ 			
            anFather[nQTail] = nQHead; //��¼���ڵ�
			//��¼���ڵ����ɸ��ڵ㾭ʲô��������
			szMoves[nQTail] = sz4Moves[i]; 					
            nQTail ++;
		}
		nQHead ++; 
	}
	return false;	
}
main(){
	clock_t Start,Finish;       
	nGoalStatus = NineToTen("123456780");
	memset(szFlag,0,sizeof(szFlag));
	char szLine[50];  char szLine2[20];
	cin.getline(szLine,48);
	int i,j;
	//�������ԭʼ�ַ�����Ϊ�Ž����ַ���
	for( i = 0, j = 0; szLine[i]; i ++ ) {
		if( szLine[i] != ' ' ) {
			if( szLine[i] == 'x' )  szLine2[j++] = '0';
			else  szLine2[j++] = szLine[i];
		}
	}
	szLine2[j] = 0;
	
    Start=clock( );
    	
	if( Bfs(NineToTen(szLine2))) {
		int nMoves = 0;
		int nPos = nQHead;
		do {  //ͨ��anFather�����ҵ��ɹ���״̬���У������Ӧ����
			szResult[nMoves++] = szMoves[nPos];
			nPos = anFather[nPos]; 
		} while( nPos);
		for( int i = nMoves -1; i >= 0; i -- ) 
			cout << szResult[i];	
      	cout << endl;
	}
	else
		cout << "unsolvable" << endl;
    	
    Finish=clock( ); 
    cout<<"Time cost:"<<time <<"ms\n"<< endl;
            		
	system("pause"); 
	return 0;		
}


