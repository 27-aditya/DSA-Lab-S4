#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// student data type
struct student{
  char name[1000];
  char rollno[100];
  int age;
};
// class for storing students
struct class{
  struct student s[10];
  int cntl;
};
// hash function
int hash(struct student s1){
  int sum = s1.age;
  for (int i = 0; i < strlen(s1.name); i++){
    sum += s1.name[i];
  }
  return sum%4;
}
/*int hash(int key, int hashsize) {
  return key % hashsize;
}*/
// main
int main(){
  struct class g1[4] = {0};
  int n;
  scanf("%d",&n);
  // take student inputs
  for (int i = 0; i < n; i++){
    struct student s;
    scanf("%s %s %d",s.name, s.rollno, &s.age);
    int index = hash(s);

    struct class *g = &g1[index];
    g->s[g->cntl++] = s;
  }

  char command;
  while (1){
    scanf("%c",&command);
    if(command == 'c'){
      int k;
      scanf("%d", &k);
      printf("%d", g1[k].cntl); // print no of students
      for (int i = 0; i < g1[k].cntl; ++i) {
        printf(" %s", g1[k].s[i].name); // print name of students
      }
      printf("\n");
    }
    else if(command >= '0' && command <= '3'){
      int found = 0;
      int m = command - '0';
      char branch[3];
      scanf("%s",branch);
      for (int i = 0; branch[i]; i++) {
        branch[i] = toupper((unsigned char)branch[i]); // convert to uppercase
      }
      for (int i = 0; i < g1[m].cntl; ++i) {
        // check for branch using the strcmp push the pointer to 7 ahead to just check the branch
        if (strcmp(g1[m].s[i].rollno + 7, branch) == 0) {
          found = 1;
          printf("%s ", g1[m].s[i].name); // print the student in the branch
        }
      }
      if (!found)
        printf("-1");
      printf("\n");
    }
    else if (command == 'e')
      return 0;
  }
}