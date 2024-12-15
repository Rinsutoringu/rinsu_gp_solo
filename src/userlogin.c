#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>



/*
##############################################
这个函数用来完成用户的登录操作
先读取配置文件中的账号密码
然后与用户输入的账号密码进行按对匹配
如果任意对匹配上后，返回0
匹配不上，返回1
##############################################
*/

int userlogin()
{

    char* arr[10];
    int i = 0;
    char* line = NULL;
    char buffer[100] = {0};
    // 先从文件中读取全部用户名和密码
    FILE *file;
    file = fopen("../name_and_password.txt", "r");
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
        line = (char *)malloc((strlen(buffer)+1)*sizeof(char));
        strcpy(line, buffer);
        getline[n] = line;
    }
    
    // 进行字符串切割
    for (int n = 0; n < i; n++)
    {
        username[n] = strtok(getline[n], " ");
        password[n] = strtok(NULL, " ");
        
    }
    
    char input_username[20] = {0};
    char input_password[20] = {0};
    printf("please input your username\n");
    scanf("%s", input_username);
    printf("please input your password\n");
    scanf("%s", input_password);

    for (int n = 0; n < i; n++)
    {
        if (strcmp(input_username, username[n]) == 0)
        {
            return 0;
        }
        return 1;
    }
    return 0;
}