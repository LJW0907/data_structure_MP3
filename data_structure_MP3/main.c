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
		/*
		else if (!strcmp(command, "search"))
			handle_search();
		else if (!strcmp(command, "remove"))
			handle_remove();
		else if (!strcmp(command, "status"))
			handle_status();
		else if (!strcmp(command, "play"))
			handle_play();
		else if (!strcmp(command, "remove"))
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
























/*
#define MAX_PEOPLE 5
#define BUFFER_SIZE 50

typedef struct person {
	char* name;
	char* number;
	char* email;
	char* group;
} Person;

Person** directory;

int n;
int find_flag;
char *file_name;

int read_line(FILE *fp, char* str, int limit);
void init_directory();
void process_command();

char delim[] = "#";

int main() {
	init_directory(); //전화번호부 동적 할당 초기화
	process_command();
}




void init_directory() {
	directory = (Person**)malloc(sizeof(Person*) * MAX_PEOPLE);
	n = 0;
}

void process_command() {
	char line[BUFFER_SIZE];
	char *command, *name, *number, *email, *group;
	char empty[] = " ";

	while (1) {
		printf("$ ");

		if (read_line(stdin, line, BUFFER_SIZE) <= 0)
			continue;

		command = strtok(line, " ");

		//command
		if (!strcmp(command, "add")) { //add

			name = _strdup(strtok(NULL, "\0"));

			if (name == NULL) {
				printf("Enter name.\n");
				continue;
			}

			printf("Phone: ");
			read_line(stdin, line, BUFFER_SIZE);
			number = _strdup(line);
			if (strlen(number) == 0)
				number = empty;

			printf("Email: ");
			read_line(stdin, line, BUFFER_SIZE);
			email = _strdup(line);
			if (strlen(email) == 0)
				email = empty;

			printf("Group: ");
			read_line(stdin, line, BUFFER_SIZE);
			group = _strdup(line);
			if (strlen(group) == 0)
				group = empty;

			if (n >= MAX_PEOPLE) { //배열이 꽉 차서 재할당
				directory = (Person**)realloc(directory, sizeof(Person*) * 2 * MAX_PEOPLE);
			}

			int i = n - 1;
			//삽입 정렬
			while (i >= 0 && strcmp(directory[i]->name, name) > 0) {
				directory[i + 1] = directory[i];
				i--;
			}
			//각각의 구조체도 메모리를 할당해줘야 함. 가장 중요!!!
			directory[i + 1] = (Person*)malloc(sizeof(Person));

			//name 빼곤 strdup를 사용하지 않는다.
			//이미 위에서 strdup를 한 번 적용한 사본이기 때문에
			directory[i + 1]->name = _strdup(name);
			directory[i + 1]->number = number;
			directory[i + 1]->email = email;
			directory[i + 1]->group = group;

			n++;

			printf("%s was added successfully\n", name);
		}

		else if (!strcmp(command, "find")) {
			find_flag = 0;
			name = strtok(NULL, "\0");

			for (int i = 0; i < n; i++) {
				if (!strcmp(name, directory[i]->name)) {
					printf("%s:\n", directory[i]->name);
					printf("\tPhone: %s\n", directory[i]->number);
					printf("\tEmail: %s\n", directory[i]->email);
					printf("\tGroup: %s\n", directory[i]->group);
					find_flag = 1;
					break;
				}
			}
			if (find_flag == 0)
				printf("No person named \'%s\' exists.\n", name);
		}

		else if (!strcmp(command, "delete")) { //delete
			find_flag = 0;
			name = strtok(NULL, "\0");

			for (int i = 0; i < n; i++) {
				if (!strcmp(name, directory[i]->name)) {
					Person *p = directory[i];

					//정렬을 흐트러뜨리지 않기 위해 하나씩 전부 당긴다
					for (int j = i; j < n - 1; j++)
						directory[j] = directory[j + 1];

					//메모리 해제
					free(p->name);
					if (p->number != NULL) free(p->number);
					if (p->email != NULL) free(p->email);
					if (p->group != NULL) free(p->group);
					free(p);

					n--;
					find_flag = 1;

					printf("%s was deleted successfully.\n", name);
					break;
				}
			}
			if (find_flag == 0)
				printf("No person named \'%s\' exists.\n", name);
		}
		else if (!strcmp(command, "read")) { //read
			FILE *fp;
			file_name = strtok(NULL, "\0");

			if (file_name == NULL) {
				printf("Enter file name.\n");
			}
			else if ((fp = fopen(file_name, "r"))) {
				n = 0;

				while (!(read_line(fp, line, BUFFER_SIZE) <= 0)) {
					name = strtok(line, "#");
					number = strtok(NULL, "#");
					email = strtok(NULL, "#");
					group = strtok(NULL, "#");

					directory[n] = (Person*)malloc(sizeof(Person));

					directory[n]->name = _strdup(name);
					directory[n]->number = _strdup(number);
					directory[n]->email = _strdup(email);
					directory[n]->group = _strdup(group);

					n++;
				}
				fclose(fp);
			}
			else
				printf("Can't read directory\n");
		}
		else if (!strcmp(command, "save")) { //save
			FILE *fp;
			file_name = strtok(NULL, "\0");

			if (file_name == NULL) {
				printf("Enter save file name.\n");
			}
			else if (fp = fopen(file_name, "w")) {
				for (int i = 0; i < n; i++)
					fprintf(fp, "%s#%s#%s#%s#\n", directory[i]->name, directory[i]->number
						, directory[i]->email, directory[i]->group);

				fclose(fp);
			}
		}
		else if (!strcmp(command, "status")) { //status

			for (int i = 0; i < n; i++) {
				printf("%s:\n", directory[i]->name);
				printf("\tPhone: %s\n", directory[i]->number);
				printf("\tEmail: %s\n", directory[i]->email);
				printf("\tGroup: %s\n", directory[i]->group);
			}
			printf("Total %d person.\n", n);
		}
		else if (!strcmp(command, "exit")) { //exit
			printf("directory close");
			exit(1);
		}
		else { //잘못된 값 입력
			printf("Enter correct system\n");

			continue;

		}
	}
}

*/