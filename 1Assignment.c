#include <stdio.h>
#include <string.h>

#define SIZE 20     /* غيّرها إلى 5 لاختبار Overflow */

typedef struct
{
    char buffer[SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;


/* init the buffer */
void init(CircularBuffer *cb)
{
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}


/* check if full */
int isFull(CircularBuffer *cb)
{
    return cb->count == SIZE;
}


/* check if empty */
int isEmpty(CircularBuffer *cb)
{
    return cb->count == 0;
}


/* write from the buffer */
void writeBuffer(CircularBuffer *cb, char data)
{
    if (isFull(cb))
    {
        printf("Buffer Overflow: %c\n", data);
        return;
    }

    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count++;
}


/* read from the buffer */
char readBuffer(CircularBuffer *cb)
{
    char data;

    if (isEmpty(cb))
    {
        printf("Buffer Underflow\n");
        return '\0';
    }

    data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE;
    cb->count--;

    return data;
}


int main()
{
    CircularBuffer cb;
    char name[50];
    char fullText[100];
    int i;
    char ch;

    init(&cb);

    /* enteer the name */
    printf("Enter your name: ");
    scanf("%s", name);

    /* add to ESY-CE */
    strcpy(fullText, name);
    strcat(fullText, "ESY-CE");

    printf("\nText after adding suffix: %s\n", fullText);

    /* load the text in the box */
    printf("\nWriting to buffer...\n");

    for (i = 0; i < strlen(fullText); i++)
    {
        writeBuffer(&cb, fullText[i]);
    }

    /* read the text from the box */
    printf("\nReading from buffer:\n");

    while (!isEmpty(&cb))
    {
        ch = readBuffer(&cb);
        printf("%c", ch);
    }

    printf("\n");

    /* the buffer is empty? */
    if (isEmpty(&cb))
    {
        printf("\nBuffer is now empty.\n");
    }

    return 0;
}