/*
 * Dictionary.c
 *
 *  Created on: Apr 3, 2016
 *      Author: Dennis Chau
 */

#include<stdio.h>
#include<string.h>
#include "Dictionary.h"

enum BOOLEAN
{
	TRUE = 1,
	FALSE = 0,
};

//http://www.cs.yale.edu/homes/aspnes/classes/223/notes.pdf

/* dictionary initialization code used in both DictCreate and grow */
Dict internalDictCreate(int size)
{
	Dict d;
	int i;
	d = malloc(sizeof(*d));
	//assert(d != 0);
	d->size = size;
	d->n = 0;
	d->table = malloc(sizeof(struct elt *) * d->size);
	//assert(d->table != 0);
	for(i = 0; i < d->size; i++)
	{
		d->table[i] = 0;
	}
	return d;
}

Dict DictCreate(void)
{
	return internalDictCreate(INITIAL_SIZE);
}

void DictDestroy(Dict d)
{
	printf("DictDestroy");
	int i;
	struct elt *e;
	struct elt *next;
	for(i = 0; i < d->size; i++)
	{
		for(e = d->table[i]; e != NULL; e = next)
		{
			printf(" %d",i);
			next = e->next;
			free(e->key);
			free(e->value);
			free(e);
		}
	}
	free(d->table);
	free(d);
}

static unsigned long hash_function(const char *s)
{
	unsigned const char *us;
	unsigned long h;
	h = 0;
	for(us = (unsigned const char *) s; *us; us++)
	{
		h = h * MULTIPLIER + *us;
	}
	return h;
}

static void grow(Dict d)
{
	Dict d2; /* new dictionary we'll create */
	struct dict swap; /* temporary structure for brain transplant */
	int i;
	struct elt *e;
	d2 = internalDictCreate(d->size * GROWTH_FACTOR);
	for(i = 0; i < d->size; i++)
	{
		for(e = d->table[i]; e != 0; e = e->next)
		{
			/* note: this recopies everything */
			/* a more efficient implementation would
			* patch out the strdups inside DictInsert
			* to avoid this problem */
			DictInsert(d2, e->key, e->value);
		}
	}
	/* the hideous part */
	/* We'll swap the guts of d and d2 */
	/* then call DictDestroy on d2 */
	swap = *d;
	*d = *d2;
	*d2 = swap;
	DictDestroy(d2);
}

/* insert a new key-value pair into an existing dictionary */
void DictInsert(Dict d, const char *key, const char *value)
{
	struct elt *e;
	unsigned long h;
	//assert(key);
	//assert(value);
	e = malloc(sizeof(*e));
	//assert(e);
	e->key = strdup(key);
	e->value = strdup(value);
	h = hash_function(key) % (d->size);

	//collision : chaining (add in front)
	e->next = d->table[h]; //if first item, e->next == NULL; otherwise, it "push" the current list to the right and become new head of the list
	d->table[h] = e;
	d->n++;

	/* grow table if there is not enough room */
	if(d->n >= d->size * MAX_LOAD_FACTOR)
	{
		grow(d);
	}
}

/* insert a new key-value pair into an existing dictionary
 * check if no duplicate then insert to the end of list*/
enum BOOLEAN DictInsertToBackWithCheck(Dict d, const char *key, const char *value)
{
	struct elt* e ;
	struct elt* tmp;
	unsigned long h ;
	e = malloc(sizeof(*e));
	e->key = strdup(key);
	e->value = strdup(value);
	h = hash_function(key) % (d->size);
	printf("DictInsertToBackWithCheck index:%d \n",h);
	tmp = d->table[h];
	while (tmp != NULL)
	{
		if (strcmp(tmp->value,e->value) == 0) {return FALSE;}
//		if (tmp->next == NULL)
		if (0)
		{
			break;
		}
		else
		{
			tmp = tmp->next;
		}
	}

	if (tmp == NULL)
	{
		printf("idx empty \n");
		d->table[h] = e;
	}
	else
	{
		tmp->next = e;
	}
	e->next = NULL;
	d->n++;

	/* grow table if there is not enough room */
	if(d->n >= d->size * MAX_LOAD_FACTOR)
	{
		grow(d);
	}
	return TRUE;
}


/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
const char *DictSearch(Dict d, const char *key)
{
	struct elt *e;
	for(e = d->table[hash_function(key) % d->size]; e != 0; e = e->next)
	{
		if(!strcmp(e->key, key))
		{
			/* got it */
			return e->value;
		}
	}
	return 0;
}

void DictPrint(Dict d)
{
	if (d->n == 0) {return;}
	struct elt* tmp = NULL;
	unsigned int idx = 0;

	for (idx = 0; idx < d->size; idx++)
	{
		printf ("key %d : ",idx);
		tmp = d->table[idx];
		while (tmp != NULL)
		{
			printf (" %s",tmp->value);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void DictDelete(Dict d, const char *key)
{
	struct elt **prev; /* what to change when elt is deleted */
	struct elt *e; /* what to delete */
	for(prev = &(d->table[hash_function(key) % d->size]);
		*prev != 0;
		prev = &((*prev)->next) )
	{
		if(!strcmp((*prev)->key, key))
		{
			/* got it */
			e = *prev;
			*prev = e->next;
			free(e->key);
			free(e->value);
			free(e);
			(d->n)--;
			return;
		}
	}
}
