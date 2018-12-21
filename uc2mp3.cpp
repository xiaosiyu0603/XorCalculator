#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char pathstring[_MAX_PATH];

int main(int argc, char **argv)
{

    char *inputfilename, *outputfilename;
    if (argc < 2)
    {
        inputfilename = new pathstring;
        printf("输入文件名：（限制%d个字符）\n", _MAX_PATH);
        gets(inputfilename);
    }
    else
    {
        inputfilename = argv[1];
    }

    printf("%s\n", inputfilename);

    if (strlen(inputfilename) == 0)
    {
        printf("错误的文件名\n");
        return 1;
    }
    else
    {
        char drive[_MAX_DRIVE];
        char dir[_MAX_DIR];
        char fname[_MAX_FNAME];
        char ext[_MAX_EXT];
        outputfilename = new pathstring;

        _splitpath(inputfilename, drive, dir, fname, ext);
        _makepath(outputfilename, drive, dir, fname, ".mp3");
        printf("输入文件：%s\n输出文件：%s\n", inputfilename, outputfilename);
    }

    FILE *ucinput = fopen(inputfilename, "rb"),
         *mp3output = fopen(outputfilename, "wb");

    if (ucinput == NULL)
    {
        printf("文件%s无法打开", inputfilename);
    }
    if (mp3output == NULL)
    {
        printf("文件%s无法打开", outputfilename);
    }

    int temp;
    while ((temp = getc(ucinput)) != EOF)
    {
        putc(temp ^ 0xa3, mp3output);
    }
    fclose(ucinput);
    fclose(mp3output);

    return 0;
}
