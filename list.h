/***************************************************************
*
* Mark Foudy
* mark@foudy.io
* August 15, 2022
* list.c
*
* This is the header file for the Penguin User Management Assistant (PUMA).
*
************************************************************ */

#define maxStackSize 100
#define CIPHERSHIFT 3

//-----------------------------
// PUMA ADT
//-----------------------------
typedef struct user{
	int uniqueKey;
	char *username;
	char *password;
	char *ip;
	char *MACaddress;
	int isAuthorized; // 1 is true and 0 is false
}user_t;

typedef struct node_adt{
	user_t *userData;
	struct node_adt *next;
} node;

// *********************************************
// PUMA FUNCTIONS:
// *******************************************

// creates
node* createList();
node* createNode(user_t *uData);

// *********************************************
// populate
int populateList(node** inHeadPtr);

// *********************************************
// prints

// to file
void printUnauthListToFile(node* head);
void printAuthListToFile(node* head);

// to console
void printListAllToConsole(node* head);
void printUnauthListToConsole(node* head);
void printAuthListToConsole(node* head);

//other
void printNode(node *n);

// *********************************************
// searches
node *findItem(node* inHead, int findWhat, char *theString);

// *********************************************
// sorts
int sortList(node **head);

// *********************************************
// inserts
int insertRear(node** inHeadPtr, user_t *uData) ;

// *********************************************
// deletes
int deleteList(node** inHeadPtr);
int deleteNode(node* inNode);
int deleteFront(node** inHeadPtr);
int deleteRear(node** inHeadPtr);
int deleteN(node** inHeadPtr, int position); // not used

// *********************************************
// helper functions
int generateUniqueKey(char *ip, int len);
int isAuthorized();
int listLength(node* inHead);
int listEmpty(node* inHead);
char *encrypt(char *password, int len);
char *decrypt(char *password, int len); // not used but remains to show to validate encryption algorithm
int validateIP(char *ip);
int validateMacAddress(char *mac);
user_t* getRearData(node* inHeadPtr);
int flush_buff();



