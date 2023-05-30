#include "library.h"

#define NUM_CHARS 256

//�� �迭�� ���Ҹ��� ���� ���ڰ� ���� artist���� ����ȴ�
Artist *artist_directory[NUM_CHARS];


void init() {
	for (int i = 0; i < NUM_CHARS; i++)
		artist_directory[i] = NULL;
}

void add_song(char *artist, char* title, char *path) {
	//�뷡�� artist�� �̹� directory�� �ִ��� ã�´�
	Artist *ptr_artist = find_artist(artist);

	if (ptr_artist == NULL) {

	}
	else {

	}
}

Artist *find_artist(char *name) {
	Artist *p = artist_directory[(unsigned char)name[0]]; //Artist�� ù ����(name[0])�� ���� ��
	//ù���ڰ� ���� artist �׷��� �����Ѵٸ� �װ����� name �̸��� ���� artist�� ã�´�
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