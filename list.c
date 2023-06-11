/***************************************************************
*
* Mark Foudy
* mark@foudy.io
* August 15, 2022
* list.c
*
* This is my source file for the Penguin User Management Assistant (PUMA).
*
************************************************************ */

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "list.h"

typedef enum { False, True } boolean;


//-----------------------------------------------
// Creates
//-----------------------------------------------

/**************************************************************************
* createList: This creates the linked list to be used by PUMA
****************************************************************************/
node* createList() {
	node* p = NULL;
	return p;
}

/**************************************************************************
* createNode: This creates and allocates memory space
 * to house individual user data in program structure.
****************************************************************************/
node* createNode(user_t *uData) {
	node* tempNode = (node*)malloc(sizeof (node));

	if(tempNode != NULL) {
		tempNode->userData = uData;
		tempNode->next = NULL;
		return tempNode;
	}
	else {
		return NULL;
	}
}

/**************************************************************************
* populateList Function: This function is a major driver of the PUMA system.
* It relies on several helper functions to accomplish its task.
****************************************************************************/

int populateList(node** inHeadPtr){
    //This will read from the file that the user specifies.
    // it will store each record into the linked list using
    // the following helper function: int insertRear(node** inHeadPtr, int item);
    char username[30];
    char password[30];

    // It was necessary to make copies of both the  ip address and the mac address
    // because in the validation process, strtok() was altering the character strings and
    // putting them into subcomponents, therefore I had to pass a copy, not the original.
    char ip[16];
    char copyOfIp[16];

    char mac[18];
    char copyOfMac[18];

    user_t *temp;
    FILE *fp;
    char line[80];

    char filename[30];
    printf("Enter filename to be imported into system: ");
    scanf("%s", filename);



    fp = fopen(filename, "r");

    if (fp == NULL)
        return 0; // fail

    printf("\n\nReading data from file. If there is invalid data then it will be reported below.\n");

    while (fgets(line, sizeof(line), fp) != NULL){
        //On success, the function returns the number of variables filled.
        if ( sscanf(line, "%s %s %s %s", username, password, ip, mac) != 4)
            continue; // not all data is present, continue reading the file

        // here we have to copy the ip and mac to their copies so we can validate them
        strcpy(copyOfIp, ip);
        strcpy(copyOfMac, mac);


        // validateIP() and validateMacAddress() both use strtok() which takes the string and splits it into
        // components using the (.) period for IP and (:)colon for MAC address. If we pass the original strings
        // they get modified. So, instead we pass copies.
        if (validateIP(copyOfIp) == -1){
            printf("%s has invalid ip.\n", username);
            continue; // skip the rest and read another
        }

        if (validateMacAddress(copyOfMac) == -1){
            printf("%s has invalid mac address.\n", username);
            continue; // skip the rest and read another
        }

        // we malloc the struct
        temp = (user_t *)malloc(sizeof(user_t));

        // we have to malloc for the char*'s because those are just pointers with no memory yet
        // these are only for string (char *)
        temp->username = (char *)malloc(sizeof(username));
        temp->password = encrypt((char *)malloc(sizeof(password)), sizeof(password));
        temp->ip = (char *)malloc(sizeof(ip));
        temp->MACaddress = (char *)malloc(sizeof(mac));

        // this is an int
        temp->uniqueKey = generateUniqueKey(ip, strlen(ip));

        // these are all strings so we to strcpy
        strcpy(temp->username, username );
        strcpy(temp->password, password );
        strcpy(temp->ip, ip );
        strcpy(temp->MACaddress, mac );

        // this is int
        temp->isAuthorized = isAuthorized();

        // now the struct is malloced and filled in
        // now I insert the struct into the list
        insertRear( inHeadPtr, temp);
    }
    fclose(fp);

    return 1; // success
}

/**********************************************************
 * PRINT Functions to be used specifically in menu option #2.
 **********************************************************/

/**********************************************************
 * printUnauthListToFile Function
 **********************************************************/
//int isAuthorized; // 1 is true and 0 is false
void printUnauthListToFile(node* head){
    node* temp = head;
    FILE *fp;
    char filename[21] = "blacklisted_users.txt";
    filename[20] = '\0';
    fp = fopen(filename, "w");


    while(temp!=NULL) {
        if(temp->userData->isAuthorized == 0) {
            fprintf(fp, "%d %s\n", temp->userData->uniqueKey,  temp->userData->username);
        }
        // advance the temp pointer
        temp = temp->next;
    }
    fclose(fp);
}

/**************************************************************************
* printAuthListToFile Function
****************************************************************************/
void printAuthListToFile(node* head){
    node* temp = head;
    FILE *fp;
    char filename[21] = "whitelisted_users.txt";
    filename[20] = '\0';
    fp = fopen(filename, "w");


    while(temp != NULL) {
        if(temp->userData->isAuthorized == 1) {
            fprintf(fp, "%d %s\n", temp->userData->uniqueKey,  temp->userData->username);
        }
        // advance the temp pointer
        temp = temp->next;
    }
    fclose(fp);

}


/**************************************************************************
* printListAllToConsole Function
****************************************************************************/
void printListAllToConsole(node* head){
    node* temp = head;
    int num = 0;

    while(temp != NULL) {
        printf("%d %d %s\n", num++, temp->userData->uniqueKey,  temp->userData->username);

        // advance the temp pointer
        temp = temp->next;
    }
}

/**************************************************************************
* printUnauthListToConsole Function
****************************************************************************/
void printUnauthListToConsole(node* head){
    node* temp = head;

    while(temp!=NULL) {
        if(temp->userData->isAuthorized == 0) {
            printf("%d %s\n", temp->userData->uniqueKey,  temp->userData->username);
        }
        // advance the temp pointer
        temp = temp->next;
    }
}
/**************************************************************************
* printAuthListToConsole Function
****************************************************************************/
void printAuthListToConsole(node* head){
    node* temp = head;

    while(temp != NULL) {
        if(temp->userData->isAuthorized == 1) {
            printf("%d %s\n", temp->userData->uniqueKey,  temp->userData->username);
        }
        // advance the temp pointer
        temp = temp->next;
    }
}

/**************************************************************************
* printNode Function
****************************************************************************/
void printNode(node *n){
    printf("UniqueKey is: %d\n", n->userData->uniqueKey);
    printf("Username is: %s\n", n->userData->username);
    printf("Password is: %s\n", n->userData->password);
    printf("IP Address is: %s\n", n->userData->ip);
    printf("Mac Address is: %s\n", n->userData->MACaddress);

    if(n->userData->uniqueKey == 1)
        printf("This user is authorized!\n\n");
    else
        printf("This user is NOT authorized!\n\n");
}


/*********************************************
*  findItem() returns the integer location of the
*  first appearance of the item in the list.
*  If item is not in the list it returns 0.
********************************************/
node *findItem(node* inHead, int findWhat, char *theString) {
    node* p = inHead;
    int curLocation = 1;

    if (inHead == NULL) {
        return NULL;
    }


    while(p != NULL) {
        switch (findWhat){
            case 0:
                if(strcmp(p->userData->username, theString) == 0) {
                    return p;
                }
                break;
            case 1:
                if(strcmp(p->userData->ip, theString)  == 0) {
                    return p;
                }
                break;
            case 2:
                if(strcmp(p->userData->MACaddress, theString) == 0) {
                    return p;
                }
                break;

            default:
                break;
        }
        // advance the two pointer pairs
        p = p->next;
    }

    // never found a match in the list
    return NULL;
}

/**************************************************************************
* swap Function
****************************************************************************/
void swap(node *a, node *b)
{
    user_t *temp = a->userData; // save the one struct data
    a->userData = b->userData; // swap
    b->userData = temp;        // stores the saved struct to b
}

/**************************************************************************
* sortList Function
****************************************************************************/
int sortList(node **head)
{
    int swapped, i;
    node *ptr1;
    node *lptr = NULL;

    if (head == NULL || *head == NULL)
        return -1;

    do
    {
        swapped = 0;
        ptr1 = *head; // set ptr1 to the head of the list

        // traverse the list using ptr1
        while (ptr1->next != NULL)
        {
           if (strcmp(ptr1->userData->username, ptr1->next->userData->username) > 0 ) // test of return value
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
    return 0; //success
}

/**************************************************************************
* insertRear Function:
****************************************************************************/
int insertRear(node** inHeadPtr, user_t *uData) {
    node *p = *inHeadPtr; // the list
    node *q = NULL;

    node *temp = createNode(uData);
    temp->userData = uData;
    temp->next = NULL;

    // INSERT NODE INTO EMPTY LIST
    if (listEmpty(*inHeadPtr)) {
        *inHeadPtr = temp;
        return 1;

    }
    else {
        //FIND THE LAST NODE (make p point to it)
        q = p->next;
        while (q != NULL){
            p = q;
            q = q->next;
        }
    }

    //ATTACH NEW NODE TO THE LAST NODE
    p->next = temp;

    return 1;
}

//-------------------------------------------------------------------
//  The following Functions are deletion functions which each have specific purposes.
//  In order to ensure future development of this platform, I decided against
//  removing the last delete function whose functionality is not currently a part of this platform.
/**************************************************************************
* deleteFront Function
****************************************************************************/
int deleteFront(node** inHeadPtr) {
    node* temp = NULL;

    // VERIFY INCOMING PTRS NOT NULL
    if(inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }
    else {
        // IF only one element on the list
        if(listLength(*inHeadPtr) == 1) {
            temp = *inHeadPtr;
            *inHeadPtr = NULL;
            free(temp);
            return 1;
        }
        else {
            temp = *inHeadPtr;
            *inHeadPtr = temp->next;
            free(temp);
            return 1;
        }
    }
}

/**************************************************************************
* deleteRear Function
****************************************************************************/
int deleteRear(node** inHeadPtr) {
    node* temp = NULL;
    int num = 0;

    // VERIFY INCOMING PTRS NOT NULL
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }
    else {
        num = listLength(*inHeadPtr);

        //IF only one element in list
        if(num == 1) {
            temp = *inHeadPtr;
            *inHeadPtr = NULL;
            free(temp);
            return 1;
        }
        else {
            //CHECK IF ONLY TWO ELEMENTS
            if(num == 2) {
                temp = (*inHeadPtr)->next;
                (*inHeadPtr)->next = NULL;
                free(temp);
                return 1;
            }
                //MORE THAN 2 in the list
            else {
                node* p = *inHeadPtr;
                node* q = p->next;
                node* r = q->next;
                while (r != NULL) {
                    p = q;
                    q = r;
                    r = r->next;
                }//WHILE
                p->next = NULL;
                free(q);
                return 1;
            }
        }
    }
}

/**************************************************************************
* Delete Node Function
****************************************************************************/
int deleteNode(node* inNode) {
    if (inNode != NULL) {
        free(inNode);
        return 1;
    }
    else {
        return -1;
    }
}

/**********************************************************************************************
 * function deleteList() traverses and deletes each node in list.
 * This function provides a mechanism where system administrators
 * can remove the complete lists of users.
 *************************************************************************************************/
int deleteList(node** inHeadPtr) {
    node* p = *inHeadPtr;
    node* q = NULL;

    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }// IF

    q = p->next;
    while(q != NULL) {
        deleteNode(p);
        p = q;
        q = q->next;
    }

    deleteNode(p);
    *inHeadPtr = NULL;
    return 1;

}


/******************************************************************************************
 * function deleteN: allows system administrator options to delete individual user records
 * This function is not currently used by PUMA but remains in the source code
 * in the event that this feature becomes necessary for future versions of this application.
************************************************************************************/
int deleteN(node** inHeadPtr, int position) {

    node* tempNode = NULL;
    node* p = NULL;
    node* q = NULL;
    int numStatus = 0;
    int numLen = 0;
    int cur_location = 1;

    //VERIFY INCOMING PTRS NOT NULL
    if(inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }

    //DELETE CASES OF EMPTY, SINGLETON, GENERAL LISTS
    numLen = listLength(*inHeadPtr);

    //CASE 1: DELETE FROM SINGLETON LIST OR FIRST POSITION
    if(numLen == 1 || position == 1) {
        numStatus = deleteFront(inHeadPtr);
        return numStatus;
    }

        // CASE 2: DELETE CASE WHEN position > LIST LENGTH
    else if(position > numLen) {
        numStatus = deleteRear(inHeadPtr);
        return numStatus;
    }

        // CASE 3: DELETE FROM MIDDLE OF LIST AT position
        // algorithm:
        //  --FIND THE NODE AT POSITION (position -1)
        //  --ATTACH ANCHOR TO NODE AT POSITION AFTER (position)
        //  --ATTACH FIRST HALF OF LIST TO ANCHOR
        //  --DELETE NODE AT POSITION
    else {
        //MAKE p POINT TO NODE RIGHT BEFORE position
        p = *inHeadPtr;
        while(cur_location < position-1) {
            p = p->next;
            cur_location++;
        }
        // when the while loop ends, p is pointing to the node prior to the one to be deleted

        //q is now pointing to the next node which is the one to be deleted
        q = p->next;

        //link the node prior to the delete node to the node after the delete node
        p->next = q->next;

        //now q is an orphan and can be deleted
        deleteNode(q);
    }

    return 1;
}

//---------------------------------------------------------------------------
// HELPER FUNCTION SECTION:
// All these functions are called by other functions to achieve specific tasks
//---------------------------------------------------------------------------

/**************************************************************************
* generateUniqueKey Function:
* This function generates a unique key for each user record.
****************************************************************************/
int generateUniqueKey(char *ip, int len){
	int sum = 0;
	int i = 0;

	for (i = 0; i < len; i++){
		sum += ip[i];
	}

	//num = (rand() % (upper � lower + 1)) + lower 
	sum = sum * (rand() % 100 + 1);

	return sum;

}

/**************************************************************************
* isAuthorized Function
****************************************************************************/
int isAuthorized(){
	return rand() % 2;
}

/**************************************************************************
* listEmpty Function: 1 means empty/ 0 means not empty.
****************************************************************************/
int listEmpty(node* inHead) {
    if (inHead == NULL) {
        return 1; // 1 means empty
    }
    else {
        return 0;  // 0 means not empty
    }
}

/**************************************************************************
* listLength Function
****************************************************************************/
int listLength(node* inHead){
    node* p = inHead;
    node* q = NULL;
    int count = 1;

    if(p == NULL)
        return 0;
    else{
        q = p->next;
        if (q == NULL) {
            return -1;
        }
        else {
            while(q != NULL) {
                count++;
                q = q->next;
            }
            return count;
        }
    }
}


/*************************************************************************
* encrypt Function:
* This function is used to obscure user passwords and protect user information.
****************************************************************************/
char *encrypt(char *password, int len){
	char ch;
	int i;
	char *encryptedPassword = (char *) malloc (sizeof(password) * len);
	strcpy(encryptedPassword, password);


	for(i = 0; encryptedPassword[i] != '\0'; ++i){
		ch = encryptedPassword[i];
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + CIPHERSHIFT;
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			encryptedPassword[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + CIPHERSHIFT;
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			encryptedPassword[i] = ch;
		}
	}
	return encryptedPassword;
}

/*********************************************************************************
* decrypt Function: Not Used, but included in order to validate encryption algorithm.
*********************************************************************************/
char *decrypt(char *password, int len) {
	char ch;
	int i;
	char *decryptedPassword = (char *) malloc (sizeof(password) * len);
	strcpy(decryptedPassword, password);


	for(i = 0; decryptedPassword[i] != '\0'; ++i){
		ch = decryptedPassword[i];
		if(ch >= 'a' && ch <= 'z'){
			ch = ch - CIPHERSHIFT;
			if(ch < 'a'){
				ch = ch + 'z' - 'a' + 1;
			}
			decryptedPassword[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch - CIPHERSHIFT;
			if(ch < 'A'){
				ch = ch + 'Z' - 'A' + 1;
			}
			decryptedPassword[i] = ch;
		}
	}
	return decryptedPassword;
}

/**************************************************************************
* validateIP Function: Ensures that an invalid IP is flagged.
****************************************************************************/
int validateIP(char *ip){
	char *tempIp = ip;
	char *result;
	int ipArr[4];
	int i = 0;

	//char * strtok ( char * str, const char * delimiters );
	// split the string by periods
	result = strtok(tempIp, ".");

	while(result != NULL){
		if (i>3)
			return -1; // this means we incremented i to 4 and the while condition was still true
		else{
			// convert result to an int
			sscanf(result, "%d", &ipArr[i]);

			// validate the individual ip number
			// each ip unit is between 0-255 inclusive
			if (ipArr[i] < 0 || ipArr[i] > 255){
				return -1; 
			}
			i++;
			result = strtok (NULL, ".");
		}
	}

	// check if there are less than 4 octets
	if (i<4)
		return -1;

	if(ipArr[0] == 255 && ipArr[1] == 255 && ipArr[2] == 255 && ipArr[3] == 255) 
		return -1;  // 255.255.255.255 is reserved for broadcast

	if(ipArr[0] == 127 && ipArr[1] == 0 && ipArr[2] == 0 && ipArr[3] == 1) 
		return -1; // 127.0.0.1 reserved for localhost

	return 0;  // success 

}
/**************************************************************************
* validateMacAdress Function: Ensures that an invalid MAC Address is flagged
****************************************************************************/
int validateMacAddress(char *mac){
	char *tempMac = mac;
	char *result;
	char *macArr[6]; // 6 strings with 2 hex digits each
	int i = 0;
	int x = 0;


	// char * strtok ( char * str, const char * delimiters );
	// split the string by periods
	result = strtok(tempMac, ":");

	while(result != NULL){
		if (i>5)
			return -1; // this means we incremented i to 4 and the while condition was still true
		else{
			macArr[i] = result;

			// check length of result to make sure it's just 2
			if (strlen(result) != 2)
				return -1;  // one of the components of the hex is too long

			//int isxdigit( int arg ); 
			//0 means not hex
			for(x=0; x<2; x++){
				if(isxdigit(result[x])== 0)
					return -1; // err one char is not hex
			}

			i++;
			result = strtok (NULL, ":");
		}
	}

	if (i<6)
		return -1;

	return 0;  // success 

}

/**************************************************************************
* getRearData Function
****************************************************************************/
user_t* getRearData(node* inHeadPtr){
    node* p = inHeadPtr;

    if(p == NULL){
        return NULL;
    }
    else{
        // while the p->next is not null, we keep advancing
        // when it is null, that node that p points to is the last one and that
        // is the data we want to return from this function
        while(p->next != NULL) {
            p = p->next; // advance the pointer
        }
        return p->userData; // this is a pointer to the user_t structure
    }
}

/**************************************************************************
* flush_buff Function
****************************************************************************/
int flush_buff()
{
    while (getchar() != '\n'){}
    return 0;
}
