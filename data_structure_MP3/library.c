#include "library.h"

#define NUM_CHARS 256

//각 배열의 원소마다 시작 문자가 같은 artist끼리 저장된다
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

//artist 객체 생성
Artist *create_artist_instance(char *name) {
	Artist *ptr_artist = (Artist *)malloc(sizeof(Artist));

	ptr_artist->name = name;
	ptr_artist->next = NULL;
	ptr_artist->head = NULL;
	ptr_artist->tail = NULL;
	

	return ptr_artist;
}

//directory에 artist를 추가하는 함수
Artist *add_artist(char *name) {
	Artist *ptr_artist = create_artist_instance(name);

	Artist *p = artist_directory[(unsigned char)name[0]]; //name[0]로 시작되는 artist 첫 노드 주소
	Artist *q = NULL;

	//오름차순
	while (p != NULL && strcmp(p->name, name) < 0) {
		q = p;
		p = p->next;
	}
	//artist가 directory[name[0]]의 유일한 노드일 경우
	if (p == NULL && q == NULL) {
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	//artist가 첫번째 노드일 경우
	else if (q == NULL) {
		ptr_artist->next = artist_directory[(unsigned char)name[0]];
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	//일반적인 경우
	else {
		ptr_artist->next = q->next;
		q->next = ptr_artist;
	}

	return ptr_artist;
}

//Song 객체 생성
Song *create_song_instance(Artist *ptr_artist, char *title, char *path) {
	Song *ptr_song = (Song *)malloc(sizeof(Song));

	ptr_song->artist = ptr_artist;
	ptr_song->title = title;
	ptr_song->path = path;
	ptr_song->index = num_index;
	num_index++;

	return ptr_song;
}

//artist 연결리스트에 song을 추가
void add_song(char *artist, char* title, char *path) {
	//노래의 artist가 이미 directory에 있는지 찾는다
	Artist *ptr_artist = find_artist(artist);

	if (ptr_artist == NULL) {
		ptr_artist = add_artist(artist); //artist를 directory에 추가
	}

	Song *ptr_song = create_song_instance(ptr_artist, title, path);
	SNode *ptr_snode = (SNode *)malloc(sizeof(SNode));
	ptr_snode->song = ptr_song;
	ptr_snode->prev = NULL;
	ptr_snode->next = NULL;
	
	//snode를 artist에 저장
	insert_node(ptr_artist, ptr_snode);
}

void insert_node(Artist *ptr_artist, SNode *ptr_snode) {
	SNode *p = ptr_artist->head;
	while (p != NULL && strcmp(p->song->title, ptr_snode->song->title) < 0) 
		p = p->next;

	//add ptr_snode before p
	//1. empty
	//2. 맨 처음
	//3. 맨 끝
	//4. 일반적
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
	Artist *p = artist_directory[(unsigned char)name[0]]; //Artist의 첫 문자(name[0])를 통한 비교
	//첫문자가 같은 artist 그룹이 존재한다면 그곳에서 name 이름을 가진 artist를 찾는다
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