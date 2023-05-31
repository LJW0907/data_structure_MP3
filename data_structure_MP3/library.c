#include "library.h"
#include "string_tools.h"

#define NUM_CHARS 256
#define SIZE_INDEX_TABLE 100
#define BUFFER_SIZE 50
//�� �迭�� ���Ҹ��� ���� ���ڰ� ���� artist���� ����ȴ�
Artist *artist_directory[NUM_CHARS];
int num_index = 0;
//play ��ɿ��� index�� �������� �����Ѵ�. �װ� ����ȭ�ϱ� ���� index_directory �迭 ����
SNode *index_directory[SIZE_INDEX_TABLE];

void insert_node(Artist *ptr_artist, SNode *ptr_snode);
void insert_to_index_directory(Song *ptr_song);
void print_artist(Artist *p);
void print_song(Song *ptr_song);
Artist *find_artist(char *name);
SNode *find_snode(Artist *ptr_artist, char *title);
SNode *find_song_id(int index);

void init() {
	for (int i = 0; i < NUM_CHARS; i++)
		artist_directory[i] = NULL;

	for (int i = 0; i < SIZE_INDEX_TABLE; i++)
		index_directory[i] = NULL;
}

void load(FILE *fp) {
	char buffer[BUFFER_SIZE];
	char *artist, *title, *path;

	while (1) {
		if (read_line(fp, buffer, BUFFER_SIZE) <= 0)
			break;

		artist = strtok(buffer, "#");
		if (!strcmp(artist, " "))
			artist = NULL;
		else
			artist = _strdup(artist);

		title = strtok(NULL, "#");
		if (!strcmp(title, " "))
			title = NULL;
		else
			title = _strdup(title);

		path = strtok(NULL, "#");
		if (!strcmp(path, " "))
			path = NULL;
		else
			path = _strdup(path);

		printf("%s %s %s\n", artist, title, path);
		add_song(artist, title, path);
	}
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

	//SNode ��ü ���� �� �ʱ�ȭ
	SNode *ptr_snode = (SNode *)malloc(sizeof(SNode));
	ptr_snode->song = ptr_song;
	ptr_snode->prev = NULL;
	ptr_snode->next = NULL;
	
	//snode�� artist�� ����
	insert_node(ptr_artist, ptr_snode);
	insert_to_index_directory(ptr_song);
}

void insert_node(Artist *ptr_artist, SNode *ptr_snode) {
	SNode *p = ptr_artist->head;
	while (p != NULL && strcmp(p->song->title, ptr_snode->song->title) < 0) 
		p = p->next;

	//add ptr_snode before p
	if (ptr_artist->head == NULL) { //1. empty
		ptr_artist->head = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else if (p == ptr_artist->head) { //2. �� ó��
		ptr_snode->next = ptr_artist->head;
		ptr_artist->head->prev = ptr_snode;
		ptr_artist->head = ptr_snode;
	}
	else if(p == NULL){ //3. �� ��
		ptr_snode->prev = ptr_artist->tail;
		ptr_artist->tail->next = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else { //4. �Ϲ���
		ptr_snode->prev = p->prev;
		ptr_snode->next = p;
		p->prev->next = ptr_snode;
		p->prev = ptr_snode;
	}
}

void insert_to_index_directory(Song *ptr_song) {
	SNode *ptr_snode = (SNode *)malloc(sizeof(SNode));
	ptr_snode->song = ptr_song;
	ptr_snode->next = NULL; 
	ptr_snode->prev = NULL; //unused

	int index = ptr_song->index % SIZE_INDEX_TABLE;

	//add the snode into single linked list index_table[index]
	SNode *p = index_directory[index];
	SNode *q = NULL;
	while (p != NULL && strcmp(p->song->title, ptr_song->title) < 0) {
		q = p;
		p = p->next;
	}
	
	if (q == NULL) {//add_first
		ptr_snode->next = p;
		index_directory[index] = ptr_snode;
 	}
	else { //add after q
		ptr_snode->next = p;
		q->next = ptr_snode;
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


void find_song(char *artist, char *title) {
	Artist *ptr_artist = find_artist(artist);

	if (ptr_artist == NULL) {
		printf("No such artist exists\n");
		return;
	}
		
	if (title == NULL) {
		printf("Found:\n");
		print_artist(ptr_artist);
	}
	else {
		SNode *ptr_snode = find_snode(ptr_artist, title);

		if (ptr_snode != NULL) {
			printf("Found:\n");
			printf("%s\n", ptr_artist->name);
			print_song(ptr_snode->song);
		}
		else {
			printf("No such song exists\n");
		}
	}
}

//ptr_artist���� title�̶�� �̸��� song�� ���� snode ã�Ƽ� ��ȯ
SNode *find_snode(Artist *ptr_artist, char *title) {
	SNode *ptr_snode = ptr_artist->head;

	while (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) < 0)
		ptr_snode = ptr_snode->next;

	if (ptr_snode != NULL && !strcmp(ptr_snode->song->title, title)) {
		return ptr_snode;
	}
	else {
		return NULL;
	}
}

SNode *find_song_id(int index) {
	SNode *ptr_snode = index_directory[index%SIZE_INDEX_TABLE];

	while (ptr_snode != NULL && ptr_snode->song->index != index)
		ptr_snode = ptr_snode->next;

	return ptr_snode;
}

void play(int index) {
	SNode *ptr_snode = find_song_id(index);
	if (ptr_snode == NULL) {
		printf("No such song exists.\n");
	}

	printf("Found the song: %s", ptr_snode->song->title);
}

//
//int remove_song() {
//
//}