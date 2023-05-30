#include "library.h"

#define NUM_CHARS 256

//각 배열의 원소마다 시작 문자가 같은 artist끼리 저장된다
Artist *artist_directory[NUM_CHARS];


void init() {
	for (int i = 0; i < NUM_CHARS; i++)
		artist_directory[i] = NULL;
}

void add_song(char *artist, char* title, char *path) {
	//노래의 artist가 이미 directory에 있는지 찾는다
	Artist *ptr_artist = find_artist(artist);

	if (ptr_artist == NULL) {

	}
	else {

	}
}

Artist *find_artist(char *name) {
	Artist *p = artist_directory[(unsigned char)name[0]]; //Artist의 첫 문자(name[0])를 통한 비교
	//첫문자가 같은 artist 그룹이 존재한다면 그곳에서 name 이름을 가진 artist를 찾는다
	while (p != NULL && strcmp(p->name, name) < 0)
		p = p->next;

	if (p != NULL && strcmp(p->name, name) < 0)
		return p;
	else
		return NULL;
}
//
//void find_song() {
//
//}
//
//int remove_song() {
//
//}