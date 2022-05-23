#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 41
typedef struct data
{
    char loc[MAX];
    int hour;
    int minute;
} Data;

typedef struct node
{
    Data database;
    struct node *next;
    struct node *prev;
} Node;

Node *cur;
Node *tail;

void initlist(void)
{
    cur = NULL;
    tail = NULL;
}
int listEmpty(void)
{
    return cur == NULL && tail == NULL;
}
Node *makeNode(Data v)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->database.hour = v.hour;
    p->database.minute = v.minute;
    strcpy(p->database.loc, v.loc);
    p->next = NULL;
    p->prev = NULL;
    return p;
}
Node *insertLast(Data x)
{
    Node *p = makeNode(x);
    if (listEmpty())
    {
        cur = p;
        tail = p;
        return cur;
    }
    p->prev = tail;
    tail->next = p;
    tail = p;
    return cur;
}
void load_data(void)
{
    char file[256];
    scanf("%s", file);
    FILE *f = fopen(file, "r");
    if (f == NULL)
        printf("File dosen't exist\n");
    initlist();
    bool check = false;
    while (!feof(f))
    {
        check = false;
        Data x;
        fscanf(f, "%s%d%d", x.loc, &x.hour, &x.minute);
        cur = insertLast(x);
        printf("%-50s%-10d%-10d\n", x.loc, x.hour, x.minute);
        check = true;
    }
    if (check == true)
        printf("Doc thanh cong du lieu\n");
    fclose(f);
}

void travel_history(void)
{
    for (Node *p = cur; p != NULL; p = p->next)
        printf("%-50s%-10d%-10d\n", p->database.loc, p->database.hour, p->database.minute);
}

void search_by_loc(void)
{
    char location[MAX];
    printf("Enter a location: ");
    scanf("%s", location);
    bool check = false;
    for (Node *p = cur; p != NULL; p = p->next)
    {
        if (check == true)
            printf(" ,");
        check = false;
        if (strcmp(p->database.loc, location) == 0)
        {
            check = true;
            printf("%d:%d", p->database.hour, p->database.minute);
        }

    }
    if (check != true)
        printf("\nBan chua toi dia diem do\n");
}

void search_by_time(void)
{
    int hour, min;
    do
    {
        scanf("%d%d", &hour, &min);
    } while (hour < 0 || hour >= 24 || min < 0 || min >= 60);
    bool check = false;
    for (Node *p = cur; p != NULL; p = p->next)
    {
        if (p->database.hour == hour && p->database.minute == min)
        {
            check = true;
            printf("%s\n", p->database.loc);
            break;
        }
    }
    if (check != true)
        printf("KHONG tim thay lich su di chuyen!\n");
}

void check_lastest_trace(void)
{
    printf("Information of patient: ");
    char loc[MAX];
    int hour, min;
    scanf("%s%d%d", loc, &hour, &min);
    bool check = false;
    for (Node *p = cur; p != NULL; p = p->next)
    {
        if (strcmp(p->database.loc, loc) == 0)
        {
            if (p->database.hour > hour ||( p->database.hour == hour&&p->database.minute >= min))
            {   
                check = true;
                printf("Ban co kha nang bi lay Covid, can phai khai bao y te ngay lap tuc!\n");
                break;
            }
        }
    }
    if(check==false) printf("Lich su di chuyen cua ban OK\n");
}

void Quit(void)
{
    Node *p = cur;
    while (p != NULL)
    {
        Node *np = p->next;
        free(p);
        p = np;
    }
}

int main(int argc, char const *argv[])
{
    int choice;
    char c;
    do
    {
        printf("\n1.Nap du lieu log lich su di chuyen");
        printf("\n2.In lich su di chuyen");
        printf("\n3.Tim kiem lich su di chuyen theo dia diem");
        printf("\n4.Tim kiem thong tin di chuyen theo thoi gian");
        printf("\n5.Kiem tra truy vet moi nhat");
        printf("\n6.Quit ");
        printf("\nPress number to choose: ");
        scanf("%d", &choice);
        fflush(stdin);
        if (choice == 6)
        {
            Quit();
            printf("\nExit programming");
            break;
        }
        switch (choice)
        {
        case 1:
            load_data();
            break;
        case 2:
            travel_history();
            break;
        case 3:
            search_by_loc();
            break;
        case 4:
            search_by_time();
            break;
        case 5:
            check_lastest_trace();
            break;
        default:
            printf("\nThis function does not exist\n");
            break;
        }
        printf("\nDo you want to continue the programming?\nEnter y/n: ");
        fflush(stdin);
        scanf("%c", &c);
        fflush(stdin);
        if (c == 'y')
            choice = -1;
        else
            break;
    } while (choice == -1);
    return 0;
}
