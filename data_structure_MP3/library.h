#pragma warning (disable:4996)
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

//���� ���� ������ ������ ������ �Ѵ�
typedef struct song Song;
typedef struct artist Artist;
typedef struct snode SNode;

struct song { //song ����ü - �뷡 ������ ��´�
	int index;
	char *title;
	Artist *artist;
	char *path;
};
struct snode { //snode ����ü - song �ּҸ� ��� ���� ���Ḯ��Ʈ
	Song *song;
	SNode *prev, *next;
};
struct artist { //artist ����ü - ���� ������ ��� ���Ḯ��Ʈ
	char *name;
	Artist *next;
	SNode *head, *tail;
};

void init();
void add_song(char *artist, char *title, char *path);
void find_song(char *artist, char *title);
void play(int id_str);
void status();
void load(FILE *fp);
void save(FILE *fp);

//void initialize();
//void search_song(char *name);
//void search_song(char *name, char* title);
//
//int remove_song(int id0);
//void play(int id);
//void status();
//void load(FILE *fp);
