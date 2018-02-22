#include <stdio.h>
#include <string.h>

int dbg = 0;

struct usr {
  char name[80];
  int uid;
  int lockCount;
  int maxLockCount; // set to -1 for infinte unlocks
};

int main() {

  char name[80];
  int uid;
  int lockCount;
  int maxLockCount;
  //printf("%i\n", dbg++);
  FILE * userData = fopen("users.txt", "r");
  //printf("%i\n", dbg++);
  int userCount = 0;


  while(fscanf(userData, "%s %3i %3i %3i\n", name, &uid, &lockCount, &maxLockCount) != -1)
    userCount++;

  struct usr users[userCount];

  int count = 0;
  while(fscanf(userData, "%s %3i %3i %3i\n", users[count].name, &users[count].uid, &users[count].lockCount, &users[count].maxLockCount) != -1)
    count++;
  //printf("%i\n", dbg++);
  /*
  strcpy(users[0].name, "mark");
  users[0].uid = 14;
  users[0].lockCount = 0;
  users[0].maxLockCount = 2;
  printf("%i\n", dbg++);
  strcpy(users[1].name, "marc");
  users[1].uid = 902;
  users[1].lockCount = 34;
  users[1].maxLockCount = -1;
  */

  printf("%i\n", dbg++);
  for( int i = 0; i < userCount; i++){
    //printf("%i\n", dbg++);
    printf("%s %i %i %i\n", users[i].name, users[i].uid, users[i].lockCount, users[i].maxLockCount);
  }
  return 0;
}
