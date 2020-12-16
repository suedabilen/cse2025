#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//node for bst 
struct wordNode{
	int freq;
	char word[20];
	struct wordNode *rightChild;
	struct wordNode *leftChild;
};
//node for binary tree
struct freqBt{
	int freq;
	char word[20];
	struct freqBt *rightChild;
	struct freqBt *leftChild;
	int rightsub;
	int leftsub;
};
//creating new word node for bst 
struct wordNode* newNode(int num,char key[]){
	struct wordNode *p;
	p = malloc(sizeof(struct wordNode));
	p->freq = num;
	strcpy(p -> word, key);
	p->rightChild = NULL;
	p->leftChild = NULL;
	return p;
}
//newnode func for frequency bt
struct freqBt* newFreqNode(int num,char key[]){
	struct freqBt *f;
	f = malloc(sizeof(struct freqBt));
	strcpy(f->word,key);
	f->freq = num;
	f->leftChild = NULL;
	f->rightChild = NULL;
	return f;
}

//to insert new bst node for part a
struct wordNode* insertBst(struct wordNode *root,int num,char key[]){
	
	if(root==NULL)
	return newNode(num,key);
	//compare words if its equal or bigger it will be the right child
	else if( strcmp(key,root->word) >= 0) 
	root->rightChild = insertBst(root->rightChild,num,key);
	//if not it will be the left child
	else
	root->leftChild = insertBst(root->leftChild,num,key);
	return root;
	
}
//insert freq bst node
struct wordNode* insertFreqBst(struct wordNode *root,int num,char key[]){
	
	if(root==NULL)
		return newNode(num,key);
	
	if(num < root->freq){
		root->leftChild = insertFreqBst(root->leftChild,num,key);
	}
	else if(num >= root->freq){
		root->rightChild = insertFreqBst(root->rightChild,num,key);
	}
	return root;
}
//findmax recursive function for bst
int findMax(struct wordNode *p)
{
 	int root, left, right, max;
 	max = -1; // Assuming all values are positive integers
 		if (p != NULL) {
 			root = p -> freq;
			left = findMax(p ->leftChild);
 			right = findMax(p->rightChild);
 		// Find the largest of the three values.
		if (left > right)
 			max = left;
		 
		else
 		max = right;
 		if (root > max)
		 	max = root;
 		}
 return max;
}
//finds depth of the tree 
int depth(struct freqBt *root) {
  int d;
  while (root != NULL) {
    d++;
    root = root->leftChild;
  }
  return d;
}
//is the tree perfect?
bool perfect(struct freqBt *root, int d, int level) {
    // if the tree is empty
  if (root == NULL)
    return true;

  //if right and left is null
  if (root->leftChild == NULL && root->rightChild == NULL)
    return true;
  //if right or left is null tree is not perfect	
  if (root->leftChild != NULL && root->rightChild != NULL)
    return perfect(root->leftChild, d, level + 1) &&
       perfect(root->rightChild, d, level + 1);
  //return its perfect or not
  return false;
}


bool isPerfect(struct freqBt *root) {
  int d = depth(root);
  return perfect(root, d, 0);
}
//inserting Binary Tree
struct freqBt* insertBt(struct freqBt *root,int num,char key[]){
	if(root==NULL)
	return newFreqNode(num,key);
	
	if(root->leftsub == root->rightsub){
		root->leftChild = insertBt(root->leftChild,num,key);
		root->leftsub++;
	}
	//if there is less node in right tree
	else if(root->rightsub < root->leftsub){
		if(isPerfect(root->rightChild)){
		root->leftChild = insertBt(root->leftChild,num,key);
		root->leftsub++;
		}
		else{root->rightChild = insertBt(root->rightChild,num,key);
		root->rightsub++;
		
		
		}
	}
	//if there is less node in left subtree
	else if(root->leftsub < root->rightsub){
		if(isPerfect(root->leftChild)){
		root->rightChild = insertBt(root->rightChild,num,key);
		root->rightsub++;
		}
		else{
		root->leftChild = insertBt(root->leftChild,num,key);
		root->leftsub++;
			
	}
	
	}
	return root;	
}
//find the depth of bst node
int depthNode(struct wordNode *node, char key[], int depth) 
{   //if there is no node
    if (node == NULL) 
        return 0; 
    //the key I searched for
    if (strcmp(node->word,key) == 0) 
        return depth; 
    //look for left child
    int depthgo = depthNode(node->leftChild, key, depth+1); 
    if (depthgo != 0) 
        return depthgo; 
  
    depthgo = depthNode(node->rightChild, key, depth+1); 
    return depthgo; 
} 

//minvalue
struct wordNode* minValueNode(struct wordNode *node,int num)
{
    struct wordNode* current = node;
    while (current && current->leftChild != NULL)
        current = current->leftChild;
 
    return current;
}
//delete bst node
struct wordNode* deleteBstNode(struct wordNode *root,int num){
	if(root == NULL) 
	return root;
	
	if(num < root->freq)
		root->leftChild = deleteBstNode(root->leftChild,num);
	
	else if(num > root->freq)
		root->rightChild = deleteBstNode(root->rightChild,num);
		
	else{
		if(root->leftChild == NULL){
			struct wordNode* temp = root->rightChild;
			free(root);
			return temp;
		}
		else if(root->rightChild == NULL) {
			struct wordNode* temp = root->leftChild;
			free(root);
			return temp;
		}
		
		
		struct wordNode* temp = minValueNode(root->rightChild,num);
		root->freq = temp->freq;
		root->rightChild = deleteBstNode(root->rightChild,temp->freq);
		
	}
	return root;
}
//inorder func for binary search tree
void inorder(struct wordNode *root){
	
	if(root != NULL) {
		inorder(root->leftChild);
		printf("%s \n", root->word);
		inorder(root->rightChild);
	}
}


void inorderFreq(struct wordNode *root){
	
	if(root != NULL) {
		inorderFreq(root->leftChild);
		printf("%d \n", root->freq);
		inorderFreq(root->rightChild);
	}
}


//inorder function for freq binary tree
void inorderFreqBt(struct freqBt* root){
	
	if(root != NULL) {
		inorderFreqBt(root->leftChild);
		printf("%d\n", root->freq);
		inorderFreqBt(root->rightChild);
	}
}



int main() {
	struct wordNode *startptr = NULL;
	struct wordNode *freqptr = NULL;
	struct freqBt *btptr = NULL;
	FILE *fileptr = fopen("input.txt" , "r");
	char line[150];
	char *lineNumber,*word,*frequency,*newWord;
	int freq,lineNum,totalAccessBst;
	int i;
	
	int maxFreq,totalAccessBt;
	//struct wordNode node[100];
	
	if(fileptr == NULL) {
		puts("File couldnt be opened");
		return(-1);
	}//if there is no file such that or not openable file
	
	while(fgets(line, sizeof line,fileptr) != NULL ) {
		lineNumber = strtok(line,",");
		word = strtok(NULL,",");
		frequency = strtok(NULL," ");
		for(i = 0; word[i]; i++){
  				word[i] = tolower(word[i]);
		}
		
		freq = atoi(frequency);
		startptr = insertBst(startptr,freq,word);
		freqptr = insertFreqBst(freqptr,freq,word);
	
	totalAccessBst += depthNode(startptr,word,1) * freq;
	
	}
	
	
	printf("WORD BST FOR PART A: \n");
	inorder(startptr);
	printf("TOTAL ACCESS TIME FOR WORD BST IS : %d \n",totalAccessBst);
	
	printf("Max Frequency for freq bst: \n");
	//inorderFreq(freqptr);
	
	lineNum = atoi(lineNumber);
	for(i = 0; i<lineNum ; i++){
		maxFreq = findMax(freqptr);
		btptr = insertBt(btptr,maxFreq,freqptr->word);
		totalAccessBt += depth(btptr) * maxFreq;
		freqptr = deleteBstNode(freqptr,maxFreq);
		printf("%d \n" , maxFreq);

	}
	
	printf("TOTAL ACCESS FOR FREQUENCY BT:%d \n", totalAccessBt);
	printf("FREQUENCY BINARY TREE: \n");
	inorderFreqBt(btptr);
	
	
	fclose(fileptr);
	return 0;
}
