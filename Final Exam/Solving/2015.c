#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_L 256

typedef struct Santa
{
    int id;
    char toy[31];
    struct Santa *left;
    struct Santa *right;
} Santa;
Santa *root;
Santa *makeNode(int id, char *toy)
{
    Santa *p = (Santa *)malloc(sizeof(Santa));
    p->id = id;
    strcpy(p->toy, toy);
    p->left = NULL;
    p->right = NULL;
    return p;
}

Santa *insert(Santa *r, int id, char *toy)
{
    if (r == NULL)
        return makeNode(id, toy);
    int c = strcmp(r->id, id);
    if (c == 0)
    {
        printf("Student %s exists do not insert\n", id);
        return r;
    }else if(c<0){
        r->right = insert(r->right, id, toy);
        return r;
    }else{
        r->left = insert(r->left, id, toy);
        return r;
    }
}

void load(char *filename){
    FILE *f = fopen(filename, "r");
    if(f==NULL) printf("Load data -> file not found\n");
    root = NULL;
    while(!feof(f)){
        int id;char toy[MAX_L];
        fscanf(f,"%d%s", id, toy);
        root = insert(root, id, toy);
    }
    fclose(f);
}

void processLoad(){
    char file[MAX_L];
    scanf("%s",file);
    load(file);
}

Santa *find(Santa *r, int *id){
    if(r==NULL) return NULL;
    if(r->id==id) return r;
    if(r->id<id) return find(r->right, id);
    return find(r->left, id);
}

void processFind(){
    char id[MAX_L];
    scanf("%s", id);
    if(find(root, id) == NULL) printf("Can not find");
    else printf("Found %s with toy : %s ", id, find(root,id)->toy);
}

Santa *findMin(Santa *r){
    if(r==NULL) return NULL;
    Santa *lmin = findMin(r->left);
    if(lmin!=NULL) return lmin;
    return r;
}

void processfindMin(){
    Santa *min = findMin(root);
    printf("Min of tree 's information : %s with %s", min->id, min->toy);
}

Santa *removeStudent(Santa *r, int id){
    if(r==NULL) return NULL;
    if(r->id>id) r->left = removeStudent(r->left, id);
    else if(r->id<id) r->right = removeStudent(r->right, id);
    else{
        if(r->left!=NULL && r->right != NULL){
            Santa *tmp = findMin(r->right);
            strcpy(r->id, tmp->id);
            strcpy(r->toy, tmp->toy);
            r->right = removeStudent(r->right, tmp->id);
        }else{
            Santa *tmp = r;
            if(r->left==NULL) r = r->right;
            else r = r->left;
            free(tmp);
        }
    }
    return r;
}

void freeTree(Santa *r){
    if(r==NULL) return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}

void inOrder(Santa *r){
    if(r==NULL) return;
    inOrder(r->left);
    printf("%s,%s\n",r->id, r->toy);
    inOrder(r->right);
}

void inOrderF(Santa *r, FILE *f){
    if(r==NULL) return;
    inOrderF(r->left, f);
    fprintf(f,"%s  %s\n", r->id, r->toy);
    inOrderF(r->right,f);
}
int main(int argc, char const *argv[])
{
    processLoad();
    return 0;
}
