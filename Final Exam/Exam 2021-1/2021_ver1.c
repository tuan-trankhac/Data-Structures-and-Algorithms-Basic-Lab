#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 4
#define DAY 15
typedef struct day
{
    double open;
    double close;
    double digit;
} day;
typedef struct Node
{
    char id[MAX]; // co 3 ky tu chi gom chu cai va so
    day Day[11];
    int index;
    struct Node *left;
    struct Node *right;
} Node;
Node *root;
int N; // so ma co phieu

void load(void);
void find_by_id(void);
void find_up(void);
void find_max(void);
void quit(void);

void menu(void)
{
    int n;
    printf("\n---------------MENU---------------\n");
    printf("1.Doc file\n");
    printf("2.Tim theo ma chung khoan\n");
    printf("3.Tim nhung ma chung khoan co xu huong tang\n");
    printf("4.Tim ma co so ngay tang lon nhat\n");
    printf("5.Thoat chuong trinh\n");
    printf("Enter your number of option you want to: ");
    scanf("%d", &n);
    switch (n)
    {
    case 1:
        load();
        break;
    case 2:
        find_by_id();
        break;
    case 3:
        find_up();
        break;
    case 4:
        find_max();
        break;
    case 5:
        quit();
        exit(0);
        break;
    default:
        printf("This function does not exist\n");
        break;
    }
}

Node *makeNode(char *id, double open, double close)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->index = 0;
    strcpy(p->id, id);
    p->Day[0].open = open;
    p->Day[0].close = close;
    p->Day[0].digit = close - open;
    p->left = NULL;
    p->right = NULL;
    p->index++;
    return p;
}

Node *insert(Node *r, char *id, double open, double close)
{
    if (r == NULL)
        return makeNode(id, open, close);
    int c = strcmp(r->id, id);
    if (c == 0)
    {
        return r;
    }
    else if (c < 0)
    {
        r->right = insert(r->right, id, open, close);
        return r;
    }
    else
    {
        r->left = insert(r->left, id, open, close);
        return r;
    }
}

Node *find(Node *r, char *id)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->id, id);
    if (c == 0)
        return r;
    if (c < 0)
        return find(r->right, id);
    return find(r->left, id);
}
void inOrder(Node *r)
{
    if (r == NULL)
        return;
    inOrder(r->left);
    printf("%s: ", r->id);
    double sum = 0.0;
    for (int i = 0; i < 10; i++)
        sum += r->Day[i].digit;
    printf("%-10.3lf\n", sum / 10.0);
    inOrder(r->right);
}

void load_file(void)
{
    FILE *f = fopen("data.txt", "r");
    if (f == NULL)
        printf("File not found\n");
    root = NULL;
    fscanf(f, "%d", &N);
    while (!feof(f))
    {
        double open;
        double close;
        char id[MAX];
        fscanf(f, "%s%lf%lf", id, &open, &close);
        Node *temp = find(root, id);
        if (temp == NULL)
            root = insert(root, id, open, close);
        else
        {
            temp->Day[temp->index].open = open;
            temp->Day[temp->index].close = close;
            temp->Day[temp->index].digit = close - open;
            temp->index++;
        }
    }
    fclose(f);
}
void load()
{
    load_file();
    inOrder(root);
    menu();
}
double find_Max_c(Node *r)
{
    double Max = 0.0;
    for (int i = 0; i < 10; i++)
        if (r->Day[i].close > Max)
            Max = r->Day[i].close;
    return Max;
}
double find_Min_c(Node *r)
{
    double Min = 1000000.0;
    for (int i = 0; i < 10; i++)
        if (r->Day[i].close < Min)
            Min = r->Day[i].close;
    return Min;
}
void find_by_id()
{
    char id[MAX];
    printf("Nhap id: ");
    scanf("%s", id);
    Node *temp = find(root, id);
    if (temp == NULL)
        printf("khong tim thay\n");
    else
    {
        printf("Gia dong cua lon nhat la: %.3lf\n", find_Max_c(temp));
        printf("Gia dong cua nho nhat la: %.3lf\n", find_Min_c(temp));
    }
    menu();
}
void find_up_c(Node *r)
{
    if (r == NULL)
        return;
    find_up_c(r->left);
    for (int i = 0; i < 10; i++)
    {
        if (r->Day[i].digit > 0 && r->Day[i + 1].digit > 0)
            printf("%s\n", r->id);
        break;
    }
    find_up_c(r->right);
}
void find_up()
{
    find_up_c(root);
    menu();
}
int Max_count = 0;

void Count(Node *r)
{
    if (r == NULL)
        return;
    Count(r->left);
    int count = 0;
    for (int i = 0; i < 10; i++)
    {
        if (r->Day[i].digit > 0)
            count++;
    }
    if (count > Max_count)
    {
        Max_count = count;
    }
    Count(r->right);
}
#define SM 256
int j = 0;
Node *Max_c[SM];
void Count_c(Node *r)
{
    if (r == NULL)
        return;
    Count_c(r->left);
    int count = 0;
    for (int i = 0; i < 10; i++)
    {
        if (r->Day[i].digit > 0)
            count++;
    }
    if (count == Max_count)
    {
        Max_count = count;
        Max_c[j] = r;
        j++;
    }
    Count_c(r->right);
}
void find_max()
{
    Count(root);
    Count_c(root);
    printf("Ma co so ngay tang lon nhat:\n");
    for (int i = 0; i < j; i++)
    {
        printf("%s\n", Max_c[i]->id);
    }
    printf("So lon nhat do la: %d\n", Max_count);
    menu();
}
void quit()
{
    printf("Tran Khac Tuan - 20200554\n");
}

int main(int argc, char const *argv[])
{
    menu();
    return 0;
}
