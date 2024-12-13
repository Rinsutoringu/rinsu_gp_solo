#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int userlogin()
{
    char* arr[10];
    int i = 0;
    char* line = NULL;
    char buffer[100] = {0};
    // 先从文件中读取全部用户名和密码
    FILE *file;
    file = fopen("name_and_password.txt", "r");
    if (file == NULL)
    {
        printf("file open error\n");
        return 1;
    }
    // 获取文件行数
    while (fgets(buffer, 100, file) != NULL)
    {
        i++;
    }

    // 重置文件读写指针
    fseek(file, 0, SEEK_SET);
    
    // 创建存储文件内每一行字符串的数组
    char* getline[i];
    char* username[i];
    char* password[i];


    // 获取存储文件每一行的字符串指针
    for (int n = 0; n < i; n++)
    {
        fgets(buffer, 100, file);
        buffer[strcspn(buffer, "\n")] = '\0';
        // 现在把文件的第一行读进了一个固定长度字符型数组里面
        line = malloc((strlen(buffer)+1)*sizeof(char));
        strcpy(line, buffer);
        getline[n] = line;
    }
    
    // 进行字符串切割
    for (int n = 0; n < i; n++)
    {
        username[n] = strtok(getline[n], " ");
        password[n] = strtok(NULL, " ");
        
    }
    
    for (int n = 0; n < i; n++)
    {
        // printf("line is%s, ");
        printf("UserName is %s, PassWord is %s\n", username[n], password[n]);
    }
    
    
    for (int n = 0; n < i; n++)
    {
        free(getline[i]);
    }
    

    printf("Please enter your username and password.");

}

int main(int argc, char const *argv[])
{
    userlogin();
    
    return 0;
}
