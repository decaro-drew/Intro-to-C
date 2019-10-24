/*
This program reads a file, and either adds a number into a hashtable, or searches for it, depending on the command
*/
#include <stdlib.h>
#include <stdio.h>

struct Node{
  struct Node* next;
  int val;
};

 struct Node* InsertNode(struct Node* node, int num){//take in hashtabe
   int x = 0;
   
  if(node  == NULL){
    node = malloc(sizeof(struct Node));
    node->next = NULL;
    node->val = num;
    printf("inserted\n");
    return node;
  }
  else{
    struct Node* ptr = node;
    struct Node* new;
    new = malloc(sizeof(struct Node));
    
    
    while(ptr->next != NULL){
      //   printf("ptr val: %d\n", ptr->val);
      if(ptr->val == num)
	x = 1;
      ptr = ptr->next;
      if(ptr->val == num)
	x=1;
      
    }
    	ptr->next = new;
	new->val = num;
	new->next = NULL;
    if(x == 1)
      printf("duplicate\n");
    else
      printf("inserted\n");
  }
  return node;
}


int main(int argc, char** argv){
 
  
  struct Node *ptr = NULL;
  struct Node *hash[10000];
 
 int i;
 for(i=0; i <10000; i++){
   hash[i]  = NULL;
 }
 FILE* fp = fopen(argv[1], "r");
 if(fp == NULL){
   printf("error\n");
   return 0;
 } 
 
 int num;
 char command;
 
 while(fscanf(fp, "%c %d", &command, &num)!= EOF){
   int key;
   if(num >= 0)
     key = num%10000;
   else
     key= -(num%10000);

   if(command == 'i'){
    
     if(hash[key]==NULL)
       hash[key] = InsertNode(ptr, num);
     else{
       struct Node *tmp = hash[key];
       hash[key] = InsertNode(tmp, num);
     }
     
   }
   if(command == 's'){
     if(hash[key] == NULL){
       printf("absent\n");
     }
     else{
       struct Node* ptr = hash[key];
       while(ptr != NULL){
	 if(ptr->val == num){
	   printf("present\n");
	   break;
	 }
	 ptr = ptr->next;
       }
       if(hash[key] == NULL)
	 printf("absent\n");
     }  
   }
 }


  fclose(fp);

  return 0;
}
