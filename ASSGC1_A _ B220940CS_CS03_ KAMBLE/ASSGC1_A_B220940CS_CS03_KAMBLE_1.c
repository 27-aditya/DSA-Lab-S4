#include <stdio.h>
#include <stdlib.h>

struct stack {
  int top;
  int size;
  char *s;
};

void create(struct stack *stk, int size) {
    stk->top = -1;
    stk->size = size;
    stk->s = (char *)malloc(size * sizeof(char));
}

void push(struct stack *stk, char ch) {
    if(stk->top == stk->size - 1)
      printf("Stack Overflow\n");
    else{
      stk->top++;
      stk->s[stk->top] = ch;
    }
}

char pop(struct stack *stk) {
  char temp;
  if (stk->top == -1) {
      printf("Stack Underflow\n");
      return '\0';
  }
  temp = stk->s[stk->top];
  stk->top--;
  return temp;
}

int hasduparentheses(char arr[], struct stack *stk, int size) {
  for(int i=0;arr[i]!='\0';i++){
    if(arr[i]=='(' || arr[i] == '+' || arr[i]=='-' || arr[i]=='*' || arr[i] =='/' || arr[i]=='%'){
      push(stk, arr[i]);      
    }
    if(arr[i] ==')'){
      if(stk->s[stk->top]=='(')
        return 1;
      else{
        while(stk->s[stk->top]!='('){
          stk->top--;
        }
        stk->top--;
      }
    }
  }  
  return 0;
}

int main() {
  int n;
  scanf("%d", &n);
  char arr[100];
  scanf("%s", arr);
  struct stack stk;
  create(&stk, 100);
  int result = hasduparentheses(arr,&stk, n);
  free(stk.s);
  printf("%d\n", result);
  return 0;
}
