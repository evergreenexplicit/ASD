//myCompare
//malloc
// = null?
#include <stdio.h>
#include <stdlib.h>


struct Node {
	
	void *data;
	struct Node *next;
	
};

struct MyList{
	
	struct Node *first;
};
struct MyList* initList(){
	struct MyList* list = malloc(sizeof(struct MyList));
	list->first = NULL;
	
}
void insert(struct MyList* list, void* value){
	if(list->first == NULL){
		list->first = malloc(sizeof(struct Node));
		list->first->next = NULL;
		list->first->data = malloc(sizeof(int));
		*(int *)(list->first->data) = *(int *)value;
		return;
	}
	struct Node *curNode = list->first;
	while(curNode->next != NULL)
		curNode = curNode->next;
	
	curNode->next = malloc(sizeof(struct Node));
	curNode->next->next = NULL;
	curNode->next->data = value;

	
}
void delete(struct MyList* list, void* value){
	if(list->first == NULL)
		return;
	
	if (* (int *) list->first->data == * (int *) value){
		struct Node *tmpNode = list->first;
		list->first = list->first->next;
		//free(list->first->data);
		free(tmpNode);
		return;
	}
	
	struct Node *curNode = list->first;
	while(curNode->next != NULL){
		if (* (int *) curNode->next->data == * (int *) value){
			struct Node *tmpNode = curNode->next;
			curNode->next = curNode->next->next;
			//free(tmpNode->data);
			free(tmpNode);
			
			return;
		}
		curNode = curNode->next;

		
	}

}

void findMTF(struct MyList *list,void*value){
	if(list->first == NULL)
	return;
	
	struct Node *curNode = list->first;
	while(curNode->next != NULL){
		if (* (int *) curNode->next->data == * (int *) value){
			struct Node *tmpNode = curNode->next;
			curNode->next = curNode->next->next;
			tmpNode->next = list->first;
			list->first = tmpNode;
			
			return;
		}
		curNode = curNode->next;

		
	}
	
}

void findTRANS(struct MyList *list,void*value){
	if(list->first == NULL)
	return;
	
	if (* (int *) list->first->next->data == * (int *) value){
		struct Node* tmpNode = list->first;
		struct Node* tmpNode2 = list->first->next->next;
		list->first = list->first->next;
		list->first->next = tmpNode;
		list->first->next->next = tmpNode2;
		return;
	}
	
	struct Node *curNode = list->first;
	while(curNode->next->next != NULL){
		if (* (int *) curNode->next->next->data == * (int *) value){
			struct Node* tmpNode = curNode->next;
			struct Node* tmpNode2 = curNode->next->next->next;
			curNode->next= curNode->next->next;
			curNode->next->next = tmpNode;
			curNode->next->next->next = tmpNode2;
			return;
		}
		curNode = curNode->next;

		
	}
	
}
void show(struct MyList* list){
	if(list->first == NULL)
		return;
		
	printf("%d\n",*(int *)(list->first->data));
	
	struct Node *curNode = list->first;
	while(curNode->next != NULL){
		printf("%d\n",*(int *)(curNode->next->data));
		curNode = curNode->next;
	}
	printf("\n");
	
}

int main(void){
	
	struct MyList* list = initList();
	
	int i = 15;
	void *p1 = (int *)&i;
	insert(list,p1);
	show(list);
	
	int j = 20;
	void *p2 = (int *)&j;
	insert(list,p2);
	show(list);
	
	int	k = 25;
	void *p3 = (int *)&k;
	insert(list,p3);
	show(list);
	
	findMTF(list,p1);
	show(list);
	
}