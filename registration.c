#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_REGISTRATION_NO_LEN 30
#define MAX_ADDRESS_LEN 80
#define MAX_NAME_LEN 20
typedef struct student
{
 char REGISTRATION_NO[MAX_REGISTRATION_NO_LEN]; // Assume it is a unique Key
 int rollno;
 char address[MAX_ADDRESS_LEN];
 int age;
 char NAME[MAX_NAME_LEN];
}student_t;
#define NUM_BUCKETS 97
student_t hash_tbl[NUM_BUCKETS];
int hash_func(char *REGISTRATION_NO)
{
 int a,c;
a=(REGISTRATION_NO[5]*1000+REGISTRATION_NO[6]*100+REGISTRATION_NO[7]*10+REGISTRATION_NO[8]);
 c = (a-9999)%NUM_BUCKETS;
 return c;
}
void hash_tbl_init(student_t hash_tbl[NUM_BUCKETS])
{
 int i;
 for(i=0;i<NUM_BUCKETS;i++)
 hash_tbl[i].REGISTRATION_NO[0] = '\0';
}
int insert_hash_tbl(student_t hash_tbl[NUM_BUCKETS],
 char REGISTRATION_NO[], int rollno, char address[], int age, char NAME[])
{
 int index;
 student_t *p_rec;
 index = hash_func(REGISTRATION_NO);
 printf("insert_hash_tbl : index = %d\n", index);
 if (hash_tbl[index].REGISTRATION_NO[0] != '\0')
 {
 printf("Slot is occupied. Can not add (TBD : implement collision handling)\n");
 return 0;
 }
 p_rec = &hash_tbl[index];
 strcpy(p_rec->REGISTRATION_NO, REGISTRATION_NO);
 p_rec->rollno = rollno;
 strcpy(p_rec->address, address);
 p_rec->age = age;
 strcpy(p_rec->NAME, NAME);
 return 1;

}
int search_hash_tbl(student_t hash_tbl[NUM_BUCKETS],
 char REGISTRATION_NO[], int *p_rollno, char address[], int *p_age, char NAME[])
{
 int index;
 student_t *p_rec;
 index = hash_func(REGISTRATION_NO);
 printf("search_hash_tbl : index = %d\n", index);
 if (strcmp(hash_tbl[index].REGISTRATION_NO, REGISTRATION_NO) != 0)
 {
 printf("search_hash_tbl : record with REGISTRATION_NO %s does not exist\n",REGISTRATION_NO);
 return 0;
 }
 p_rec = &hash_tbl[index];
 strcpy(REGISTRATION_NO, p_rec->REGISTRATION_NO);
 *p_rollno = p_rec->rollno;
 strcpy(address, p_rec->address);
 *p_age = p_rec->age;
 strcpy(NAME, p_rec->NAME);
 return 1;
}
int delete_hash_tbl(student_t hash_tbl[NUM_BUCKETS], char REGISTRATION_NO[])
{
 int index;
 index = hash_func(REGISTRATION_NO);
 printf("delete_hash_tbl : index = %d\n", index);
 if (strcmp(hash_tbl[index].REGISTRATION_NO, REGISTRATION_NO) != 0)
 {
 printf("delete_hash_tbl : record with REGISTRATION_NO %s does not exist\n",REGISTRATION_NO);
 return 0;
 }
 strcpy(hash_tbl[index].REGISTRATION_NO,"");
 return 1;
}
void print_hash_tbl(student_t hash_tbl[NUM_BUCKETS])
{
 int i;
 student_t *p_rec;
 printf("The elements in hash table are:\n");
 for(i=0;i<NUM_BUCKETS;i++)
 {
 if (strcmp(hash_tbl[i].REGISTRATION_NO, "") != 0)
 {
 p_rec = &hash_tbl[i];
 printf("hash_tbl[%d]=<REGISTRATION_NO=%s, rollno=%d, address=%s, age=%d,NAME=%s>\n",i, p_rec->REGISTRATION_NO, p_rec->rollno, p_rec->address, p_rec->age, p_rec->NAME);
 }
 }
}
int main()
{
 int choice, rollno, age, ret;
 char REGISTRATION_NO[MAX_REGISTRATION_NO_LEN],
address[MAX_ADDRESS_LEN], NAME[MAX_NAME_LEN];
 hash_tbl_init(hash_tbl);
 while (1)
 {
 printf(" 1)Print Hash Table\n");
 printf(" 2)Insert Record\n");
 printf(" 3)Search Record\n");
 printf(" 4)Delete Record\n");
 printf(" 0)Exit\n");
 printf(" What do you want to do?");
 scanf("%d", &choice);
 switch(choice)
 {
 case 1:
 print_hash_tbl(hash_tbl);
 break;
 case 2:
 printf("Enter REGISTRATION_NO rollno address age NAME\n");
 scanf("%s%d%s%d%s", REGISTRATION_NO, &rollno, address, &age, NAME);
 ret = insert_hash_tbl(hash_tbl, REGISTRATION_NO, rollno, address, age, NAME);
 if (ret == 1)
 printf("insert_hash_tbl succeeded\n");
 else
 printf("insert_hash_tbl failed\n");
 break;
 case 3:
 printf("Which REGISTRATION_NO do you want to search?\n");
 scanf("%s", REGISTRATION_NO);
 ret = search_hash_tbl(hash_tbl, REGISTRATION_NO, &rollno, address, &age,NAME);
 if (ret == 1)
 printf("search_hash_tbl succeeded\nREGISTRATION_NO=%s, rollno=%d,address=%s, age=%d, NAME=%s",REGISTRATION_NO, rollno, address, age, NAME);
 else
 printf("search_hash_tbl failed\n");
 break;
 case 4:
 printf("Which REGISTRATION_NO do you want to delete?\n");
 scanf("%s", REGISTRATION_NO);
 ret = delete_hash_tbl(hash_tbl, REGISTRATION_NO);
 if (ret == 1)
 printf("delete_hash_tbl succeeded\n");
 else
 printf("delete_hash_tbl failed\n");
 break;
 case 0:
 exit(0);
 }
 }
}
