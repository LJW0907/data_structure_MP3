#include <stdio.h>
#include "library.h"
#include "string_tools.h"

int read_line(FILE *fp, char* str, int limit) { //������ ��� ������ ���ڿ� �Է� �Լ�
	int ch, i = 0;
	char tmp = ' ';

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) //getchar()�� ��ȯ���� int��!! ���
		if (i < limit - 1) {
			if (tmp != ' ' || ch != ' ') {
				str[i++] = tmp = ch;
			}
		}

	if (str[i - 1] == ' ')
		i--;

	str[i] = '\0';
	return i; //���ڿ� ���� ��ȯ
}

//int compose_name() {
//
//}