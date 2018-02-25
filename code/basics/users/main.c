//users
//author: valentin veluppillai
#include <stdio.h>
#include <string.h>


struct usr {
  char name[80];
  int uid;
  int lockCount;
  int maxLockCount; // set to -1 for infinte unlocks
};

int findUid(int, int, struct usr*);

int main() {

  char name[80];
  int index;
  int uid;
  int lockCount;
  int maxLockCount;
  int userCount = 0;

  FILE* userData = fopen("users.txt", "r");
  FILE* logData;

  while(fscanf(userData, "%s%i%i%i", name, &uid, &lockCount, &maxLockCount) != -1)
    userCount++;

  struct usr users[userCount];

  fclose(userData);
  userData = fopen("users.txt", "r");

  for(int i = 0; i < userCount; i++)
    fscanf(userData, "%s%i%i%i", users[i].name, &users[i].uid, &users[i].lockCount, &users[i].maxLockCount);

  fclose(userData);

  for( int i = 0; i < userCount; i++)
    printf("entry %i:\tname: %s\tuid: %i\tlockcount: %i\tmaxlockcount: %i\n", i, users[i].name, users[i].uid, users[i].lockCount, users[i].maxLockCount);

  printf("enter uid: ");
  scanf("%i", &uid);
  index = findUid(uid, userCount, users);

  logData = fopen("log.txt", "a");

  if(index != -1){
    if( (users[index].lockCount >= users[index].maxLockCount)&&(users[index].maxLockCount >= 0)){
      printf("\nDENIED: out of unlocks\n");
      fprintf(logData, "User %s [UID: %i] tried to unlock; ERR: OOU\t time: insert_time_here\n", users[index].name, users[index].uid);
    }
    else{
      printf("\nGRANTED\n");
      fprintf(logData, "User %s [UID: %i] unlocked\t ERR: - \t time: insert_time_here\n", users[index].name, users[index].uid);
      users[index].lockCount++;
    }
  }
  else{
    printf("\nDENIED: unknown user\n");
    fprintf(logData, "unknown user [UID: %i] tried to unlock\t ERR: UU\t time: insert_time_here\n", uid);
  }

  userData = fopen("users.txt", "w");
  for( int i = 0; i < userCount; i++){
    fprintf(userData, "%s %i %i %i\n", users[i].name, users[i].uid, users[i].lockCount, users[i].maxLockCount);
  }
  fclose(userData);
  return 0;
}

int findUid(int uid, int len, struct usr* users){
  for(int i = 0; i < len; i++){
    if(uid == (users+i)->uid)
      return i;
  }
  return -1;
}
