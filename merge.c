#include "merge.h"

void sort(int *vetor, int n){
    int *res=(int*)malloc(n * sizeof(int));
    mergesort(vetor,res,0,n-1);
}

void mergesort(int *vet,int *res,int begin,int end){
    int half;
    if(begin<end){
        half=(begin+end)/2;
        mergesort(vet,res,begin,half);
        mergesort(vet,res,half+1,end);
        merge(vet,res,begin,half,end);
    }
}

void merge(int *vet,int *res,int begin, int half, int end){
  int set1, set2,cont=0,i;
  set1=begin;
  set2=half+1;
  while(set1<=half && set2<=end){
      if(vet[set1]<vet[set2]){
          res[cont++]=vet[set1++];
      }
      else{
          res[cont++]=vet[set2++];
      }
  }
  while(set1<=half){
      res[cont++]=vet[set1++];
  }
  while(set2<=end){
      res[cont++]=vet[set2++];
  }
  for(i=0;i<cont;i++){
      vet[i+begin]=res[i];
  }
}
