#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX 100
typedef struct Data
{
    char username[256]; // it nhat 6 ky tu khong co dau cach
    char password[256]; // khong co dau cach
    double diem;
} Infor;
Infor User[MAX];
// typedef struct Member
// {
//     Infor information;
//     struct Member *right;
//     struct Member *left;
// }User;

// User *root;
int count = 1;
void log_in();
void quit();
void menu_main()
{
    int m;
    printf("1. Dang Nhap\n");
    printf("2. Thoat\n");
    scanf("%d", &m);
    switch (m)
    {
    case 1:
        log_in();
        break;
    case 2:
        printf("Exit\n");
        break;
    default:
        break;
    }
}
int n = 0;
void insert(char *name, char *pass, double diem)
{
    int i = n - 1;
    while (i >= 0)
    {
        int c = strcmp(User[i].username, name);
        if (c == 0)
        {
            printf("This name is exists, do not insert\n");
            return;
        }
        else if (c > 0)
        {
            User[i + 1] = User[i];
            i--;
        }
        else
            break;
    }
    i++;
    strcpy(User[i].username, name);
    strcpy(User[i].password, pass);
    User[i].diem = diem;
    n++;
}

void load()
{
    n = 0;
    FILE *f = fopen("sinhvien.txt", "r");
    while (!feof(f))
    {
        char user[256];
        char pass[256];
        double diem;
        fscanf(f, "%s%s%lf", user, pass, &diem);
        insert(user, pass, diem);
    }
    fclose(f);
}
int BinSearch(int low, int high, char *name)
{
    int mid;
    if (low <= high)
    {
        mid = (low + high) / 2;
        if (strcmp(User[mid].username, name) == 0)
            return mid;
        else if (strcmp(User[mid].username, name) > 0)
            return BinSearch(low, mid - 1, name);
        else
            return BinSearch(mid + 1, high, name);
    }
    else
        return -1;
}
void grade_student(int index);
void change_pass(int index);
void write_file(int index);

void menu_student(int index)
{
    int m;
    printf("1. Diem cua sinh vien\n");
    printf("2. Thay doi mat khau\n");
    printf("3. Ghi lai thong tin tren file va thoat khoi menu con\n");
    scanf("%d", &m);
    switch (m)
    {
    case 1:
        grade_student(index);
        break;
    case 2:
        change_pass(index);
        break;
    case 3:
        write_file(index);
        break;
    default:
        break;
    }
}
void grade_student(int index)
{
    printf("Diem cua sinh vien la: %.1lf\n", User[index].diem);
    menu_student(index);
}
bool check_space(char *pass)
{
    for (int i = 0; i < strlen(pass); i++)
        if (isspace(pass[i]))
            return false;
    return true;
}
void change_pass(int index)
{
    char newpass[256];
    char c;
    int i = 0;
    int len = 0;
    int check = 1;
    do
    {
        check = 1;
        printf("Nhap mat khau moi: ");
        fflush(stdin);
        fgets(newpass, 256, stdin);
        newpass[strlen(newpass) - 1] = '\0';
        fflush(stdin);
        if (strlen(newpass) < 6 || check_space(newpass) == false)
        {
            printf("Error\n");
            check = 0;
        }
    } while (check == 0);

    char temp[256];
    int j = 0;
    do
    {
        check = 1;
        printf("Nhap lai mat khau moi: ");
        fflush(stdin);
        fgets(temp, 256, stdin);
        temp[strlen(temp) - 1] = '\0';
        fflush(stdin);
        if (strcmp(temp, newpass) != 0)
        {
            printf("Error\n");
            check = 0;
        }
    } while (strcmp(temp, newpass) != 0);
    strcpy(User[index].password, newpass);
    menu_student(index);
}
void write_file(int index)
{
    FILE *f = fopen("sinhvien.txt", "w+");
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%s\t%s\t%.1lf\n", User[i].username, User[i].password, User[i].diem);
    }
    fclose(f);
    // menu_main();
}
void insert_more();
void display_student();
void remove_student();
void ad_write();
void menu_admin()
{
    int m;
    printf("1. Them mot sinh vien vao he thong\n");
    printf("2. In danh sach sinh vien\n");
    printf("3. Xoa sinh vien\n");
    printf("4. Ghi lai thong tin len file va thoat menu con\n");
    scanf("%d", &m);
    switch (m)
    {
    case 1:
        insert_more();
        break;
    case 2:
        display_student();
        break;
    case 3:
        remove_student();
        break;
    case 4:
        ad_write();
        break;
    default:
        break;
    }
}
void insert_more()
{
    char name[256];
    char pass[256];
    double diem;
    int check = 1;
    printf("Nhap username, password, diem:\n");
    do
    {
        check = 1;
        fflush(stdin);
        fgets(name, 256, stdin);
        name[strlen(name) - 1] = '\0';
        fflush(stdin);
        if (check_space(name) == false)
        {
            printf("Error\n");
            check = 0;
        }
    } while (check == 0);

    do
    {
        scanf("%s", pass);
    } while (strlen(pass) < 6 || check_space(pass) == false);
    scanf("%lf", &diem);
    insert(name, pass, diem);
    printf("Nhap thanh cong\n");
    menu_admin();
}
void display_student()
{
    for (int i = 0; i < n; i++)
        if (strcmp(User[i].username, "Admin") != 0)
            printf("%-10s%-10s%-10.1lf\n", User[i].username, User[i].password, User[i].diem);
    menu_admin();
}
void remove_student()
{
    char name[256];
    printf("Nhap ten can xoa: ");
    scanf("%s", name);
    if (strcmp(name, "Admin") == 0)
        printf("Khong the xoa user nay\n");
    else
    {
        int index = BinSearch(0, n - 1, name);
        printf("Thong tin cua sinh vien can xoa:\n");
        printf("%-10s%-10s%-10.1lf\n", User[index].username, User[index].password, User[index].diem);
        for (int i = index; i < n; i++)
            User[i] = User[i + 1];
        n--;
    }
    menu_admin();
}
void ad_write()
{
    FILE *f = fopen("sinhvien.txt", "w+");
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%s\t%s\t%lf\n", User[i].username, User[i].password, User[i].diem);
    }
    fclose(f);
    // menu_main();
}
void log_in()
{
    ++count;
    char username[256];
    char pass[256];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", pass);
    int index = BinSearch(0, n - 1, username);
    if (index == -1 && count < 4)
        log_in();
    if (index != -1 && count < 4)
    {
        if (strcmp(pass, User[index].password) == 0)
        {
            if (strcmp(username, "Admin") == 0)
                menu_admin();
            else
                menu_student(index);
            menu_main();
        }
        else
            log_in();
    }
    return;
}
int main(int argc, char const *argv[])
{
    load();
    menu_main();
    return 0;
}