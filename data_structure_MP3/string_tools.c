#include <stdio.h>
#include "library.h"
#include "string_tools.h"

int read_line(FILE *fp, char* str, int limit) { //단점을 모두 보완한 문자열 입력 함수
	int ch, i = 0;
	char tmp = ' ';

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) //getchar()의 반환형은 int다!! 명심
		if (i < limit - 1) {
			if (tmp != ' ' || ch != ' ') {
				str[i++] = tmp = ch;
			}
		}

	if (str[i - 1] == ' ')
		i--;

	str[i] = '\0';
	return i; //문자열 길이 반환
}

//int compose_name() {
//
//}