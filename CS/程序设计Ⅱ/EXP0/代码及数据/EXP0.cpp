/*********************************************************************
Copyright: 2019-9999, Zhanghan Wang
File name: EXP0.cpp
Description:
这是一个小型英汉词典，它的功能有：
	读取：读取词条文件（格式为.dat)
	查询：查询已有词条
	添加：添加新词条
	删除：删除词条
	编辑：编辑词条
	整理：整理所有词条
Author:王章瀚	PB18111697
Version:1.0.0
Date: 2019/5/14
*********************************************************************/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#pragma warning(disable:4996)

using namespace std;
const int MAX_WORD_LEN = 32;
const int MAX_EXPLAIN_LEN = 256;
const int MAX_SENTENCE_LEN = 256;
const int MAX_LINE_LEN = MAX_WORD_LEN + MAX_EXPLAIN_LEN + MAX_SENTENCE_LEN + 5;
const int ADD_SIZE = 1;

typedef struct entry {
	bool exist;		//是否被删除
	long flocation;	//在文件中位置
	char* word;		//单词
	char* explain;	//解释
	char* sentence;	//例句
} entry;

typedef struct entryArray {
	entry** enArray;		//词条数组
	entry* lastInFile;		//文件中最后一个词条
	int startLetterIndex[26];//记录单词首字母位置的索引
	int wordsNum;			//表示可用总词条数
	int fwordsNum;			//表示文件中总词条数（包括未删除的）
	int size;				//表示词条数组enArray的大小
} entryArray;

void listHelp();
void dealCommand(entryArray* entries, char* command);
void printEntry(entry* en);
void printAllEntries(entryArray* entries, int mode);
void entryInitiate(entry* en);
int entryCompare(const entry* en1, const entry* en2);
void sortEntryArray(entryArray* entries);
void readEntries(entryArray* entries);
entry* searchEntry(entryArray* entries, char* word);
void addEntry(entryArray* entries, entry* en);
void deleteEntry(entryArray* entries, char* word);
void editEntry(entryArray* entries, char* word, char* newData, int mode);
void clear(entryArray* entries);


int main() {
	char* command = (char*)calloc(MAX_LINE_LEN,sizeof(char));
	entryArray* entries = (entryArray*)malloc(sizeof(entryArray));
	readEntries(entries);
	listHelp();
	while (true) {
		fgets(command, MAX_LINE_LEN, stdin);
		dealCommand(entries, command);
	}
}

void listHelp() {
	printf("\
小型英汉词典命令介绍:\n\
help\t\t\t列出帮助列表\n\
consult word\t\t查询单词,(用需要查询的单词代替word)\n\
add word_ex_sen	\t添加单词,(word：操作单词；ex：解释；sen：例句)\n\
del word\t\t删除单词,(word：操作单词)\n\
edit word_item_data\t编辑单词,\n\
\t\t\t\t|word：操作单词；\n\
\t\t\t\t|item：可以为w(单词),e(解释),s(例句)；\n\
\t\t\t\t|data：编辑的数据\n\
clear\t\t\t清理\t,彻底删除标记词条\n\
cls\t\t\t清屏\n\
quit\t\t\t退出\t,关闭程序\n\
");
}

/*
 *函数名： dealCommand
 *功能：处理用户命令，并执行操作
 */ 
void dealCommand(entryArray* entries, char* command) {
	command[strlen(command) - 1] = '\0';
	//处理命令 help 
	if (strstr(command, "help") - command == 0) {
		listHelp();
	}
	//处理命令 consult 
	else if (strstr(command, "consult") - command == 0) {
		if (strlen(command) <= 8) {
			printf("无效命令！\n");
			return;
		}
		LARGE_INTEGER nFreq;
		LARGE_INTEGER nBeginTime;
		LARGE_INTEGER nEndTime;
		double time;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);
		entry*en = searchEntry(entries, command + 8);
		QueryPerformanceCounter(&nEndTime);
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
		if (en == (entry*)NULL) {
			printf("找不到该单词，耗时%lf秒！\n", time);
		}
		else {
			printf("已查找到单词，耗时%lf秒！\n", time);
			printEntry(en);
		}
	}
	//处理命令 add 
	else if (strstr(command, "add") - command == 0) {
		if (strlen(command) <= 4) {
			printf("无效命令！\n");
			return;
		}
		else if (command[3] != ' ') {
			printf("无效命令！\n");
			return;
		}
		entry* en = (entry*)malloc(sizeof(entry));
		entryInitiate(en);
		char* word = (char*)calloc(MAX_WORD_LEN, sizeof(char));
		char* explain = (char*)calloc(MAX_EXPLAIN_LEN, sizeof(char));
		char* sentence = (char*)calloc(MAX_SENTENCE_LEN, sizeof(char));
		memset(word, 0, sizeof(word));
		memset(explain, 0, sizeof(word));
		memset(sentence, 0, sizeof(word));
		word = strtok(command + 4, "_");
		if ((explain = strtok(NULL, "_")) == NULL || (sentence = strtok(NULL, "_")) == NULL) {
			printf("无效命令！\n");
		}
		else {
			strcpy(en->word, word);
			strcpy(en->explain, explain);
			strcpy(en->sentence, sentence);
			addEntry(entries, en);
		}
	}
	//处理命令 del 
	else if (strstr(command, "del") - command == 0) {
		if (strlen(command) <= 4 || command[3] != ' ') {
			printf("无效命令！\n");
			return;
		}

		deleteEntry(entries, command+4);
	}
	//处理命令 edit 
	else if (strstr(command, "edit") - command == 0) {
		char* word = (char*)calloc(MAX_WORD_LEN, sizeof(char));
		char* item = (char*)calloc(MAX_EXPLAIN_LEN, sizeof(char));
		char* data = (char*)calloc(MAX_EXPLAIN_LEN, sizeof(char));
		memset(word, 0, sizeof(word));
		memset(item, 0, sizeof(word));
		memset(data, 0, sizeof(word));
		word = strtok(command + 5, "_");
		if (command[4] != ' ') {
			printf("无效命令！\n");
		}
		else if ((item = strtok(NULL, "_")) == NULL || (data = strtok(NULL, "_")) == NULL) {
			printf("无效命令！\n");
		}
		else {
			if (item[0] == 'w') {
				editEntry(entries, word, data, 0);
			}
			else if (item[0] == 'e') {
				editEntry(entries, word, data, 1);
			}
			else if (item[0] == 's') {
				editEntry(entries, word, data, 2);
			}
			else {
				printf("无效命令！\n");
			}
		}
		return;
	}
	//处理命令 clear 
	else if (strcmp(command, "clear") == 0) {
		clear(entries);
	}
	//处理命令 all0 
	else if (strcmp(command, "all0") == 0) {
		printAllEntries(entries, 0);
	}
	//处理命令 all1 
	else if (strcmp(command, "all1") == 0) {
		printAllEntries(entries, 1);
	}
	//处理命令 wordsNum 
	else if (strcmp(command, "wordsNum") == 0) {
		printf("目前有%d个单词\n", entries->wordsNum);
	}
	//处理命令 fwordsNum 
	else if (strcmp(command, "fwordsNum") == 0) {
		printf("目前有%d个单词(f)\n", entries->fwordsNum);
	}
	//处理命令 cls 
	else if (strcmp(command, "cls") == 0) {
		system("cls");
		listHelp();
	}
	//处理命令 quit 
	else if (strcmp(command, "quit") == 0) {
		exit(0);
	}
	//处理其他命令 
	else {
		printf("无效命令！\n");
		return;
	}

}


/*
 *函数名： printEntry
 *功能：打印词条en的所有内容 
 */ 
void printEntry(entry* en) {
	printf("单词:%s\n解释:%s\n例句:%s\n", en->word, en->explain, en->sentence);
}

/*
 *函数名： printAllEntries
 *功能：打印词条数组entries的所有词条
 */ 
void printAllEntries(entryArray* entries, int mode) {
	printf("\n");
	if (mode == 0) {
		for (int i = 0; i < entries->fwordsNum; i++) {
			printEntry(entries->enArray[i]);
		}
	}
	else if (mode == 1) {
		for (int i = 0; i < entries->wordsNum; i++) {
			printEntry(entries->enArray[i]);
		}
	}
	printf("\n");
}

/*
 *函数名： entryInitiate
 *功能：初始化词条en 
 */ 
void entryInitiate(entry *en) {
	en->exist = true;
	en->flocation = 0;
	en->word = (char*)calloc(MAX_WORD_LEN, sizeof(char));
	en->explain = (char*)calloc(MAX_EXPLAIN_LEN, sizeof(char));
	en->sentence = (char*)calloc(MAX_SENTENCE_LEN, sizeof(char));
	strcpy(en->word, "NULL");
	strcpy(en->explain, "NULL");
	strcpy(en->sentence, "NULL");
}

/*
 *函数名： freeEntry
 *功能：释放词条en涉及的所有内存空间 
 */ 
void freeEntry(entry* en) {
	if (en->word != (char*)NULL) { free(en->word); en->word = NULL; }
	if (en->explain != (char*)NULL) { free(en->explain); en->explain = NULL; }
	if (en->sentence != (char*)NULL) { free(en->sentence); en->sentence = NULL; }
	free(en);
}

/*
 *函数名： entryCompare
 *功能：对词条en1与en2进行比较，相当于结构体entry的一个compare函数 
 */ 
int entryCompare(const entry* en1, const entry* en2) {
	if ((en1->exist && en2->exist) || (!en1->exist && !en2->exist)) {
		return strcmp(en1->word, en2->word);
	}
	else if (en1->exist && !en2->exist) {
		return -1;
	}
	else if (en2->exist && !en1->exist) {
		return 1;
	}
	else {
		return 0;
	}
}

/*
 *函数名： sortEntryArray
 *功能：对词条entries进行排序 
 */ 
void sortEntryArray(entryArray* entries) {
	int i, j;
	bool changed;
	entry* temp;
	for (i = entries->fwordsNum - 1; i >= 0; i--) {
		changed = false;
		for (j = 0; j < i; j++) {
			if (entryCompare(entries->enArray[j], entries->enArray[j + 1]) > 0) {
				changed = true;
				temp = entries->enArray[j];
				entries->enArray[j] = entries->enArray[j + 1];
				entries->enArray[j + 1] = temp;
			}
		}
		if (!changed) {
			break;
		}
	}
}


/*
 *函数名： readEntries
 *功能：从文件中读取词条信息，保存到词条数组entries中 
 */ 
void readEntries(entryArray* entries) {
	FILE* dict = fopen("dict.dat", "r");
	fscanf(dict, "%d\n", &entries->fwordsNum);
	entries->enArray = (entry**)calloc(entries->fwordsNum + ADD_SIZE, sizeof(entry*)); //初始多设置ADD_SIZE个空间，以便添加时使用
	entries->size = entries->fwordsNum + ADD_SIZE; entries->wordsNum = 0;
	memset(entries->startLetterIndex, 0, sizeof(entries->startLetterIndex));
	entry** cur = entries->enArray;
	char exist;
	long tempLocation;
	char* curLine;
	int curLetter = 0;
	while (!feof(dict)) {
		curLine = (char*)calloc(MAX_LINE_LEN, sizeof(char));
		tempLocation = ftell(dict);
 		fgets(curLine, MAX_LINE_LEN, dict);
		if (curLine[0] == '\0') {
			break;
		}
		*cur = (entry*)malloc(sizeof(entry));
		entryInitiate(*cur);
		exist = *strtok(curLine, "_");
		(*cur)->flocation = tempLocation;
		strcpy((*cur)->word, strtok(NULL, "_"));
		strcpy((*cur)->explain, strtok(NULL, "_"));
		strcpy((*cur)->sentence, strtok(NULL, "_"));
		(*cur)->sentence[strlen((*cur)->sentence)-1] = '\0';
		//判断是否是旧词条，并做标记 
		if (exist == '#') {
			(*cur)->exist = false;
		}
		else {
			(*cur)->exist = true;
			entries->startLetterIndex[(*cur)->word[0] - 'a']++;
			entries->wordsNum++;
		}
		cur++;
	}

	for (int i = 1; i < 26; i++) {
		entries->startLetterIndex[i] += entries->startLetterIndex[i - 1];
	}
	fclose(dict);
	entries->lastInFile = entries->enArray[entries->fwordsNum-1];
	sortEntryArray(entries);
}

/*
 *函数名： searchEntry
 *功能：在词条数组entries中查找单词word 
 */ 
entry* searchEntry(entryArray* entries, char* word) {
	entry* en = (entry*)malloc(sizeof(entry));
	int comp;
	entryInitiate(en);
	strcpy(en->word, word);
	int start = 0, end = 0, middle = 0;
	end = entries->wordsNum - 1;
	//通过索引获取起始位置 
	if ((word[0] > 'a'&& word[0] <= 'z')) {
		start = entries->startLetterIndex[word[0]-'a'-1];
	}
	else if (word[0] == 'a') {
		start = 0;
	}
	end = entries->startLetterIndex[word[0]-'a'] - 1;
	//二分查找 
	while (true) {
		middle = (start + end) / 2;
		comp = entryCompare(entries->enArray[middle], en);
		if (comp > 0) {
			if (start >= end) {
				freeEntry(en);
				return (entry*)NULL;
			}
			end = middle - 1;
		}
		else if (comp < 0) {
			if (start >= end) {
				freeEntry(en);
				return (entry*)NULL;
			}
			start = middle + 1;
		}
		else if (comp == 0) {
			freeEntry(en);
			return entries->enArray[middle];
		}
	}
	freeEntry(en);
}

/*
 *函数名： addEntry
 *功能：在词条数组entries末尾添加词条en 
 */ 
void addEntry(entryArray* entries, entry* en) {
	entry* temp;
	if (en == NULL) {
		printf("增改词条失败\n");
		return;
	}
	else if ((temp = searchEntry(entries, en->word)) != (entry*)NULL) {
		printf("该词条已存在,内容如下:\n");
		printEntry(temp);
		printf("您可能需要编辑词条？输入help查看帮助.\n");
	}
	else {
		if (entries->size <= entries->fwordsNum) {
			entries->enArray = (entry**)realloc(entries->enArray, (entries->size + ADD_SIZE)*sizeof(entry*));
			entries->size += ADD_SIZE;
		}
		temp = entries->lastInFile;
		en->flocation = temp->flocation + strlen(temp->word) + strlen(temp->explain) + strlen(temp->sentence) + 6;
		entries->enArray[entries->fwordsNum] = en;
		entries->wordsNum++; entries->fwordsNum++;

		FILE* dict = fopen("dict.dat", "a+"); 
		fprintf(dict, "*_%s_%s_%s\n", en->word, en->explain, en->sentence);
		fclose(dict);
		dict = fopen("dict.dat", "r+");
		fprintf(dict, "%06d\n", entries->fwordsNum);
		fclose(dict);
		entries->lastInFile = en;
		for (int i = en->word[0] - 'a'; i < 26; i++) {
			entries->startLetterIndex[i]++;
		}
		sortEntryArray(entries);
		printf("增改词条成功\n");
	}
}

/*
 *函数名： deleteEntry
 *功能：在词条数组entries中删除单词为word的词条 
 */ 
void deleteEntry(entryArray* entries, char* word) {
	entry* toDelete = searchEntry(entries, word);
	if (toDelete == (entry*)NULL) {
		printf("删除词条\"%s\"失败，未找到该词条\n", word);
	}
	else {
		toDelete->exist = false;
		sortEntryArray(entries);
		entries->wordsNum--;

		FILE* dict = fopen("dict.dat", "r+");
		fseek(dict, toDelete->flocation, SEEK_CUR);
		fprintf(dict, "%c", '#');
		fclose(dict);
		for (int i = word[0] - 'a'; i < 26; i++) {
			entries->startLetterIndex[i]--;
		}
		printf("删除单词%s成功！\n", word);
		sortEntryArray(entries);
	}

}

/*
 *函数名： editEntry
 *功能：编辑entries中单词为word的词条，newData为新数据，根据mode决定修改它的哪一项。 
 */ 
void editEntry(entryArray* entries, char* word, char* newData, int mode) {
	entry* oldEntry = searchEntry(entries, word);
	if (oldEntry == (entry*)NULL) {
		printf("找不到该词条\n");
	}
	else if (mode == 0 && strcmp(word, newData) == 0) {
		printf("单词");
		fputs(newData, stdout);
		printf("已存在，修改失败。");
	}
	else {
		entry* newEntry = (entry*)malloc(sizeof(entry));
		entryInitiate(newEntry);
		newEntry->exist = true;
		newEntry->flocation = oldEntry->flocation;
		strcpy(newEntry->word, oldEntry->word);
		strcpy(newEntry->explain, oldEntry->explain);
		strcpy(newEntry->sentence, oldEntry->sentence);
		if (mode == 0) {
			strcpy(newEntry->word, newData);
		}
		if (mode == 1) {
			strcpy(newEntry->explain, newData);
		}
		else if (mode == 2) {
			strcpy(newEntry->sentence, newData);
		}
		oldEntry->exist = false;
		entries->wordsNum--;
		FILE* dict = fopen("dict.dat", "r+");
		fseek(dict, oldEntry->flocation, SEEK_CUR);
		fprintf(dict, "%c", '#');
		fclose(dict);
		for (int i = word[0] - 'a'; i < 26; i++) {
			entries->startLetterIndex[i]--;
		}
		addEntry(entries, newEntry);
		sortEntryArray(entries);
	}
}

/*
 *函数名： clear
 *功能：对词条数组entries做清理，同时清理文件。 
 */ 
void clear(entryArray* entries) {
	sortEntryArray(entries);
	FILE* dict = fopen("dict.dat", "w");
	fprintf(dict, "%06d\n", entries->wordsNum);
	entry* en;
	for (int i = 0; i < entries->wordsNum; i++) {
		en = entries->enArray[i];
		if (en->exist) {
			fprintf(dict, "%c", '*');
		}
		else {
			fprintf(dict, "%c", '#');
		}
		fprintf(dict, "_%s_%s_%s\n", en->word, en->explain, en->sentence);
	}
	for (int i = entries->wordsNum; i < entries->fwordsNum; i++) {
		freeEntry(entries->enArray[i]);
	}
	entries->fwordsNum = entries->wordsNum;
	entries->lastInFile = entries->enArray[entries->wordsNum - 1];
	fclose(dict);
	printf("完成清理！\n");
}
