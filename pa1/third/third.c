/*
This program reads a file, and either gets the nth bit of number, set the nth bit to something else, 
or gets the complement of an nth bit

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void get(unsigned short x, int n){
  unsigned short int bit = (x >> (n))&1;
  printf("%hd\n", bit);
}


unsigned short int set(unsigned short int x, int n, int v){
  //shift it then or it with xc
  // unsigned short new;
  if(v==1){
    x =(1<<n) | x;
  }
  else{
     x = x & ~(1 << n); 
    
  }
  printf("%hu\n", x);
  return x;
}


unsigned short int comp(unsigned short int x, int n){
  //use XOR ^
  //  unsigned short new;
  x = x ^ (1<<n);
  printf("%hu\n", x);
  return x;

}


int main(int argc, char** argv){
  int n, v;
  unsigned short int x;
  char op[5];
  FILE* fp = fopen(argv[1], "r");
  
  fscanf(fp, "%hu", &x);
  
  
  while(fscanf(fp, "%s %d %d", op, &n, &v)!=EOF){
    // printf("x = %hu, op = %s, n = %d, v = %d\n", x, op, n, v);
    if(strcmp(op,"get") == 0){
      //  printf("its get\n");
      get(x, n);
    }
    if(strcmp(op, "set") == 0){
      //  printf("its set\n");
     x=  set(x, n, v);
    }
    if(strcmp(op, "comp") == 0){
      // printf("its comp\n");
     x= comp(x, n);
    }
  }
  fclose(fp);
  return 0;
}
