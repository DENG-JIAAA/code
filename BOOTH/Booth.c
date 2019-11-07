#include <stdio.h>
#include <stdlib.h>

/* �洢������ x �Ĳ��� */
char xCom[20] = { 0 };

/* �洢 -x �Ĳ��� */
char mxCom[20] = { 0 };

/* �洢���� y �Ĳ��� */
char yCom[20] = { 0 };

/* �洢���� y ĩλ���� 0 */
char multiNum[20] = { 0 };

/* �洢���ֻ��ĳ�ֵ */
char multiSrc[20] = { 0 };

/* �����ַ������� */
int length(char* ch)
{
	int len = 0;
	while (*ch != NULL)
	{
		++len;
		++ch;
	}
	return len;
}

/* �����ַ��� */
char* copy(char* dest, const char* src)
{
	char* tmp = dest;
	while (*dest++ = *src++) {}
	return tmp;
}

/* �ַ����Ƚ� */
int compare(const char* dest, const char* src)
{
	int tmp = 0;
	while (!(tmp = *dest - *src) && *dest && *src)
	{
		dest++;
		src++;
	}
	if (tmp > 0) { return 1; }
	else if (tmp < 0) { return -1; }
	else { return 0; }
}

/* �ַ�����ȡ����ȡ��src�е�begin�±굽end�±���ַ���������洢��res�� */
char* intercept(char* src, char *res, int begin, int end)
{
	int i = begin;
	int j = 0;
	while (i <= end)
	{
		res[j] = src[i];
		++j;
		++i;
	}
	return res;
}

/* ���� */
void mRight(char* src)
{
	int len = length(src);
	int i = len - 1;

	/* ��ȡС�����ֵ���ʼλ�� */
	int num = 0;
	char* p = src;
	while (*p != '.')
	{
		++num;
		++p;
	}
	++num;

	/* ��С����ĵ�һλ�ճ�������ȫ������ */
	for (; i >= num; --i)
	{
		src[i + 1] = src[i];
	}
	++i;

	/* ��������������1 �� ��0 */
	if (src[0] == '1')
	{
		src[i] = '1';
	}
	else
	{
		src[i] = '0';
	}

}

/* �������ӷ� */
void Add(char* lhsstr, char *rhsstr, char *result)
{
	int lhsLen = length(lhsstr);
	int rhsLen = length(rhsstr);

	/* �Գ��Ƚ�С�����֣������0��Ŀ����Ϊ��ʹ����������ͬ */
	if (lhsLen < rhsLen)
	{
		int diff = rhsLen - lhsLen;
		int i = lhsLen;
		while (diff > 0)
		{
			lhsstr[i] = '0';
			--diff;
			++i;
		}
	}
	else if (lhsLen > rhsLen)
	{
		int diff = lhsLen - rhsLen;
		int i = rhsLen;
		while (diff > 0)
		{
			rhsstr[i] = '0';
			--diff;
			++i;
		}
	}

	/* �õ����ĳ��� */
	int i = lhsLen <= rhsLen ? rhsLen - 1 : lhsLen - 1;
	int j = i;

	/* ��λ��־ */
	int flag = 0;

	while (i >= 0)
	{
		/* С�������� */
		if (lhsstr[i] == '.')
		{
			result[i] = '.';
			--i;
			continue;
		}
		/* С�������� */
		if (rhsstr[j] == '.')
		{
			result[j] = '.';
			--j;
			continue;
		}

		int lhs = lhsstr[i] - '0';
		int rhs = rhsstr[j] - '0';

		int sum = lhs + rhs;

		if (flag == 1)
		{
			sum += 1;
			flag = 0;
		}
		/* ��Ϊ2������Ҫ��λ���洢0�����½�λ��־ */
		if (sum == 2)
		{
			flag = 1;
			sum = 0;
		}
		/* ��Ϊ3����֮ǰ�н�λ�������ں�Ϊ2Ҳ�н�λ����11���洢1�����½�λ��־ */
		else if (sum == 3)
		{
			flag = 1;
			sum = 1;
		}
		result[i] = sum + '0';
		--i;
		--j;
	}
}

/* ԭ��ת���� */
void calComplement(char *origin, char *recv)
{
	/* ������־ */
	int isMinus = 0;
	if (origin[0] == '-')
	{
		isMinus = 1;
	}

	char* result = origin;

	/* ԭ��Ϊ��������--> ԭ��䷴��һ */
	if (isMinus)
	{
		/* -0.1101  -> 11.xxxx */
		*origin++ = '1';
		*origin++ = '1';

		/* С��λȫ���䷴ */
		while (*origin != NULL)
		{
			if (*origin == '1')
			{
				*origin = '0';
			}
			else if (*origin == '0')
			{
				*origin = '1';
			}
			++origin;
		}

		/* ��һ����������Ͳ�����������ͬ�ļ������� 11.xxxx + 00.0001 */
		int len = length(result);
		char rhs[20] = { 0 };
		rhs[0] = '0';
		rhs[1] = '0';
		rhs[2] = '.';
		rhs[len - 1] = '1';
		for (int i = len - 2; i > 2; --i)
		{
			rhs[i] = '0';
		}

		Add(result, rhs, recv);
		return;
	}

	/* ԭ��Ϊ�������벻�ı䣬�������������ǰ��0���� 0.1011 --> 00.1011 */
	int len = length(origin);
	for (int i = len - 1; i >= 0; --i)
	{
		origin[i + 1] = origin[i];
	}
	origin[0] = '0';
	copy(recv, origin);
}

/* ����תԭ�룺���Ľ��ת�� */
void calOri(char* origin, char* recv)
{
	/* ������־ */
	int isMinus = 0;
	if (origin[0] == '1')
	{
		isMinus = 1;
	}

	char* result = origin;

	/* ����ķ���λΪ�� */
	if (isMinus)
	{
		/*
		multiRes : 11.01110001
		X * Y COM : 1.01110001
		X * Y : -0.10001111
		*/

		/*
		** 11.XXXXX --> -0.XXXXX��ͨ��multiRes����
		** ת������Ϊ11ǡ�ÿ���-0��������λ��ֱ���滻��
		*/
		*origin++ = '-';
		*origin++ = '0';

		/* ��λȡ�� */
		while (*origin != NULL)
		{
			if (*origin == '1')
			{
				*origin = '0';
			}
			else if (*origin == '0')
			{
				*origin = '1';
			}
			++origin;
		}

		/* ��һ���� */
		int len = length(result);
		char rhs[20] = { 0 };
		rhs[0] = '0';
		rhs[1] = '0';
		rhs[2] = '.';
		rhs[len - 1] = '1';
		for (int i = len - 2; i > 2; --i)
		{
			rhs[i] = '0';
		}

		Add(result, rhs, recv);
		return;
	}

	/* �������λΪ������ԭ��Ͳ�����ͬ */
	//copy(recv, origin);
	if (!isMinus) {
		int len = length(origin);
		int m = 0;
		for (; m < len - 1; ++m)
		{
			origin[m] = origin[m + 1];
		}
		origin[m] = '\0';
		copy(recv, origin);
	}
}

/* booth�㷨����ʵ�� */
void Calculate()
{
	int i = 0;
	char index[20] = { 0 };

	/* �õ�ĩβ��0�ĳ������� */
	copy(index, multiNum);

	/* ����С��������ʼλ�� */
	int num = 0;
	while (index[i] != '.')
	{
		++num;
		++i;
	}

	/* ȥ��index��С���㣬����֮�������λ�ָ� */
	char res[20] = { 0 };
	int len = length(index);
	for (i = num; i < len - 1; ++i)
	{
		index[i] = index[i + 1];
	}
	index[i] = '\0';


	i = length(index) - 1;

	/* �״μ����־����Ϊ�״μ������벿�ֻ���ֵ�ļ��� */
	int first = 1;

	/* �洢���ֻ� */
	char multiRes[20] = { 0 };

	while (i - 1 >= 0)
	{
		/* ��λ�ָ�ӵ�λ���λ�ָ�ָ���ĩλ��ÿ��ͬʱ���λ�ƶ�һλ */
		intercept(index, res, i - 1, i);

		/* �״������ֵ������ */
		if (first)
		{
			first = 0;
			if (compare(res, "00") == 0)
			{
				/* 00 --> ��ֵ����һλ */
				mRight(multiSrc);
			}
			else if (compare(res, "01") == 0)
			{
				/* 01 --> ��ֵ��[x]����������һλ */
				Add(multiSrc, xCom, multiRes);
				mRight(multiRes);
			}
			else if (compare(res, "10") == 0)
			{
				/* 10 --> ��ֵ��[-x]����������һλ */
				Add(multiSrc, mxCom, multiRes);
				mRight(multiRes);
			}
			else if (compare(res, "11") == 0)
			{
				/* ��ֵ����һλ */
				mRight(multiSrc);
			}
		}
		/* ���״ζ����벿�ֻ������� */
		else
		{
			/* 00 --> ���ֻ�����һλ */
			if (compare(res, "00") == 0)
			{
				if (i - 1 > 0)
					mRight(multiRes);
			}
			else if (compare(res, "01") == 0)
			{
				/* 01 --> ���ֻ���[x]����������һλ */
				Add(multiRes, xCom, multiRes);
				if (i - 1 >0)
					mRight(multiRes);
			}
			else if (compare(res, "10") == 0)
			{
				/* 10 --> ���ֻ���[-x]����������һλ */
				Add(multiRes, mxCom, multiRes);
				if (i - 1 >0)
					mRight(multiRes);
			}
			else if (compare(res, "11") == 0)
			{
				/* ���ֻ�����һλ */
				if (i - 1 >0)
					mRight(multiRes);
			}
		}
		--i;
	}

	/* ���ֻ������� */
	printf("���ֻ������� : %s\n", multiRes);

	/* ��������������Ϊ���ᱻ������㲹��ʱ���ģ����Ǽ���ԭ��ʱҪ�õ��� */
	char Ori[20] = { 0 };
	copy(Ori, multiRes);

	/* ͨ�����ֻ��õ����� */
	if (1)
	{
		int mlen = length(multiRes);
		i = 0;
		for (; i < mlen - 1; i++)
		{
			multiRes[i] = multiRes[i + 1];
		}
		multiRes[i] = '\0';
	}
	printf("[X * Y]�� : %s\n", multiRes);

	/* ͨ�����ֻ��õ�ԭ�� */
	char finalRes[20] = { 0 };

	calOri(Ori, finalRes);
	printf("X * Y : %s\n", finalRes);
	printf("-----------------------------------");
	printf("\n");
	printf("\n");

}

int main()
{
	while (1) {
		char inputx[20] = { 0 };
		char inputy[20] = { 0 };
		
		printf("==================== ����һλ�˷� ====================\n");
		printf("******         ��ʹ��˵����           ******\n");
		printf("******  �������������Ǹ�����          ******\n");
		printf("******  ��һλΪ��0������ʾ��������;  ******\n");
		printf("******  ��һλΪ��-������ʾ���븺���� ******\n");
		printf("******  ����'w'��'W'���������롣      ******\n");
		printf("******  ����'q'��'Q'���˳���          ******\n");
		printf("======================================================\n");
		printf("�����뱻���� X : ");
		scanf("%s", inputx);
		int flag = 0; //��־���˳���������д�롣1���˳���2������д��
		if (compare(inputx, "q") == 0 || compare(inputx, "Q") == 0) {
			break;
		}//����q�˳�
		if (compare(inputx, "w") == 0 || compare(inputx, "W") == 0) {
			flag = 2;
			printf("\n\n");
			continue;
		}//����w����д��
		for (int i = 0; i < length(inputx); i++) {
			if (inputx[0] == '0') {  //����
				if (inputx[1] == '.') {
					while (inputx[i] != '0' && inputx[i] != '1' && i > 1) {
						printf("[ERROR] ȷ������Ϊ������С�����������Ƿ���ȷ��\n");
						printf("���������뱻���� X : ");
						scanf("%s", inputx);
						i = 0;
						if (compare(inputx, "q") == 0 || compare(inputx, "Q") == 0) {
							flag = 1;
							break;
						}
						if (compare(inputx, "w") == 0 || compare(inputx, "W") == 0) {
							flag = 2;
							printf("\n\n");
							break;
						}
					}
					if (flag == 1) {
						break;
					}
					if (flag == 2) {
						continue;
					}
				}
				while (inputx[1] != '.') {
					printf("[ERROR] ȷ������Ϊ������С���������λ���Ƿ���ȷ��\n");
					printf("���������뱻���� X : ");
					scanf("%s", inputx);
					if (compare(inputx, "q") == 0 || compare(inputx, "Q") == 0) {
						flag = 1;
						break;
					}
					if (compare(inputx, "w") == 0 || compare(inputx, "W") == 0) {
						flag = 2;
						printf("\n\n");
						break;
					}
				}
				if (flag == 1) {
					break;
				}
				if (flag == 2) {
					continue;
				}
			}
			else if (inputx[0] == '-') {  //����
				if (inputx[1] == '0') {
					if (inputx[2] == '.') {
						while (inputx[i] != '0' && inputx[i] != '1' && i > 2) {
							printf("[ERROR] ȷ������Ϊ������С�����������Ƿ���ȷ��\n");
							printf("���������뱻���� X : ");
							scanf("%s", inputx);
							i = 0;
							if (compare(inputx, "q") == 0 || compare(inputx, "Q") == 0) {
								flag = 1;
								break;
							}
							if (compare(inputx, "w") == 0 || compare(inputx, "W") == 0) {
								flag = 2;
								printf("\n\n");
								break;
							}
						}
						if (flag == 1) {
							break;
						}
						if (flag == 2) {
							continue;
						}
					}
					while (inputx[2] != '.') {
						printf("[ERROR] ȷ������Ϊ������С���������λ���Ƿ���ȷ��\n");
						printf("���������뱻���� X : ");
						scanf("%s", inputx);
						if (compare(inputx, "q") == 0 || compare(inputx, "Q") == 0) {
							flag = 1;
							break;
						}
						if (compare(inputx, "w") == 0 || compare(inputx, "W") == 0) {
							flag = 2;
							printf("\n\n");
							break;
						}
					}
					if (flag == 1) {
						break;
					}
					if (flag == 2) {
						continue;
					}
				}
				while (inputx[1] != '0') {
					printf("[ERROR] ȷ������Ϊ������Ҫ�����븺���ľ���ֵҪ<1��\n");
					printf("���������뱻���� X : ");
					scanf("%s", inputx);
					if (compare(inputx, "q") == 0 || compare(inputx, "Q") == 0) {
						flag = 1;
						break;
					}
					if (compare(inputx, "w") == 0 || compare(inputx, "W") == 0) {
						flag = 2;
						printf("\n\n");
						break;
					}
				}
				if (flag == 1) {
					break;
				}
				if (flag == 2) {
					continue;
				}
			}
			else {  //����
				while (inputx[0] != '-' && inputx[0] != '0') {
					printf("[ERROR] ��������������Ҫ���������ľ���ֵҪ<1��\n");
					printf("���������뱻���� X : ");
					scanf("%s", inputx);
					if (compare(inputx, "q") == 0 || compare(inputx, "Q") == 0) {
						flag = 1;
						break;
					}
					if (compare(inputx, "w") == 0 || compare(inputx, "W") == 0) {
						flag = 2;
						printf("\n\n");
						break;
					}
				}
			}
		}
		if (flag == 1) {
			break;
		}
		if (flag == 2) {
			continue;
		}

		printf("��������� Y : ");
		scanf("%s", inputy);
		if (compare(inputy, "q") == 0 || compare(inputy, "Q") == 0) {
			break;
		}
		if (compare(inputy, "w") == 0 || compare(inputy, "W") == 0) {
			flag = 2;
			printf("\n\n");
			continue;
		}
		for (int i = 0; i < length(inputy); i++) {
			if (inputy[0] == '0') {
				if (inputy[1] == '.') {
					while (inputy[i] != '0' && inputy[i] != '1' && i > 1) {
						printf("[ERROR] ȷ������Ϊ������С�����������Ƿ���ȷ��\n");
						printf("������������� Y : ");
						scanf("%s", inputy);
						i = 0;
						if (compare(inputy, "q") == 0 || compare(inputy, "Q") == 0) {
							flag = 1;
							break;
						}
						if (compare(inputy, "w") == 0 || compare(inputy, "W") == 0) {
							flag = 2;
							printf("\n\n");
							break;
						}
					}
					if (flag == 1) {
						break;
					}
					if (flag == 2) {
						continue;
					}
				}
				while (inputy[1] != '.') {
					printf("[ERROR] ȷ������Ϊ������С���������λ���Ƿ���ȷ��\n");
					printf("������������� Y : ");
					scanf("%s", inputy);
					if (compare(inputy, "q") == 0 || compare(inputy, "Q") == 0) {
						flag = 1;
						break;
					}
					if (compare(inputy, "w") == 0 || compare(inputy, "W") == 0) {
						flag = 2;
						printf("\n\n");
						break;
					}
				}
				if (flag == 1) {
					break;
				}
				if (flag == 2) {
					continue;
				}
			}
			else if (inputy[0] == '-') {
				if (inputy[1] == '0') {
					if (inputy[2] == '.') {
						while (inputy[i] != '0' && inputy[i] != '1' && i > 2) {
							printf("[ERROR] ȷ������Ϊ������С�����������Ƿ���ȷ��\n");
							printf("������������� Y : ");
							scanf("%s", inputy);
							i = 0;
							if (compare(inputy, "q") == 0 || compare(inputy, "Q") == 0) {
								flag = 1;
								break;
							}
							if (compare(inputy, "w") == 0 || compare(inputy, "W") == 0) {
								flag = 2;
								printf("\n\n");
								break;
							}
						}
						if (flag == 1) {
							break;
						}
						if (flag == 2) {
							continue;
						}
					}
					while (inputy[2] != '.') {
						printf("[ERROR] ȷ������Ϊ������С���������λ���Ƿ���ȷ��\n");
						printf("������������� Y : ");
						scanf("%s", inputy);
						if (compare(inputy, "q") == 0 || compare(inputy, "Q") == 0) {
							flag = 1;
							break;
						}
						if (compare(inputy, "w") == 0 || compare(inputy, "W") == 0) {
							flag = 2;
							printf("\n\n");
							break;
						}
					}
					if (flag == 1) {
						break;
					}
					if (flag == 2) {
						continue;
					}
				}
				while (inputy[1] != '0') {
					printf("[ERROR] ȷ������Ϊ������Ҫ�����븺���ľ���ֵҪ<1��\n");
					printf("������������� Y : ");
					scanf("%s", inputy);
					if (compare(inputy, "q") == 0 || compare(inputy, "Q") == 0) {
						flag = 1;
						break;
					}
					if (compare(inputy, "w") == 0 || compare(inputy, "W") == 0) {
						flag = 2;
						printf("\n\n");
						break;
					}
				}
				if (flag == 1) {
					break;
				}
				if (flag == 2) {
					continue;
				}
			}
			else {
				while (inputy[0] != '-' && inputy[0] != '0') {
					printf("[ERROR] ��������������Ҫ���������ľ���ֵҪ<1��\n");
					printf("������������� Y : ");
					scanf("%s", inputy);
				}
				if (compare(inputy, "q") == 0 || compare(inputy, "Q") == 0) {
					flag = 1;
					break;
				}
				if (compare(inputy, "w") == 0 || compare(inputy, "W") == 0) {
					flag = 2;
					printf("\n\n");
					break;
				}
			}
		}
		if (flag == 1) {
			break;
		}
		if (flag == 2) {
			continue;
		}

		char origin[20] = { 0 };

		// x����
		copy(origin, inputx);
		calComplement(origin, xCom);
		printf("-----------------------------------\n");
		printf("[X]�� : %s\n", xCom);

		// -x����
		copy(origin, inputx);
		int lenx = length(origin);
		/* ���x�����Ϊ������ôֱ�ӽ�����ȥ�����ɵõ�-x */
		if (inputx[0] == '-')
		{
			int i = 0;
			for (; i < lenx - 1; ++i)
			{
				origin[i] = origin[i + 1];
			}
			origin[i] = '\0';
		}
		/* ���x����Ϊ������ô��Ӹ��ŵõ�-x */
		else
		{
			for (int i = lenx - 1; i >= 0; --i)
			{
				origin[i + 1] = origin[i];
			}
			origin[0] = '-';
		}
		calComplement(origin, mxCom);
		printf("[-X]�� : %s\n", mxCom);

		// y����
		copy(origin, inputy);
		calComplement(origin, yCom);
		printf("[Y]�� : %s\n", yCom);

		// ����y��ĩβ��0
		copy(origin, yCom);
		int leny = length(origin);
		int k = 0;
		for (; k < leny - 1; ++k)
		{
			origin[k] = origin[k + 1];
		}
		origin[k] = '0';
		origin[k + 1] = '\0';
		copy(multiNum, origin);
		printf("����Y��ĩβ��0 : %s\n", multiNum);


		// ���㲿�ֻ���ֵ
		multiSrc[0] = '0';
		multiSrc[1] = '0';
		multiSrc[2] = '.';
		int len = length(xCom) - 3;
		int i = 0;
		int j = 3;
		for (; i < len; ++i, ++j)
		{
			multiSrc[j] = '0';
		}
		printf("���ֻ���ֵ: %s\n\n", multiSrc);

		/* Booth�㷨 */
		Calculate();
	}
	system("pause");
	return 0;
}
