#include<stdio.h>
#include<string.h>
#include"linkedList.h"
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////LINKED LIST////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


struct ListNode* reverseList(struct ListNode* head)
{
	if ((head == NULL) || (head->next == NULL))
	{
		return head;
	}

	struct ListNode* prev, *tmp;
	prev= tmp = NULL;

	while (head->next != NULL)
	{
		tmp = head->next;
		head->next = prev;
		prev = head;
		head = tmp;
	}
	head->next = prev;
	return head;
}


/* Function to print entire linked list */
void printList(struct ListNode *head)
{
	struct ListNode* tmp;
	tmp = head;
	while(tmp != NULL)
	{
		printf ("[%d %d] -> ",tmp->val,tmp);
		//printf ("Deferencing node pointer: %d \n", *tmp);
		tmp = tmp->next;
	}
	printf("\n");
}

/* Function to print linked list for numOfNode */
void printList_partial(struct ListNode *head,int numOfNode)
{
	struct ListNode* tmp;
	tmp = head;
	while ((tmp != NULL) && numOfNode)
	{
		printf ("[%d %d] -> ",tmp->val,tmp);
		//printf ("Deferencing node pointer: %d \n", *tmp);
		tmp = tmp->next;
		numOfNode--;
	}
	printf("\n");
}

void printList_reverse(struct ListNode* head)
{
  if(head == NULL)
    return;

  printList_reverse(head->next);
  printf ("[%d %d] -> ",head->val,head);
}

void push(struct ListNode** head_ref, int new_data, unsigned char addToFront)
{
	struct ListNode* new_node = (struct ListNode*) malloc(sizeof(struct ListNode));

	if (addToFront) // add Front
	{
		new_node->val = new_data;
		new_node->next = *head_ref;
		*head_ref = new_node;
	}
	else //add at the back
	{
		struct ListNode* temp_head = *head_ref; //cannot use head_ref because it will be modified head_ref directly
		if (temp_head == NULL) //empty list
		{
			new_node->val = new_data;
			new_node->next = NULL;
			*head_ref = new_node;
		}
		else
		{
			while (temp_head->next != NULL)
			{
				temp_head = temp_head->next;
			}
			new_node->val = new_data;
			new_node->next = NULL;
			temp_head->next = new_node;
		}
	}
}

int pop(struct ListNode** head)
{
	int pop_value = 0;
	struct ListNode* tail = (*head);
	struct ListNode* tail_prv = (*head);
//	tail = (*head);
//	tail_prv = (*head);
	if (tail == NULL) return 0;
	while (tail->next != NULL)
	{
		tail_prv = tail;
		tail = tail->next;
	}

	if (tail == (*head))
	{
		*head = NULL;
		pop_value = tail->val;
	}
	else
	{
		tail_prv->next = NULL;
		pop_value = tail->val;
		free(tail);

	}
	return pop_value;
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n)
{
    struct ListNode *scout = head, *target = head;
    int count = 0;
    while(scout)
    {
    	printf ("Scout node value is: %d \n",scout->val);
    	printf ("Target node value is: %d \n",target->val);
    	scout = scout->next;
        if(count > n)  //the trick is scout have to be n+1 node ahead of target
        	target = target->next;
        count++;
        printf ("============ \n");
    }
    if(count > n)
    	target->next = target->next->next; // "jump over" the to-be-remove node
    else // case: remove 1 item in a list containg only 1 item
    	head = head->next;
    return head;
}

void deleteNode(struct ListNode* node_todelete)
{
    struct ListNode *temp = NULL;
    if (!node_todelete) return;
    temp = node_todelete->next;
    if (!temp) return; // cannot be solved if want to delete last node, give only access to that node
    /* the idea is not actually delete "node_todelete"
     but copy all the content of the node after node_todelete into node_todelete
     then delete that node  */
    node_todelete->val = temp->val;
    node_todelete->next = temp->next;
    free(temp);
    return;

/* also work but more cryptic
	struct ListNode* tofree = node->next;
 	*node = *(node->next);
	free(tofree);*/
}

/* Function to remove duplicates from a unsorted linked list */
void removeDuplicateNodes(struct ListNode *head)
{
	struct ListNode *ptr1, *runner, *dup;
	ptr1 = head;
	/* Pick elements one by one */
	while (ptr1 != NULL && ptr1->next != NULL )
	{
		runner = ptr1;
		/* Compare the picked element with rest of the elements
		 * note that linked list work best to look FORWARD, not backward*/
		while (runner->next != NULL ) /* cannot use runner directly: will have difficulty to delete last node */
		{
			/* If duplicate then delete it */
			if (ptr1->val == runner->next->val)
			{
				/* sequence of steps is important here */
				dup = runner->next; /* get hold of the addr to this duplicate node first, so later can delete */
				runner->next = runner->next->next;
				free(dup); /* important: prevent memory leak */
			}
			else /* advance runner */
			{
				runner = runner->next;
			}
		}
		ptr1 = ptr1->next; //advance to next node
	}
}

/* head_ref is a double pointer which points to head (or start) pointer
  of linked list */
static void reverse_linkedlist(struct ListNode** head_ref)
{
    struct ListNode* prev   = NULL;
    struct ListNode* current = *head_ref;
    struct ListNode* next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev; // At the end of while loop, the prev pointer points to the last node of original linked list.
    				  // We need to change *head_ref so that the head pointer now starts pointing to the last node
}

/* http://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.html
 * http://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.c
 * The algorithm used is Mergesort, because that works really well
 * on linked lists, without requiring the O(N) extra space it needs
 * when you do it on arrays. */

int cmp(struct ListNode *a, struct ListNode *b)
{
    return ((a->val) - (b->val));
}

/* This is the actual sort function. Notice that it returns the new
 * head of the list. (It has to, because the head will not
 * generally be the same element after the sort.) So unlike sorting
 * an array, where you can do :
 *   sort(myarray);
 * you now have to do
 *   list = listsort(mylist); */
struct ListNode *listsort(struct ListNode *list, int is_circular, int is_double)
{
	struct ListNode *p, *q, *e, *tail, *oldhead,*temp_list;
	int insize, nmerges, psize, qsize, i;

	/* Silly special case: if `list' was passed in as NULL, return
	 * NULL immediately. */
	if (!list)	{return NULL;}
	temp_list = list; /* for printf debug purpose only */
	insize = 1; /* every iteration, will double the size */

	while (1)
	{
		p = list;
		oldhead = list;	 /* only used for circular linkage */
		list = NULL;
		tail = NULL;

		nmerges = 0;  /* count number of merges we do in this pass */
		printf("insize : %d  \n",insize);
		while (p)
		{
			nmerges++;  /* there exists a merge to be done */

			/* step `insize' places along from p */
			q = p;
			psize = 0;
            /* Step q along the list by insize places,
             or until the end of the list, whichever comes first */
			for (i = 0; i < insize; i++)
			{
				psize++;
				if (is_circular)
					q = (q->next == oldhead ? NULL : q->next);
				else
					q = q->next;
				if (!q) break;
			}

			/* if q hasn't fallen off end, we have two lists to merge */
			qsize = insize;

            /* Now we need to merge a list starting at p of length psize,
             * with a list starting at q of length at most qsize.*/
			while (psize > 0 || (qsize > 0 && q))
			{
				/* decide whether next element of merge comes from p or q */
				if (psize == 0)
				{
					/* p is empty; e must come from q. */
					e = q; q = q->next; qsize--;
					if (is_circular && q == oldhead) {q = NULL;}
				}
				else if (qsize == 0 || !q)
				{
					/* q is empty; e must come from p. */
					e = p; p = p->next; psize--;
					if (is_circular && p == oldhead) {p = NULL;}
				}
				else if (cmp(p,q) <= 0)
				{
					/* First element of p is lower (or same);
					 * e must come from p. */
					e = p; p = p->next; psize--;
					if (is_circular && p == oldhead) {p = NULL;}
				}
				else
				{
					/* First element of q is lower; e must come from q. */
					e = q; q = q->next; qsize--;
					if (is_circular && q == oldhead) {q = NULL;}
				}
				printf ("e [%d %d] ",e->val,e);

				/* add the next element to the merged list */
				if (tail) /* tail hold addr of "previous" e */
				{
					tail->next = e;
				}
				else /* tail reset to NULL each iteration (of insize), thus this is first item in the sorted list */
				{
					list = e;
					printf ("list [%d %d] ",list->val,list);
				}

				if (is_double)
				{
					/* Maintain reverse pointers in a doubly linked list. */
					e->prev = tail;
				}

				tail = e; //update tail to point to e
				printf ("tail [%d %d] ",tail->val,tail);
			}

			/* now p has stepped `insize' places along, and q has too
			 * repeat */
			p = q;
		}

		if (is_circular)
		{
			tail->next = list;
			if (is_double)	{list->prev = tail;}
		}
		else
		{
			tail->next = NULL;
		}

		printf("\n");
		printf("insize: %d  ",insize);
		printList(list);

		/* If we have done only one merge, we're finished. */
		if (nmerges <= 1)   /* allow for nmerges==0, the empty list case */
		{
			return list;
		}

		/* Otherwise repeat, merging lists twice the size */
		insize *= 2;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
