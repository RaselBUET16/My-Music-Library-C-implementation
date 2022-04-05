//
// APS105 Lab 9
//
// This is a program written to maintain a personal music library,
// using a linked list to hold the songs in the library.
//
// Author: <Your Name Goes Here>
// Student Number: <Your Student Number Goes Here>
//

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_LENGTH = 1024;
// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node
{
    char *artist;
    char *songName;
    char *genre;
    struct node *next;
} Node;

// Declarations of linked list functions
//
// DECLARE YOUR LINKED-LIST FUNCTIONS HERE
//
Node* newNode(char* songName, char* artist, char* genre);
Node* insertNode(Node *head, Node *newNode);
Node* checkDuplicate(Node *head, char *songName);
void deleteNode(Node *node);
Node* deleteSong(Node *node,char* songName);
void printList(Node *head);
// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser(char *prompt, char *s, int arraySize);
void songNameDuplicate(char *songName);
void songNameFound(char *songName);
void songNameNotFound(char *songName);
void songNameDeleted(char *songName);
void artistFound(char *artist);
void artistNotFound(char *artist);
void printMusicLibraryEmpty(void);
void printMusicLibraryTitle(void);

int main(void)
{
    // Declare the head of the linked list.
    //   ADD YOUR STATEMENT(S) HERE
    Node *head = NULL;
    // Announce the start of the program
    printf("Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
                 "P (print), Q (quit).\n");

    char response;
    char input[MAX_LENGTH + 1];
    do
    {
        inputStringFromUser("\nCommand", input, MAX_LENGTH);

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I')
        {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            //   ADD STATEMENT(S) HERE

            // USE THE FOLLOWING STRINGS WHEN PROMPTING FOR DATA:
            char *promptName = "Song name";
            char *promptArtist = "Artist";
            char *promptGenre = "Genre";
            char* songName = malloc(sizeof(char) * MAX_LENGTH);
            char* artist = malloc(sizeof(char) * MAX_LENGTH);
            char* genre = malloc(sizeof(char) * MAX_LENGTH);
            inputStringFromUser(promptName, songName, MAX_LENGTH);
            inputStringFromUser(promptArtist, artist, MAX_LENGTH);
            inputStringFromUser(promptGenre, genre, MAX_LENGTH);
            // Check for duplicate song names
            Node* duplicate=checkDuplicate(head,songName);
            if(duplicate!=NULL){
                songNameDuplicate(songName);
                free(songName);
                free(artist);
                free(genre);
            }
            else{
                Node* node=newNode(songName,artist,genre);
                head=insertNode(head, node);
            }
        }
        else if (response == 'D')
        {
            // Delete a song from the list.

            char *prompt = "\nEnter the name of the song to be deleted";
            char *songName=malloc(sizeof(char)*MAX_LENGTH);
            inputStringFromUser(prompt, songName, MAX_LENGTH);
            // Check if song name is in the list
            Node* duplicate=checkDuplicate(head,songName);
            if(duplicate!=NULL){
                head=deleteSong(head,songName);
                songNameDeleted(songName);
            }
            else{
                songNameNotFound(songName);
            }
            //   ADD STATEMENT(S) HERE
        }
        else if (response == 'S')
        {
            // Search for a song by its name.

            char *prompt = "\nEnter the name of the song to search for";
            char *songName=malloc(sizeof(char)*MAX_LENGTH);
            inputStringFromUser(prompt, songName, MAX_LENGTH);
            // Check if song name is in the list
            Node* duplicate=checkDuplicate(head,songName);
            if(duplicate!=NULL){
                songNameFound(songName);
                printf("\n%s\n%s\n%s\n",duplicate->songName,duplicate->artist,duplicate->genre);
            }
            else{
                songNameNotFound(songName);
            }

            //   ADD STATEMENT(S) HERE
        }
        else if (response == 'P')
        {
            // Print the music library.
            if(head==NULL){
                printMusicLibraryEmpty();
            }
            else{
                printMusicLibraryTitle();
                printList(head);
            }
            //   ADD STATEMENT(S) HERE
        }
        else if (response == 'Q')
        {
            ; // do nothing, we'll catch this below
        }
        else
        {
            // do this if no command matched ...
            printf("\nInvalid command.\n");
        }
    } while (response != 'Q');

    // Delete the entire linked list.
    while(head!=NULL){
        Node* temp=head;
        head=head->next;
        songNameDeleted(temp->songName);
        deleteNode(temp);
    }
    //   ADD STATEMENT(S) HERE

    // Print the linked list to confirm deletion.
    if(head==NULL){
        printMusicLibraryEmpty();
    }
    //   ADD STATEMENT(S) HERE

    return 0;
}

// Support Function Definitions
// create new node
// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char *prompt, char *s, int maxStrLength)
{
    int i = 0;
    char c;

    printf("%s --> ", prompt);
    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;
    s[i] = '\0';
}

// Function to call when the user is trying to insert a song name
// that is already in the personal music library.
void songNameDuplicate(char *songName)
{
    printf("\nA song with the name '%s' is already in the music library.\n"
           "No new song entered.\n",
           songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound(char *songName)
{
    printf("\nThe song name '%s' was found in the music library.\n", songName);
}

// Function to call when a song name was not found in the personal music
// library.
void songNameNotFound(char *songName)
{
    printf("\nThe song name '%s' was not found in the music library.\n",
           songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted(char *songName)
{
    printf("\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void)
{
    printf("\nThe music library is empty.\n");
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void)
{
    printf("\nMy Personal Music Library: \n");
}

// Add your functions below this line.

//   ADD STATEMENT(S) HERE
Node *newNode(char* songName, char* artist, char* genre){
    Node *node = malloc(sizeof(Node));
    node->songName=songName;
    node->artist=artist;
    node->genre=genre;
    node->next = NULL;
    return node;
}
// insert new node into the list
Node* insertNode(Node *head, Node *newNode)
{
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Node *current = head;
        Node *previous = NULL;
        while (current != NULL && strcmp(current->songName, newNode->songName) < 0)
        {
            previous = current;
            current = current->next;
        }
        if (previous == NULL)
        {
            head = newNode;
        }
        else
        {
            previous->next = newNode;
        }
        newNode->next = current;
    }
    return head;
}
Node* checkDuplicate( Node *head, char *songName)
{
    Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->songName, songName) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
void deleteNode(Node *node)
{
    free(node->artist);
    free(node->songName);
    free(node->genre);
    free(node);
}
Node* deleteSong(Node *head,char* songName)
{
    Node *current = head;
    Node *previous = NULL;
    while(current!=NULL){
        if(strcmp(current->songName,songName)==0){
            break;
        }
        previous=current;
        current=current->next;
    }
    if(current==NULL){
        return head;
    }
    if(previous==NULL){
        head=current->next;
    }
    else{
        previous->next=current->next;
    }
    deleteNode(current);
    return head; 
}
void printList(Node* head){
    Node* current=head;
    while(current!=NULL){
        printf("\n%s\n%s\n%s\n",current->songName,current->artist,current->genre);
        current=current->next;
    }
}