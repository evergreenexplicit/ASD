//myCompare
//malloc
// = null?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 100

/**
	Basic list element; stores pointer to value and pointer to the next node
*/
struct Node {
	
	void *data;
	struct Node *next;
	
};
/**
	List structure with Node and comparison counters
*/
struct MyList{
	
	struct Node *first;
	int mtf;
	int trans;
	int delete;
};
/**
	Function giving proper values to MyList structure
*/
struct MyList* initList(){
	struct MyList* list = malloc(sizeof(struct MyList));
	list->first = NULL;
	list->mtf = 0;
	list->trans = 0;
	list->delete = 0;
	
}
/**
	Function inserting new nodes at the beginning of the list
*/
void insert(struct MyList* list, void* value, size_t dataSize){
	
		struct Node *curNode;
		struct Node *newNode = malloc(sizeof(struct Node));
		curNode->next = list->first;
		//list->first = curNode;
		
		while(curNode->next != NULL)
			curNode = curNode->next;
		
		void* alloc = malloc(sizeof(dataSize));
		memcpy(alloc, value, dataSize);

		curNode->next = newNode;
		newNode->data = alloc;

	
}
/**
	Function deleting first encountered element with given value
*/
void delete(struct MyList* list, void* value,size_t dataSize){
	if(list->first == NULL)
		return;
	(list->delete)++;
	if (!memcmp(value,list->first->data,dataSize)){
		struct Node *tmpNode = list->first;
		list->first = list->first->next;
		free(tmpNode);
		return;
	}
	
	struct Node *curNode = list->first;
	while(curNode->next != NULL){
		(list->delete)++;
		if (!memcmp(value,curNode->next->data,dataSize)){
			struct Node *tmpNode = curNode->next;
			curNode->next = curNode->next->next;
			free(tmpNode);
			
			return;
		}
		curNode = curNode->next;

		
	}

}
/**
	Function searching for an element and putting it at the beginning of the list
	after having found it
*/
int findMTF(struct MyList *list,void*value,size_t dataSize){
	if(list->first == NULL)
	return 0;
	
	struct Node *curNode = list->first;
	while(curNode->next != NULL){
		(list->mtf)++;
		if (!memcmp(value,curNode->next->data,dataSize)){
			struct Node *tmpNode = curNode->next;
			curNode->next = curNode->next->next;
			tmpNode->next = list->first;
			list->first = tmpNode;
			
			return 1;
		}
		curNode = curNode->next;

		
	}
	return 0;
	
}
/**
	Function searching for an element and putting it
	one node closer to the beginning of the list
	after having found it
*/
int findTRANS(struct MyList *list,void*value,size_t dataSize){
	if(list->first == NULL || list->first->next == NULL)
		return 0;
	(list->trans)++;
	if (!memcmp(value,list->first->next->data,dataSize)){
		struct Node* tmpNode = list->first;
		struct Node* tmpNode2 = list->first->next->next;
		list->first = list->first->next;
		list->first->next = tmpNode;
		list->first->next->next = tmpNode2;
		return 1;
	}
	
	struct Node *curNode = list->first;
	while(curNode->next->next != NULL){
		(list->trans)++;
		if (!memcmp(value, curNode->next->next->data, dataSize)){
			
			struct Node* tmpNode = curNode->next;
			struct Node* tmpNode2 = curNode->next->next->next;
			curNode->next= curNode->next->next;
			curNode->next->next = tmpNode;
			curNode->next->next->next = tmpNode2;
			return 1;
		}
		curNode = curNode->next;

		
	}
	return 0;
}
/**
	Function checking whether the list contains any nodes
*/
int isEmpty(struct MyList* list){
	if(list->first == NULL)
		return 1;
	else
		return 0;
	
}
/**
	Function visualizing list in a simple way
*/
void show(struct MyList* list){

	struct Node *curNode = list->first;
	while(curNode != NULL){
		printf("%d\n",*(int *)(curNode->data));
		curNode = curNode->next;
	}
	printf("\n");
	
}
/**
	Main function is responsible for testing given exercises
*/
int main(void){
		
		
	int arr[SIZE];
	 
	for(int i = 0; i < SIZE; i++)
		arr[i] = i+1;

	srand(time(NULL));
	
	for(int i = 0; i < SIZE - 1; i++){
		int rndIdx = rand() % SIZE;
		int tmp = arr[i];
		arr[i] = arr[rndIdx];
		arr[rndIdx] = tmp;
	}	
	
	struct MyList* listMTF = initList();
	struct MyList* listTRANS = initList();

	for(int i = 0; i < SIZE; i++){
		insert(listMTF,&(arr[i]),sizeof(int));
		insert(listTRANS,&(arr[i]),sizeof(int));
		
	}
	
	for (int j = SIZE; j >= 1; j--) {
		for (int i = 1; i <= SIZE; i++) {
			findTRANS(listTRANS, &i, sizeof(int));
			findMTF(listMTF, &i, sizeof(int));
		}
		
		delete(listTRANS, &j, sizeof(int));
		delete(listMTF, &j, sizeof(int));
	}
			show(listTRANS);
			show(listMTF);
			
			
	printf("total trans: %d\ntotal mtf: %d\n",
	(listTRANS->trans)+(listTRANS->delete),(listMTF->mtf)+(listMTF->delete));
	
	/* some old testing codes
		int i = 15;
		insert(list,&i,sizeof(int));
		show(list);
		
		int j = 20;

		insert(list,&j,sizeof(int));
		show(list);
		
		int	k = 25;

		insert(list,&k,sizeof(int));
		show(list);
		
		findTRANS(list,&i,sizeof(int));
		show(list);
		
		delete(list,&i,sizeof(int));
		show(list);
	*/
}