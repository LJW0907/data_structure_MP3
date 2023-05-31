#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "library.h"
#include "string_tools.h"

#define BUFFER_SIZE 50

void process_command();
void handle_add();
void handle_search();
void handle_play();
void handle_load();

int main() {
	init();
	handle_load();
	process_command();
}

void handle_load() {
	char buffer[BUFFER_SIZE];

	printf("Data file name? ");

	if (read_line(stdin, buffer, BUFFER_SIZE) <= 0)
		return;

	FILE *fp = fopen(buffer, "r");

	if (fp == NULL) {
		printf("No such file exists\n");
		return;
	}
		
	load(fp);

	fclose(fp);
}

void process_command() {
	char command_line[BUFFER_SIZE];
	char *command;

	while (1) {
		printf("$ ");

		if (read_line(stdin, command_line, BUFFER_SIZE) <= 0)
			continue;

		command = strtok(command_line, " ");

		if (!strcmp(command, "add"))
			handle_add();
		else if (!strcmp(command, "search"))
			handle_search();
		else if (!strcmp(command, "play"))
			handle_play();
		/*else if (!strcmp(command, "remove"))
			handle_remove();
		else if (!strcmp(command, "save"))
			handle_save();
		*/
		else if (!strcmp(command, "status"))
			status();
		else if (!strcmp(command, "exit"))
			break;
	}
}

void handle_add() {
	char buffer[BUFFER_SIZE];
	char *artist = NULL, *title = NULL, *path = NULL;

	printf("	Artist: ");

	if (read_line(stdin, buffer, BUFFER_SIZE) > 0)
		artist = _strdup(buffer);

	printf("	Title: ");

	if (read_line(stdin, buffer, BUFFER_SIZE) > 0)
		title = _strdup(buffer);

	printf("	Path: ");

	if (read_line(stdin, buffer, BUFFER_SIZE) > 0)
		path = _strdup(buffer);

	//add to the music library
	add_song(artist, title, path);
}

void handle_search() {
	char buffer[BUFFER_SIZE];
	char *artist = NULL, *title = NULL;
	//가수 이름과 노래 제목으로 검색
	printf("	Artist: ");
	if (read_line(stdin, buffer, BUFFER_SIZE) <= 0) {
		printf("	Artist name required.\n");
		return;
	}
	else {
		artist = _strdup(buffer);
	}
		
	printf("	Title: ");
	if (read_line(stdin, buffer, BUFFER_SIZE) > 0)
		title = _strdup(buffer);

	find_song(artist, title);
}

void handle_play() {
	char *id_str = strtok(NULL, " ");
	int index = atoi(id_str);

	play(index);
}