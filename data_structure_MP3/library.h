#pragma warning (disable:4996)
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

//순서 문제 때문에 선언을 위에서 한다
typedef struct song Song;
typedef struct artist Artist;
typedef struct snode SNode;

struct song { //song 구조체 - 노래 정보를 담는다
	int index;
	char *title;
	Artist *artist;
	char *path;
};
struct snode { //snode 구조체 - song 주소를 담는 이중 연결리스트
	Song *song;
	SNode *prev, *next;
};
struct artist { //artist 구조체 - 가수 정보를 담는 연결리스트
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
