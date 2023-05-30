#include "library.h"

#define NUM_CHARS 256

//�� �迭�� ���Ҹ��� ���� ���ڰ� ���� artist���� ����ȴ�
Artist *artist_directory[NUM_CHARS];
int num_index = 0;

void insert_node(Artist *ptr_artist, SNode *ptr_snode);
void print_artist(Artist *p);
void print_song(Song *ptr_song);
Artist *find_artist(char *name);

void init() {
	for (int i = 0; i < NUM_CHARS; i++)
		artist_directory[i] = NULL;
}

//artist ��ü ����
Artist *create_artist_instance(char *name) {
	Artist *ptr_artist = (Artist *)malloc(sizeof(Artist));

	ptr_artist->name = name;
	ptr_artist->next = NULL;
	ptr_artist->head = NULL;
	ptr_artist->tail = NULL;
	

	return ptr_artist;
}

//directory�� artist�� �߰��ϴ� �Լ�
Artist *add_artist(char *name) {
	Artist *ptr_artist = create_artist_instance(name);

	Artist *p = artist_directory[(unsigned char)name[0]]; //name[0]�� ���۵Ǵ� artist ù ��� �ּ�
	Artist *q = NULL;

	//��������
	while (p != NULL && strcmp(p->name, name) < 0) {
		q = p;
		p = p->next;
	}
	//artist�� directory[name[0]]�� ������ ����� ���
	if (p == NULL && q == NULL) {
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	//artist�� ù��° ����� ���
	else if (q == NULL) {
		ptr_artist->next = artist_directory[(unsigned char)name[0]];
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	//�Ϲ����� ���
	else {
		ptr_artist->next = q->next;
		q->next = ptr_artist;
	}

	return ptr_artist;
}

//Song ��ü ����
Song *create_song_instance(Artist *ptr_artist, char *title, char *path) {
	Song *ptr_song = (Song *)malloc(sizeof(Song));

	ptr_song->artist = ptr_artist;
	ptr_song->title = title;
	ptr_song->path = path;
	ptr_song->index = num_index;
	num_index++;

	return ptr_song;
}

//artist ���Ḯ��Ʈ�� song�� �߰�
void add_song(char *artist, char* title, char *path) {
	//�뷡�� artist�� �̹� directory�� �ִ��� ã�´�
	Artist *ptr_artist = find_artist(artist);

	if (ptr_artist == NULL) {
		ptr_artist = add_artist(artist); //artist�� directory�� �߰�
	}

	Song *ptr_song = create_song_instance(ptr_artist, title, path);
	SNode *ptr_snode = (SNode *)malloc(sizeof(SNode));
	ptr_snode->song = ptr_song;
	ptr_snode->prev = NULL;
	ptr_snode->next = NULL;
	
	//snode�� artist�� ����
	insert_node(ptr_artist, ptr_snode);
}

void insert_node(Artist *ptr_artist, SNode *ptr_snode) {
	SNode *p = ptr_artist->head;
	while (p != NULL && strcmp(p->song->title, ptr_snode->song->title) < 0) 
		p = p->next;

	//add ptr_snode before p
	//1. empty
	//2. �� ó��
	//3. �� ��
	//4. �Ϲ���
	if (ptr_artist->head == NULL) { //1
		ptr_artist->head = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else if (p == ptr_artist->head) { //2
		ptr_snode->next = ptr_artist->head;
		ptr_artist->head->prev = ptr_snode;
		ptr_artist->head = ptr_snode;
	}
	else if(p == NULL){ //3
		ptr_snode->prev = ptr_artist->tail;
		ptr_artist->tail->next = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else { //4
		ptr_snode->prev = p->prev;
		ptr_snode->next = p;
		p->prev->next = ptr_snode;
		p->prev = ptr_snode;
	}
}

Artist *find_artist(char *name) {
	Artist *p = artist_directory[(unsigned char)name[0]]; //Artist�� ù ����(name[0])�� ���� ��
	//ù���ڰ� ���� artist �׷��� �����Ѵٸ� �װ����� name �̸��� ���� artist�� ã�´�
	while (p != NULL && strcmp(p->name, name) < 0)
		p = p->next;

	if (p != NULL && strcmp(p->name, name) == 0)
		return p;
	else
		return NULL;
}

void status() {
	for(int i = 0; i < NUM_CHARS; i++)
		if (artist_directory[i] != NULL) {
			Artist *p = artist_directory[i];
			while (p != NULL) {
				print_artist(p);
				p = p->next;
			}
		}
}

void print_artist(Artist *p) {
	printf("%s\n", p->name);

	SNode *ptr_snode = p->head;
	while (ptr_snode != NULL) {
		print_song(ptr_snode->song);
		ptr_snode = ptr_snode->next;
	}

}

void print_song(Song *ptr_song) {
	printf("	%d: %s, %s\n", ptr_song->index, ptr_song->title, ptr_song->path);
}

//
//void find_song() {
//
//}
//
//int remove_song() {
//
//}