#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 256
typedef struct node
{
    char key[256], value[256];
    struct node *left;
    struct node *right;
} node;
node *root;
node *makeNode(char *key, char *value)
{
    node *newnode = (node *)malloc(sizeof(node));
    if (newnode == NULL)
        return NULL;
    strcpy(newnode->key, key);
    strcpy(newnode->value, value);
    return newnode;
}
node *find(node *r, char *key)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->key, key);
    if (c == 0)
        return r;
    if (c < 0)
        return find(r->right, key);
    return find(r->left, key);
}
node *insert(node *r, char *key, char *value)
{
    if (r == NULL)
        return makeNode(key, value);
    int c = strcmp(key, r->key);
    if (c > 0)
    {
        r->right = insert(r->right, key, value);
        return r;
    }
    else
    {
        r->left = insert(r->left, key, value);
        return r;
    }
}
node *change(node *r, char *key)
{
    char answer;
    printf("This word exist in dict\nDo u want to change meaning of word?\n");
    fflush(stdin);
    scanf("%c", &answer);
    if (answer == 'y')
    {
        char newmean[256];
        printf("New meaning of this word is: ");
        scanf("%s", newmean);
        strcpy(find(r, key)->value, newmean);
        return r;
    }
    else
        return r;
}
void Them_Sua()
{
    char word[256];
    printf("Word in English is: ");
    scanf("%s", word);
    node *temp = find(root, word);
    if (temp == NULL)
    {
        char value[256];
        printf("It's meaning: ");
        scanf("%s", value);
        insert(root, word, value);
    }
    else
        change(root, word);
}
void load(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        printf("Load data -> file not found\n");
    root = NULL;
    while (!feof(f))
    {
        char key[256], value[256];
        fscanf(f, "%s%s", key, value);
        root = insert(root, key, value);
        printf("%-8s%-8s\n", key, value);
    }
    fclose(f);
}
void NapTuDien()
{
    char file[256];
    scanf("%s", file);
    load(file);
}
void inOrder(node *r)
{
    if (r == NULL)
        return;
    inOrder(r->left);
    printf("%s,%s\n", r->key, r->value);
    inOrder(r->right);
}
void NoiDungTuDien()
{
    inOrder(root);
    printf("\n");
}
void Dich_cau()
{
printf("Sentence:");
    fflush(stdin);
    char c;
    char **p = NULL;
    p = (char **)malloc(256 * sizeof(char *));
    for (int i = 0; i < 256; i++)
    {
        p[i] = (char *)malloc(256 * sizeof(char));
    }
    int k = 0;
    int i = 0;
    while ((c = getchar()) != '\n')
    {
        if (c != ' ')
            p[k][i++] = tolower(c);
        else
        {
            i = 0;
            k++;
        }
    }
    for (int j = 0; j <= k; j++)
    {
        node *temp = find(root, p[j]);
        if (temp == NULL)
            printf(" <Thieu tu> ");
        else
        {
            printf("%s ", temp->value);
        }
    }
    for (int i = 0; i <= k; i++)
    {
        free(p[i]);
    }
    free(p);
}
void Dich_caitien()
{
    printf("Sentence:");
    fflush(stdin);
    char c;
    char **p = NULL;
    p = (char **)malloc(256 * sizeof(char *));
    for (int i = 0; i < 256; i++)
    {
        p[i] = (char *)malloc(256 * sizeof(char));
    }
    int k = 0;
    int i = 0;
    while ((c = getchar()) != '\n')
    {
        if (c != ' ')
            p[k][i++] = tolower(c);
        else
        {
            i = 0;
            k++;
        }
    }
    int j = 0;
    for (; j <= k; j++)
    {
        node *temp;
        if ((temp = find(root, p[j])) == NULL)
        {
            printf("Bo sung them tu %s vao tu dien\n", p[j]);
            Them_Sua();
        }
        if ((temp = find(root, p[j])) != NULL)
        {
            printf("%s ", temp->value);
        }
    }
    for (int i = 0; i <= k; i++)
    {
        free(p[i]);
    }
    free(p);
}
void freeTree(node *r)
{
    if (r == NULL)
        return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}
void Quit()
{
    freeTree(root);
}
int main()
{
    int choice;
    char c;
    do
    {
        printf("\n1.Nap tu dien");
        printf("\n2.Noi dung tu dien");
        printf("\n3.Them/Sua tu");
        printf("\n4.Dich Cau");
        printf("\n5.Quit ");
        printf("\nPress number to choose: ");
        scanf("%d", &choice);
        fflush(stdin);
        if (choice == 5)
        {
            Quit();
            printf("\nExit programming");
            break;
        }
        switch (choice)
        {
        case 1:
            NapTuDien();
            break;
        case 2:
            NoiDungTuDien();
            break;
        case 3:
            Them_Sua();
            break;
        case 4:
            Dich_caitien();
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
}
