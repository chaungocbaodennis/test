/*
 * Dictionary.h
 *
 *  Created on: Apr 3, 2016
 *      Author: Dennis Chau
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#define INITIAL_SIZE (8)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)
#define MULTIPLIER (97)

struct elt
{
	struct elt *next;
	char *key;
	char *value;
};

struct dict
{
	int size; /* size of the pointer table */
	int n; /* number of elements storED */
	struct elt **table; /* dynamic array of pointer to struct elt because we don't know size until runtime*/
};
typedef struct dict *Dict;

/* create a new empty dictionary */
Dict DictCreate(void);
/* destroy a dictionary */
void DictDestroy(Dict);
/* insert a new key-value pair into an existing dictionary */
void DictInsert(Dict, const char *key, const char *value);
/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
const char *DictSearch(Dict, const char *key);
/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void DictDelete(Dict, const char *key);
void DictPrint(Dict d);
/* insert a new key-value pair into an existing dictionary
 * check if no duplicate then insert to the end of list*/
enum BOOLEAN DictInsertToBackWithCheck(Dict d, const char *key, const char *value);

#endif /* DICTIONARY_H_ */
