#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MIN 9999
int N = 0;

typedef struct Data
{
    int id;
    char name[30];
    int score;
    int win;
    int lose;
} Data;

typedef struct Sport
{
    Data database;
    struct Sport *next;
} Soccer;
Soccer *head;
Soccer *last;
typedef struct round
{
    struct vs
    {
        int teamA;
        int teamB;
    } vs[3];

} round;
round Round[4];
void initlist()
{
    head = NULL;
    last = NULL;
}

int listEmpty()
{
    return head == NULL && last == NULL;
}

Soccer *makeNode(Data x)
{
    Soccer *q = (Soccer *)malloc(sizeof(Soccer));
    q->database.id = x.id;
    q->database.win = x.win;
    q->database.lose = x.lose;
    q->database.score = x.score;
    strcpy(q->database.name, x.name);
    q->next = NULL;
    return q;
}

Soccer *insertHead(Soccer *h, Data x)
{
    Soccer *p;
    p = makeNode(x);
    p->next = h;
    h = p;
    return h;
}
void load(FILE *f)
{
    int count = 0;
    if (f == NULL)
        printf("This file dosen't exist\n");
    fscanf(f, "%d", &N);
    printf("%-8s%-20s%-10s%-15s%-15s\n", "Id", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
    while (1)
    {
        Data x;
        fscanf(f, "%d", &x.id);
        fgets(x.name, 256, f);
        x.name[strlen(x.name) - 1] = '\0';
        for (int i = 0; i < strlen(x.name); i++)
        {
            x.name[i] = x.name[i + 1];
        }
        x.score = 0;
        x.win = 0;
        x.lose = 0;
        head = insertHead(head, x);
        printf("%-8d%-20s%-10d%-15d%-15d\n", x.id, x.name, x.score, x.win, x.lose);
        count++;
        if (count == N)
            break;
    }
}
void display(FILE *f)
{
    if (listEmpty())
        load(f);
    else
    {
        printf("%-8s%-20s%-10s%-15s%-15s\n", "Id", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
        for (Soccer *p = head; p != NULL; p = p->next)
            printf("%-8d%-20s%-10d%-15d%-15d\n", p->database.id, p->database.name, p->database.score, p->database.win, p->database.lose);
    }
}

void schedule(FILE *f)
{
    for (int i = 1; i <= N - 1; i++)
    {
        for (int j = 1; j <= N / 2; j++)
        {
            Round[i].vs[j].teamA = 0;
            Round[i].vs[j].teamB = 0;
        }
    }
    while (!feof(f))
    {

        char vong[256];
        int i;
        fscanf(f, "%s%d", vong, &i);
        printf("%s %d\n", vong, i);
        for (int j = 1; j <= N / 2; j++)
        {
            int id1, id2;
            fscanf(f, "%d%d", &id1, &id2);
            Round[i].vs[j].teamA = id1;
            Round[i].vs[j].teamB = id2;
            for (Soccer *p = head; p != NULL; p = p->next)
            {
                if (p->database.id == id1)
                    printf("%s - ", p->database.name);
            }
            for (Soccer *p = head; p != NULL; p = p->next)
            {
                if (p->database.id == id2)
                    printf("%s\n", p->database.name);
            }
        }
    }
}
// Loai khoang trang truoc va sau - , :
char *space(char *s)
{
    for (int i = 0; i < strlen(s); i++)
        if ((s[i] == ' ' && s[i + 1] == '-') || (s[i - 1] == '-' && s[i] == ' ') || (s[i] == ' ' && s[i + 1] == ':') || (s[i - 1] == ':' && s[i] == ' '))
            for (int j = i; j < strlen(s); j++)
            {
                s[j] = s[j + 1];
            }
    return s;
}
Soccer *find_by_name(char *s)
{
    for (Soccer *q = head; q != NULL; q = q->next)
        if (strcmp(q->database.name, s) == 0)
            return q;
    return NULL;
}
Soccer *find_by_id(int id)
{
    for (Soccer *q = head; q != NULL; q = q->next)
        if (q->database.id == id)
            return q;
    return NULL;
}
void update(FILE *f)
{
    printf("Nhap ket qua tran dau tu vong 1 den vong %d:\n", N - 1);
    for (int i = 1; i <= N - 1; i++)
    {
        printf("Cap nhat ket qua Vong %d:\n", i);
        printf("Vong %d:\n", i);
        for (int j = 1; j <= N / 2; j++)
        {
            Soccer *q0 = find_by_id(Round[i].vs[j].teamA);
            Soccer *q1 = find_by_id(Round[i].vs[j].teamB);
            printf("%s - %s : ", q0->database.name, q1->database.name);
            int result1, result2;
            scanf("%d - %d", &result1, &result2);
            if (result1 - result2 > 0)
            {
                q0->database.score += 3;
                q0->database.win += 1;
                q1->database.lose += 1;
            }
            else if (result1 - result2 < 0)
            {
                q1->database.score += 3;
                q0->database.lose += 1;
                q1->database.win += 1;
            }
            else
            {
                q0->database.score += 1;
                q0->database.win += 1;
                q1->database.score += 1;
                q0->database.win += 1;
            }
        }
    }
    display(f);
}
int min = MIN;
int find_min()
{
    for (Soccer *q = head; q != NULL; q = q->next)
        if (q->database.score < min)
            min = q->database.score;
    return min;
}
Soccer *Remove(Soccer *h, int v)
{

    if (h == NULL)
        return NULL;
    if (listEmpty())
        return NULL;
    if (h->database.score == v)
    {
        printf("%-8d%-20s%-10d%-15d%-15d\n", h->database.id, h->database.name, h->database.score, h->database.win, h->database.lose);
        Soccer *tm = h;
        h = h->next;
        free(tm);
        h = Remove(h, v);
        return h;
    }
    h->next = Remove(h->next, v);
    return h;
}

void statistical(FILE *f)
{
    min = find_min();
    printf("Cac doi co diem thap nhat la:\n");
    printf("%-8s%-20s%-10s%-15s%-15s\n", "Id", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
    head = Remove(head, min);
    printf("Cac doi con lai la:\n");
    display(f);
}
int main(int argc, char const *argv[])
{
    initlist();
    char file[256];
    scanf("%s", file);
    FILE *f = fopen(file, "r");
    int choice;
    char c;
    do
    {
        printf("\n1.In thong tin cac doi bong");
        printf("\n2.In thong tin lich thi dau");
        printf("\n3.Cap nhat ket qua vong dau");
        printf("\n4.Thong ke");
        printf("\n5.Quit ");
        printf("\nPress number to choose: ");
        scanf("%d", &choice);
        fflush(stdin);
        if (choice == 5)
        {
            printf("\nExit programming");
            break;
        }
        switch (choice)
        {
        case 1:
            display(f);
            break;
        case 2:
            schedule(f);
            break;
        case 3:
            update(f);
            break;
        case 4:
            statistical(f);
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
