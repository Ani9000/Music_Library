#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {// all the categories of the linked list
    char *firstName;
    char *familyName;
    char *address;
    char *phoneNumber;
    struct node *next;
} Node;

typedef struct phBook {// a global headnode variable
Node *head;
} phBook;

// Declarations of linked list functions
//
Node *createNode(char *familyName,char *firstName,char *address,char *phoneNumber);

// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser(char *prompt, char *s, int arraySize);
void familyNameDuplicate(char *familyName);
void familyNameFound(char *familyName);
void familyNameNotFound(char *familyName);
void familyNameDeleted(char *familyName);
void phoneNumberFound(char *phoneNumber);
void phoneNumberNotFound(char *phoneNumber);
void printPhoneBookEmpty(void);
void printPhoneBookTitle(void);

const int MAX_LENGTH = 1024;

int main(void) {
// Declare the head of the linked list.
phBook *list;
list = malloc(sizeof(phBook));
list->head = NULL;

// Announce the start of the program
printf("Personal Phone Book.\n\n");
printf("%s", "Commands are I (insert), D (delete), S (search),\n"
"P (print), Q (quit), R(Reverse).\n");

char response;
char input[MAX_LENGTH + 1];
do {
inputStringFromUser("\nCommand", input, MAX_LENGTH);

// Response is the first character entered by user.
// Convert to uppercase to simplify later comparisons.
response = toupper(input[0]);

if (response == 'I') {
char *promptName = "familyName";
char *familyName = malloc(sizeof(char)*MAX_LENGTH);
inputStringFromUser(promptName, familyName, MAX_LENGTH);
//gets family Name

char *promptfirstName =  "firstName";
char *firstName = malloc(sizeof(char)*MAX_LENGTH);
inputStringFromUser(promptfirstName, firstName, MAX_LENGTH);
//gets first Name

char *promptaddress = "address";
char *address = malloc(sizeof(char)*MAX_LENGTH);
inputStringFromUser(promptaddress, address, MAX_LENGTH);
//gets address
           
char *promptPhoneNumber = "phoneNumber";
char *phoneNumber = malloc(sizeof(char)*MAX_LENGTH);
inputStringFromUser(promptPhoneNumber, phoneNumber, MAX_LENGTH);
//gets phoneNumber

Node *newNode = createNode(familyName,firstName,address,phoneNumber);
//creates new node

if(list->head == NULL){
list->head = newNode;
}
//if the list is empty

else{
Node *n = list->head;
if(n->next == NULL){
int compare = strncmp((n->familyName),(newNode->familyName),MAX_LENGTH);
int similarityTest = strcmp(n->familyName,newNode->familyName);

if(similarityTest ==0){
familyNameDuplicate(newNode->familyName);
}
//checks if the surname is a duplicate

else{
if(compare>0){
newNode->next = n;
list->head = newNode;
}
//if the persons Name goes before the one in the list

else{
n->next = newNode;
}
}

}
//if only one element in the list

else{
Node *p = list->head;
bool duplicate = false;
//delcares variables for the while loop

while(p!=NULL){
if(strcmp(p->familyName,newNode->familyName) == 0){
duplicate = true;
}
p = p->next;
}
//checks if there is a duplicate surname

if(duplicate){
familyNameDuplicate(newNode->familyName);
}
//case for there being a duplicate surname

else if(strncmp((n->familyName),(newNode->familyName),MAX_LENGTH)>0){
newNode->next = n;
list->head = newNode;
}
//case for if the new node being elegible for the start of the list

else{
while(n->next != NULL && strncmp((n->next->familyName),(newNode->familyName),MAX_LENGTH)<0){
n = n->next;
}
//checks to see if the newNode can go after the current node

newNode->next = n->next;
n->next = newNode;
//assigns the new node into the existing list
}
//for when the new node has to inserted in the middle or at the end
}
//for multiple different entries
}
}
       
else if (response == 'D') {
// Delete a name from the list.
char *prompt = "\nEnter the name of the name to be deleted";
char *familyNameDeletion = malloc(sizeof(char)*MAX_LENGTH);
inputStringFromUser(prompt,familyNameDeletion,MAX_LENGTH);
//gets name of name to be deleted from user

Node *p = list->head;
if(p == NULL){
familyNameNotFound(familyNameDeletion);
}
//if the list is empty

else if(strcmp(p->familyName,familyNameDeletion) == 0){
Node *temp = p->next;
familyNameDeleted(familyNameDeletion);
free(p->phoneNumber);
free(p->address);
free(p->firstName);
free(p->familyName);
free(p);
list->head = temp;
}
//check if the first element in the list is the element that needs to be deleted

else if(p->next == NULL){
familyNameNotFound(familyNameDeletion);
}
//check if there is only one element in the list

else{
bool deleting = false;
while(p->next != NULL && !deleting){
if(strcmp(p->next->familyName,familyNameDeletion) == 0){
deleting = true;
}
else{
p = p->next;
}
}
//searches for the node to delete

if(deleting){
familyNameDeleted(p->next->familyName);
Node *temp = p->next->next;
free(p->next->phoneNumber);
free(p->next->address);
free(p->next->firstName);
free(p->next->familyName);
free(p->next);

p->next = temp;
}
//if the  name is found in the nodes, then it frees all the memory

else{
familyNameNotFound(familyNameDeletion);
}
//if the  is not found in the list then print that it could not be found
}
//if there are multiple elements
}
else if (response == 'R') {
// Search for a cotnact by its phone number.

char *prompt = "\nEnter the  number to search for" ;
char *phoneNumberSearch = malloc(sizeof(char)*MAX_LENGTH);
inputStringFromUser(prompt,phoneNumberSearch,MAX_LENGTH);
//gets the phone number

Node *p = list->head;
bool exists = false;
while(p!=NULL && !exists){
if(strcmp(p->phoneNumber,phoneNumberSearch) == 0){
exists = true;
}
else{
p = p->next;
}
}
//searches through the list while the node pointer is not null and while the number is not found

if(exists){
phoneNumberFound(phoneNumberSearch);
printf("\n%s\n",p->familyName);
printf("%s\n",p->firstName);
printf("%s\n",p->address);
printf("%s\n",p->phoneNumber);
               
}
//if the number is found, the while loop will stop at that node, so it is easy to print out all the elements contained in the node
else{
phoneNumberNotFound(phoneNumberSearch);
}
//if the number is not found in the list print so
        }
else if (response == 'S') {
// Search for a person from his  surname.

char *prompt = "\nEnter the name to search for" ;
char *phoneNumberSearch = malloc(sizeof(char)*MAX_LENGTH);
inputStringFromUser(prompt,phoneNumberSearch,MAX_LENGTH);
//gets the name of the phoneNumber to search for from the user

Node *p = list->head;
bool exists = false;
while(p!=NULL && !exists){
if(strcmp(p->familyName,phoneNumberSearch) == 0){
exists = true;
}
else{
p = p->next;
}
}
//searches through the list while the node pointer is not null and while the name is not found

if(exists){
familyNameFound(phoneNumberSearch);
printf("\n%s\n",p->familyName);
printf("%s\n",p->firstName);
printf("%s\n",p->address);
printf("%s\n",p->phoneNumber);
               
}
//if the name is found, the while loop will stop at that node, so it is easy to print out all the elements contained in the node
else{
familyNameNotFound(phoneNumberSearch);
}
//if the name is not found in the list print so
        }
else if (response == 'P') {
//prints out the list

if(list->head == NULL){
printPhoneBookEmpty();
}
//if the list is empty, print out that the phoneBookis empty
else{
printPhoneBookTitle();
Node *n = list->head;
while(n != NULL){
printf("%s\n",n->familyName);
printf("%s\n",n->firstName);
printf("%s\n",n->address);
printf("%s\n\n",n->phoneNumber);
n = n->next;
}
//moves though the list and while the node is not null, prints out the node
}
}
        else if (response == 'Q') {
            ; // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf ("\nInvalid command.\n");
        }
    } while (response != 'Q');
    // Delete the entire linked list.

    while(list->head != NULL){
familyNameDeleted(list->head->familyName);
Node *newHead = list->head->next;
//stores the address of the node that will become the new head

free(list->head->phoneNumber);        
free(list->head->address);
free(list->head->firstName);
free(list->head->familyName);
free(list->head);
//frees allocated memmory

list->head = newHead;
//assigns the new head to the head
}
//while the head isnt empty, delete the first term

    // Print the linked list to confirm deletion.
if(list->head == NULL){
printPhoneBookEmpty();
}
//if the list is empty
else{
printPhoneBookTitle();
Node *n = list->head;
while(n != NULL){
printf("Family name --> %s\n",n->familyName);
printf("firstName --> %s\n",n->firstName);
printf("address --> %s\n\n",n->address);
printf("phoneNumber --> %s\n\n",n->phoneNumber);            
           
n = n->next;
}
//steps through the list and prints every node
}

return 0;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char *prompt, char *s, int maxStrLength) {
    int i = 0;
    char c;
    printf("%s --> ", prompt);
    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;
    s[i] = '\0';
}

// Function to call when the user is trying to insert a name
// that is already in the personal Phone Book.
void familyNameDuplicate(char *familyName) {
printf("\nThe name '%s' is already in the Phone Book.\n" "No new name entered.\n", familyName);
}
// Function to call when a  name was found in the personal Phone Book.
void familyNameFound(char *familyName) {
printf("\nThe name '%s' was found in the Phone Book.\n",familyName);
}
// Function to call when a  name was found in the personal Phone Book.
void phoneNumberFound(char *familyName) {
printf("\nThe number '%s' was found in the Phone Book.\n",familyName);
}
// Function to call when a  number was not found in the personal Phone Book.
void phoneNumberNotFound(char *phoneNumber) {
printf("\nThe  number '%s' was not found in the Phone Book.\n",phoneNumber);
}

// Function to call when a  name was not found in the personal Phone Book.
void familyNameNotFound(char *phoneNumber) {
printf("\nThe  name '%s' was not found in the Phone Book.\n",phoneNumber);
}
// Function to call when a  name that is to be deleted
// was found in the personal Phone Book.
void familyNameDeleted(char *familyName) {
    printf("\nDeleting the name '%s' from the Phone Book.\n",
           familyName);
}

// Function to call when printing an empty Phone Book.
void printPhoneBookEmpty(void) {
    printf("\nThe Phone Book is empty.\n");
}

// Function to call to print a title when the entire Phone Book is printed.
void printPhoneBookTitle(void) {
    printf("\nMy Personal Phone Book: \n");
}

// Add your functions below this line.

Node *createNode(char *familyName,char *firstName,char *address,char *phoneNumber){
Node *newNode = (Node *) malloc(sizeof(Node));
if(newNode != NULL){
newNode->familyName = familyName;
newNode->firstName = firstName;
newNode->address = address;
newNode->phoneNumber = phoneNumber;        
newNode->next = NULL;
}
return newNode;
}