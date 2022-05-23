#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 256
typedef struct Sport
{
    char id[11]; // toi da 10 ky tu va khong co space
    int score;
    struct Sport *left;
    struct Sport *right;
} Soccer;
Soccer *root;
int count = 0;
Soccer *makeNode(char *id, int score)
{
    count++;
    Soccer *p = (Soccer *)malloc(sizeof(Soccer));
    strcpy(p->id, id);
    p->score = score;
    p->left = NULL;
    p->right = NULL;
    printf("Nut thu %d co dia chi la %p\n", count, p);
    return p;
}

Soccer *insert(Soccer *r, char *id, int score)
{
    if (r == NULL)
        return makeNode(id, score);
    int c = strcmp(r->id, id);
    if (c == 0)
    {
        r->score += score;
        return r;
    }
    else if (c < 0)
    {
        r->right = insert(r->right, id, score);
        return r;
    }
    else
    {
        r->left = insert(r->left, id, score);
        return r;
    }
}
Soccer *find_id(Soccer *r, char *id)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->id, id);
    if (c == 0)
        return r;
    if (c < 0)
        return find_id(r->right, id);
    return find_id(r->left, id);
}
Soccer *findMin(Soccer *r)
{
    if (r == NULL)
        return NULL;
    Soccer *lmin = findMin(r->left);
    if (lmin != NULL)
        return lmin;
    return r;
}
Soccer *remove_id(Soccer *r, char *id)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->id, id);
    if (c > 0)
        r->left = remove_id(r->left, id);
    else if (c < 0)
        r->right = remove_id(r->right, id);
    else
    {
        if (r->left != NULL && r->right != NULL)
        {
            Soccer *tmp = findMin(r->right);
            strcpy(r->id, tmp->id);
            r->score = tmp->score;
            r->right = remove_id(r->right, tmp->id);
        }
        else
        {
            Soccer *tmp = r;
            if (r->left == NULL)
                r = r->right;
            else
                r = r->left;
            free(tmp);
        }
    }
    return r;
}
void make_tree();
void result(Soccer *r);
void searching();
void down_rank();
void output();
void menu()
{
    int n;
    printf("\n---------------MENU---------------\n");
    printf("1.Tao cay\n");
    printf("2.Ket qua\n");
    printf("3.Tim kiem\n");
    printf("4.Xuong hang\n");
    printf("5.Xuat file\n");
    printf("Enter your number of option you want to: ");
    scanf("%d", &n);
    switch (n)
    {
    case 1:
        make_tree();
        break;
    case 2:
        result(root);
        break;
    case 3:
        searching();
        break;
    case 4:
        down_rank();
        break;
    case 5:
        output();
        exit(0);
        break;
    default:
        printf("This function does not exist\n");
        break;
    }
}
void make_tree()
{
    FILE *f = fopen("Bong.txt", "r");
    if (f == NULL)
        printf("Load data -> file not found\n");
    root = NULL;
    while (!feof(f))
    {
        char id1[MAX];
        char id2[MAX];
        int num1;
        int num2;
        int score1 = 0;
        int score2 = 0;
        fscanf(f, "%s%s%d%d", id1, id2, &num1, &num2);
        if (num1 > num2)
            score1 = 3;
        else if (num1 < num2)
            score2 = 3;
        else
        {
            score1 = 1;
            score2 = 1;
        }
        root = insert(root, id1, score1);
        root = insert(root, id2, score2);
    }
    fclose(f);
    menu();
}
void result(Soccer *r)
{
    if (r == NULL)
        return;
    result(r->left);
    printf("%-10s", r->id);
    result(r->right);
    menu();
}
void searching()
{
    char id[11];
    scanf("%s", id);
    if (find_id(root, id) == NULL)
        printf("Khong co doi bong nay!\n");
    else
        printf("Diem cua doi %s la: %d ", id, find_id(root, id)->score);
    menu();
}
char delete[MAX][MAX];
int dem=0;
void check_down(Soccer *r, int score)
{
    if (r == NULL)
        return;
    check_down(r->left, score);
    if (r->score < score)
    {
        printf("%-8s", r->id);
        strcpy(delete[dem++],r->id);
        count--;
    }
    check_down(r->right, score);
}
void down_rank()
{
    int X;
    printf("Nhap X: ");
    scanf("%d", &X);
    printf("Doi bong bi xuong hang la: ");
    check_down(root,X);
    for(int i=0; i<=dem;i++)
        root= remove_id(root,delete[i]);
    printf("\nCay moi la: ");
    result(root);
    menu();
}
void display(Soccer *r, FILE *f)
{
    if (r == NULL)
        return;
    display(r->left,f);
    fprintf(f,"%-10s%-5d\n", r->id,r->score);
    display(r->right,f);
}
void output()
{
    FILE *f = fopen("KetQua.txt","w+");
    display(root,f);
}
int main(int argc, char const *argv[])
{
    menu();
    return 0;
}