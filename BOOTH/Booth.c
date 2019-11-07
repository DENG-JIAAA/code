#include <stdio.h>
#include <stdlib.h>

/* 存储被乘数 x 的补码 */
char xCom[20] = { 0 };

/* 存储 -x 的补码 */
char mxCom[20] = { 0 };

/* 存储乘数 y 的补码 */
char yCom[20] = { 0 };

/* 存储乘数 y 末位增加 0 */
char multiNum[20] = { 0 };

/* 存储部分积的初值 */
char multiSrc[20] = { 0 };

/* 计算字符串长度 */
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

/* 拷贝字符串 */
char* copy(char* dest, const char* src)
{
	char* tmp = dest;
	while (*dest++ = *src++) {}
	return tmp;
}

/* 字符串比较 */
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

/* 字符串截取：截取从src中的begin下标到end下标的字符串，结果存储在res中 */
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

/* 右移 */
void mRight(char* src)
{
	int len = length(src);
	int i = len - 1;

	/* 获取小数部分的起始位置 */
	int num = 0;
	char* p = src;
	while (*p != '.')
	{
		++num;
		++p;
	}
	++num;

	/* 将小数后的第一位空出，其余全部后移 */
	for (; i >= num; --i)
	{
		src[i + 1] = src[i];
	}
	++i;

	/* 根据正负进行添1 或 添0 */
	if (src[0] == '1')
	{
		src[i] = '1';
	}
	else
	{
		src[i] = '0';
	}

}

/* 浮点数加法 */
void Add(char* lhsstr, char *rhsstr, char *result)
{
	int lhsLen = length(lhsstr);
	int rhsLen = length(rhsstr);

	/* 对长度较小的数字，在其后补0，目的是为了使两数长度相同 */
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

	/* 拿到最大的长度 */
	int i = lhsLen <= rhsLen ? rhsLen - 1 : lhsLen - 1;
	int j = i;

	/* 进位标志 */
	int flag = 0;

	while (i >= 0)
	{
		/* 小数点跳过 */
		if (lhsstr[i] == '.')
		{
			result[i] = '.';
			--i;
			continue;
		}
		/* 小数点跳过 */
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
		/* 和为2，则需要进位，存储0，更新进位标志 */
		if (sum == 2)
		{
			flag = 1;
			sum = 0;
		}
		/* 和为3，即之前有进位，且现在和为2也有进位，即11，存储1，更新进位标志 */
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

/* 原码转补码 */
void calComplement(char *origin, char *recv)
{
	/* 负数标志 */
	int isMinus = 0;
	if (origin[0] == '-')
	{
		isMinus = 1;
	}

	char* result = origin;

	/* 原码为负，补码--> 原码变反加一 */
	if (isMinus)
	{
		/* -0.1101  -> 11.xxxx */
		*origin++ = '1';
		*origin++ = '1';

		/* 小数位全部变反 */
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

		/* 加一操作：构造和操作数长度相同的加数，即 11.xxxx + 00.0001 */
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

	/* 原码为正，补码不改变，但在这里给补码前补0，即 0.1011 --> 00.1011 */
	int len = length(origin);
	for (int i = len - 1; i >= 0; --i)
	{
		origin[i + 1] = origin[i];
	}
	origin[0] = '0';
	copy(recv, origin);
}

/* 补码转原码：最后的结果转换 */
void calOri(char* origin, char* recv)
{
	/* 负数标志 */
	int isMinus = 0;
	if (origin[0] == '1')
	{
		isMinus = 1;
	}

	char* result = origin;

	/* 补码的符号位为负 */
	if (isMinus)
	{
		/*
		multiRes : 11.01110001
		X * Y COM : 1.01110001
		X * Y : -0.10001111
		*/

		/*
		** 11.XXXXX --> -0.XXXXX（通过multiRes补码
		** 转换，因为11恰好可用-0，都是两位，直接替换）
		*/
		*origin++ = '-';
		*origin++ = '0';

		/* 按位取反 */
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

		/* 加一操作 */
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

	/* 补码符号位为正，即原码和补码相同 */
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

/* booth算法核心实现 */
void Calculate()
{
	int i = 0;
	char index[20] = { 0 };

	/* 拿到末尾添0的乘数副本 */
	copy(index, multiNum);

	/* 计算小数部分起始位置 */
	int num = 0;
	while (index[i] != '.')
	{
		++num;
		++i;
	}

	/* 去掉index的小数点，便于之后进行移位分割 */
	char res[20] = { 0 };
	int len = length(index);
	for (i = num; i < len - 1; ++i)
	{
		index[i] = index[i + 1];
	}
	index[i] = '\0';


	i = length(index) - 1;

	/* 首次计算标志，因为首次计算是与部分积初值的计算 */
	int first = 1;

	/* 存储部分积 */
	char multiRes[20] = { 0 };

	while (i - 1 >= 0)
	{
		/* 移位分割，从低位向高位分割，分割首末位置每次同时向高位移动一位 */
		intercept(index, res, i - 1, i);

		/* 首次是与初值的运算 */
		if (first)
		{
			first = 0;
			if (compare(res, "00") == 0)
			{
				/* 00 --> 初值右移一位 */
				mRight(multiSrc);
			}
			else if (compare(res, "01") == 0)
			{
				/* 01 --> 初值加[x]补，并右移一位 */
				Add(multiSrc, xCom, multiRes);
				mRight(multiRes);
			}
			else if (compare(res, "10") == 0)
			{
				/* 10 --> 初值加[-x]补，并右移一位 */
				Add(multiSrc, mxCom, multiRes);
				mRight(multiRes);
			}
			else if (compare(res, "11") == 0)
			{
				/* 初值右移一位 */
				mRight(multiSrc);
			}
		}
		/* 非首次都是与部分积的运算 */
		else
		{
			/* 00 --> 部分积右移一位 */
			if (compare(res, "00") == 0)
			{
				if (i - 1 > 0)
					mRight(multiRes);
			}
			else if (compare(res, "01") == 0)
			{
				/* 01 --> 部分积加[x]补，并右移一位 */
				Add(multiRes, xCom, multiRes);
				if (i - 1 >0)
					mRight(multiRes);
			}
			else if (compare(res, "10") == 0)
			{
				/* 10 --> 部分积加[-x]补，并右移一位 */
				Add(multiRes, mxCom, multiRes);
				if (i - 1 >0)
					mRight(multiRes);
			}
			else if (compare(res, "11") == 0)
			{
				/* 部分积右移一位 */
				if (i - 1 >0)
					mRight(multiRes);
			}
		}
		--i;
	}

	/* 部分积运算结果 */
	printf("部分积运算结果 : %s\n", multiRes);

	/* 拷贝运算结果，因为它会被下面计算补码时更改，但是计算原码时要用到它 */
	char Ori[20] = { 0 };
	copy(Ori, multiRes);

	/* 通过部分积得到补码 */
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
	printf("[X * Y]补 : %s\n", multiRes);

	/* 通过部分积得到原码 */
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
		
		printf("==================== 补码一位乘法 ====================\n");
		printf("******         【使用说明】           ******\n");
		printf("******  请输入正数或是负数：          ******\n");
		printf("******  第一位为‘0’来表示输入正数;  ******\n");
		printf("******  第一位为‘-’来表示输入负数。 ******\n");
		printf("******  输入'w'或'W'来重新输入。      ******\n");
		printf("******  输入'q'或'Q'来退出。          ******\n");
		printf("======================================================\n");
		printf("请输入被乘数 X : ");
		scanf("%s", inputx);
		int flag = 0; //标志：退出还是重新写入。1：退出；2：重新写入
		if (compare(inputx, "q") == 0 || compare(inputx, "Q") == 0) {
			break;
		}//输入q退出
		if (compare(inputx, "w") == 0 || compare(inputx, "W") == 0) {
			flag = 2;
			printf("\n\n");
			continue;
		}//输入w重新写入
		for (int i = 0; i < length(inputx); i++) {
			if (inputx[0] == '0') {  //正数
				if (inputx[1] == '.') {
					while (inputx[i] != '0' && inputx[i] != '1' && i > 1) {
						printf("[ERROR] 确保输入为正数，小数点后的数字是否正确？\n");
						printf("请重新输入被乘数 X : ");
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
					printf("[ERROR] 确保输入为正数，小数点的输入位置是否正确？\n");
					printf("请重新输入被乘数 X : ");
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
			else if (inputx[0] == '-') {  //负数
				if (inputx[1] == '0') {
					if (inputx[2] == '.') {
						while (inputx[i] != '0' && inputx[i] != '1' && i > 2) {
							printf("[ERROR] 确保输入为负数，小数点后的数字是否正确？\n");
							printf("请重新输入被乘数 X : ");
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
						printf("[ERROR] 确保输入为负数，小数点的输入位置是否正确？\n");
						printf("请重新输入被乘数 X : ");
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
					printf("[ERROR] 确保输入为负数，要求输入负数的绝对值要<1。\n");
					printf("请重新输入被乘数 X : ");
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
			else {  //其他
				while (inputx[0] != '-' && inputx[0] != '0') {
					printf("[ERROR] 输入正数或负数，要求输入数的绝对值要<1。\n");
					printf("请重新输入被乘数 X : ");
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

		printf("请输入乘数 Y : ");
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
						printf("[ERROR] 确保输入为正数，小数点后的数字是否正确？\n");
						printf("请重新输入乘数 Y : ");
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
					printf("[ERROR] 确保输入为正数，小数点的输入位置是否正确？\n");
					printf("请重新输入乘数 Y : ");
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
							printf("[ERROR] 确保输入为负数，小数点后的数字是否正确？\n");
							printf("请重新输入乘数 Y : ");
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
						printf("[ERROR] 确保输入为负数，小数点的输入位置是否正确？\n");
						printf("请重新输入乘数 Y : ");
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
					printf("[ERROR] 确保输入为负数，要求输入负数的绝对值要<1。\n");
					printf("请重新输入乘数 Y : ");
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
					printf("[ERROR] 输入正数或负数，要求输入数的绝对值要<1。\n");
					printf("请重新输入乘数 Y : ");
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

		// x补码
		copy(origin, inputx);
		calComplement(origin, xCom);
		printf("-----------------------------------\n");
		printf("[X]补 : %s\n", xCom);

		// -x补码
		copy(origin, inputx);
		int lenx = length(origin);
		/* 如果x本身就为负，那么直接将负号去掉即可得到-x */
		if (inputx[0] == '-')
		{
			int i = 0;
			for (; i < lenx - 1; ++i)
			{
				origin[i] = origin[i + 1];
			}
			origin[i] = '\0';
		}
		/* 如果x本身为正，那么添加负号得到-x */
		else
		{
			for (int i = lenx - 1; i >= 0; --i)
			{
				origin[i + 1] = origin[i];
			}
			origin[0] = '-';
		}
		calComplement(origin, mxCom);
		printf("[-X]补 : %s\n", mxCom);

		// y补码
		copy(origin, inputy);
		calComplement(origin, yCom);
		printf("[Y]补 : %s\n", yCom);

		// 乘数y的末尾补0
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
		printf("乘数Y的末尾补0 : %s\n", multiNum);


		// 计算部分积初值
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
		printf("部分积初值: %s\n\n", multiSrc);

		/* Booth算法 */
		Calculate();
	}
	system("pause");
	return 0;
}
