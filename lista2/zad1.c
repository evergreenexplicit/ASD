#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAXRAND 1000000

/**
	stat counters for measuring
*/
int compNum = 0;
int swapNum = 0;
/**
	global variable for sorting order;
	1 -> Ascending, 0-> Descending
*/
int sortAsc = 1;


/**
	function measuring statistics of sorting algorithms
*/
void sortMeasurement(void (*sort)(int*,int),int* keys, int number,
				int* swap, int* comp, double* time){

	clock_t execTime;				
	swapNum = 0;
	compNum = 0;
	
	execTime = clock();
	(*sort)(keys,number);
	execTime = clock() - execTime;
	
	*time = ((double)execTime)/CLOCKS_PER_SEC;
	
	
	*swap = swapNum;
	*comp = compNum;	
	
	
	
}

/**
	function showing array in terminal
*/
void show(int* keys,int number){
	for(int i = 0;i < number;i++){
		printf("%d ",keys[i]);

	}
	printf("\n");
	
}
/**
	function copying array for testing different 
	algorithms on arrays with the same values
*/
void copyArray(int* dest,int* src,int number){
	for(int i = 0;i<number;i++)
		dest[i] = src[i];
	
	
}

/**
	function swapping values in an array
*/
void swap(int* p1,int* p2){
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	swapNum++;
	
}

/**
	function comparing values
	with respect to global variable sortAsc
*/
int compare(int valA,int valB){
	compNum++;
	if(sortAsc){
		if(valA > valB)
			return 1;
		else
			return 0;
	} else{
		if(valA < valB)
			return 1;
		else
			return 0;
		
		
	}
	
	
}
/**
	function ensuring proper order after sorting
*/
int finalCheck(int *keys,int number){
	for(int i = 0;i < number-1;i++)
		if(!compare(keys[i+1],keys[i])
			&& keys[i+1] != keys[i]){
			printf("%d < %d \n",keys[i+1],keys[i]);
			return 0;
		}
		
	return 1;
	
	
}

//*************************************************
/**
	three heapsort functions
*/

int findParent(int pos){ //WARN: zly floor

	return (pos - 1) / 2;
}
int findLeftChild(int pos){
	return 2*pos + 1;	
}
int findRightChild(int pos){
	return 2*pos + 2;	
}

/**
	function for inserting value into the heapsort tree
*/

void heapStep(int* keys,int startPos, int number){
	int rootIdx = startPos;
	while(findLeftChild(rootIdx) <= number-1){ //WARN unstable
		int lChild = findLeftChild(rootIdx);
		int tmpIdx = rootIdx;
		
		
		if(compare(keys[lChild],keys[tmpIdx]))
			tmpIdx = lChild;
		if (lChild+1 <= number-1
		&& compare(keys[lChild+1],keys[tmpIdx])){
			tmpIdx = lChild+1;
		}
		if(tmpIdx == rootIdx)
			return;
		else {
			swap(&(keys[rootIdx]),&(keys[tmpIdx]));
			rootIdx = tmpIdx;
		}	
	
	}
}

/**
	function creating heap for heapsort
*/
	
void createHeap(int* keys,int number){
	int startPos = findParent(number-1);

	while (startPos >= 0){
		heapStep(keys,startPos,number);
		startPos--;
		
		
	}
	
	
}	
/**
	heapsort algorithm: creating heap,
	then switching values with the root(which becomes sorted)
	and again inserting properly value which became root
*/

void heapSort(int* keys,int number){
	createHeap(keys,number);
	for(int i = number-1;i>0;i--){
		swap(&(keys[i]),&(keys[0]));
		heapStep(keys,0,i);
	}
	
	
}


//*************************************************


/**
	selectsort algorithm: 
	looking for max/min element every iteration
*/
void selectSort(int *keys,int number){
	for(int i = 0;i < number;i++){
		int maxIdx = i;
		
		for(int j = i+1;j < number; j++)
			if(compare(keys[maxIdx],keys[j]))
				maxIdx = j;
			
			++compNum;
		if(keys[maxIdx] != keys[i]) 
			swap(&(keys[maxIdx]),&(keys[i]));
		
		
	}
	
}

//*************************************************

/**
	insertSort: 
	creating sorted subarray and iterating until
	finding proper place for the value
*/
void insertSort(int *keys,int number){
	for(int i = 1;i < number; i++){
		int tmpKey = keys[i];
		int j = i;
		
		while(j > 0 && compare(keys[j-1],tmpKey)){
			swap(&(keys[j]),&(keys[j-1]));
			j--;
		}
		keys[j] = tmpKey;
	}	
}

//*************************************************

/**
	quicksort algorithm: divide and conquer,
	iterating from top and bot side of  the array and switching
	when values are at the wrong size of a chosen pivot
	(then recursion)
*/
void quickSort(int *keys,int number){
	if(number < 2)
		return;

	int pivot = keys[0];
	int i = 0;
	int j = number - 1;
	
	while(1){
		
		while(compare(pivot,keys[i]))
			i++;
		while(compare(keys[j],pivot))
			j--;
		
			if(i >= j)
				break;
			swap(&(keys[i]),&(keys[j]));
			i++;
			j--;
	}
		quickSort(keys,j+1);
		
		quickSort(&(keys[j+1]),number-(j+1));
		
	

}
//*************************************************
/**
	modified quicksort algorithm: divide and conquer,
	iterating from top and bot side of  the array and switching
	when values are at the wrong size of a chosen pivot 
	which is a median of bottom, middle and top value,
	using insertSort in case of small arrays
*/
void mQuickSort(int* keys,int number){
	if(number < 2)
		return;
	
	if (number < 16)
		insertSort(keys,number);
	
	

	int pivot;
	if(compare(keys[0],keys[number-1])){
		if(compare(keys[number/2],keys[0])){
			pivot = keys[0];
		} else {
			if(compare(keys[number/2],keys[number-1]))
				pivot = keys[number/2];
			else
				pivot = keys[number-1];
		}
		
	} else{
		if(compare(keys[0],keys[number/2])){
			pivot = keys[0];
		} else {
			if(compare(keys[number-1],keys[number/2]))
				keys[number/2];
			else
				keys[number-1];
		}		
		
		
	}
		

	int i = 0;
	int j = number - 1;
	
	while(1){
		
		while(compare(pivot,keys[i]))
			i++;
		while(compare(keys[j],pivot))
			j--;
		
		if(i >= j)
			break;
		swap(&(keys[i]),&(keys[j]));
		i++;
		j--;
	}
		quickSort(keys,j+1);
		
		quickSort(&(keys[j+1]),number-(j+1));
		
	

	
	
	
	
	
	

}
//*************************************************
/**
	main function responsible for testing implemented algorithms:
	params:
	necessary:
	--asc / --desc => soring order
	
	--type select/insert/heap/quick => sorting type and providing values to sort
	--stat k filename  => randomly generated arrays for of size 100-10000
	repeated k times with statistics saved to a file (csv recommended)
	
*/
int main(int argc, char **argv){
	if(argc != 4)
		printf("Usage: --asc|--desc --type select|insert|heap|quick\n");
	if(!strcmp(argv[1],"--desc"))
		sortAsc = 0;
	
	if(!strcmp(argv[2],"--type")){
		int number;
		scanf("%d",&number);

		int keys[number];
		for( int i = 0;i < number;i++){
			scanf("%d",&(keys[i]));
		}
		
		printf("Number provided: %d\n",number);
		
		if(!strcmp(argv[3],"select"))
			selectSort(keys,number);
		else if(!strcmp(argv[3],"insert"))
			insertSort(keys,number);
		else if(!strcmp(argv[3],"heap"))
			heapSort(keys,number);
		else if(!strcmp(argv[3],"quick"))
			quickSort(keys,number);
		else if(!strcmp(argv[3],"mQuick"))
			mQuickSort(keys,number);
		
		
		show(keys,number);
		
	}
	else if(!strcmp(argv[2],"--stat")){
		
		int repCount = atoi(argv[3]);
		
		srand(time(NULL));
		

		int selectCompNum[100][repCount],
			selectSwapNum[100][repCount],
			insertCompNum[100][repCount],
			insertSwapNum[100][repCount],
			heapCompNum[100][repCount],
			heapSwapNum[100][repCount],
			quickCompNum[100][repCount],
			quickSwapNum[100][repCount],
			mQuickCompNum[100][repCount],
			mQuickSwapNum[100][repCount];
			
		double selectTime[100][repCount],
			   insertTime[100][repCount],
			   heapTime[100][repCount],
			   quickTime[100][repCount],
			   mQuickTime[100][repCount];
			   
			   
			   
		for(int n = 100;n <=10000;n+=100){
			int iter = (n/100)-1;
			printf("Going for iter = %d\n",iter);
			for(int k = 0; k < repCount;k++){
				
				
				int keys[n];
				for(int i = 0;i<n;i++){
					keys[i] = rand() % MAXRAND;
					
				}
				int selectKeys[n],
					insertKeys[n],
					heapKeys[n],
					quickKeys[n],
					mQuickKeys[n];
				
				copyArray(selectKeys,keys,n);
				copyArray(insertKeys,keys,n);
				copyArray(heapKeys,keys,n);
				copyArray(quickKeys,keys,n);
				copyArray(mQuickKeys,keys,n);
				
				sortMeasurement(selectSort,selectKeys,n,
					&(selectSwapNum[iter][k]),
					&(selectCompNum[iter][k]),
					&(selectTime[iter][k]));
					
				sortMeasurement(insertSort,insertKeys,n,
					&(insertSwapNum[iter][k]),
					&(insertCompNum[iter][k]),
					&(insertTime[iter][k]));
				
				sortMeasurement(heapSort,heapKeys,n,
					&(heapSwapNum[iter][k]),
					&(heapCompNum[iter][k]),
					&(heapTime[iter][k]));

				sortMeasurement(quickSort,quickKeys,n,
					&(quickSwapNum[iter][k]),
					&(quickCompNum[iter][k]),
					&(quickTime[iter][k]));
					
				sortMeasurement(mQuickSort,mQuickKeys,n,
					&(mQuickSwapNum[iter][k]),
					&(mQuickCompNum[iter][k]),
					&(mQuickTime[iter][k]));
				
				if(!finalCheck(selectKeys,n)
				|| !finalCheck(insertKeys,n)
				|| !finalCheck(heapKeys,n)
				|| !finalCheck(quickKeys,n)
				|| !finalCheck(mQuickKeys,n)){
					printf("Sorting failed");
					return 0;
				}
					
			}			
		}
		
		
		FILE *f = fopen(argv[4], "w"); 
		for(int i = 0;i < 100;i++)
			for(int j = 0; j < repCount;j++)
				fprintf(f, "select;%d;%d;%d;%lf\n", (i+1)*100,selectSwapNum[i][j],selectCompNum[i][j],selectTime[i][j]); 
			
		for(int i = 0;i < 100;i++)
			for(int j = 0; j < repCount;j++)
				fprintf(f, "insert;%d;%d;%d;%lf\n", (i+1)*100,insertSwapNum[i][j],insertCompNum[i][j],insertTime[i][j]); 
			
		for(int i = 0;i < 100;i++)
			for(int j = 0; j < repCount;j++)
				fprintf(f, "heap;%d;%d;%d;%lf\n", (i+1)*100,heapSwapNum[i][j],heapCompNum[i][j],heapTime[i][j]); 
			
		for(int i = 0;i < 100;i++)
			for(int j = 0; j < repCount;j++)
				fprintf(f, "quick;%d;%d;%d;%lf\n", (i+1)*100,quickSwapNum[i][j],quickCompNum[i][j],quickTime[i][j]); 
			
		for(int i = 0;i < 100;i++)
			for(int j = 0; j < repCount;j++)
				fprintf(f, "mQuick;%d;%d;%d;%lf\n", (i+1)*100,mQuickSwapNum[i][j],mQuickCompNum[i][j],mQuickTime[i][j]); 
		fclose(f);

		
		

		
	}
	else printf("Not matched\n");
}