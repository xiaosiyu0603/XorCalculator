#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char pathstring[_MAX_PATH];

void transform2mp3(char *inputfilename)
{
    char *outputfilename;

    if (strlen(inputfilename) == 0)
    {
        printf("������ļ���\n");
        return;
    }

    {
        char drive[_MAX_DRIVE];
        char dir[_MAX_DIR];
        char fname[_MAX_FNAME];
        char ext[_MAX_EXT];
        outputfilename = new pathstring;

        _splitpath(inputfilename, drive, dir, fname, ext);
        _makepath(outputfilename, drive, dir, fname, ".mp3");
        printf("���룺%s\n�����%s\n", inputfilename, outputfilename);
    }

    FILE *ucinput = fopen(inputfilename, "rb"),
         *mp3output = fopen(outputfilename, "wb");

    if (ucinput == NULL)
    {
        printf("�ļ�%s�޷���", inputfilename);
        return;
    }
    if (mp3output == NULL)
    {
        printf("�ļ�%s�޷���", outputfilename);
        return;
    }

    int temp;
    while ((temp = getc(ucinput)) != EOF)
    {
        putc(temp ^ 0xa3, mp3output);
    }
    fclose(ucinput);
    fclose(mp3output);

    printf("%sת�����\n\n", inputfilename);

    return;
}

int main(int argc, char **argv)
{
    char *inputfilename;
    if (argc < 2)
    {
        inputfilename = new pathstring;
        printf("�����ļ�����������%d���ַ���\n", _MAX_PATH);
        gets(inputfilename);
        transform2mp3(inputfilename);
    }
    else
    {
        for (int i = 1; i < argc; i++)
            transform2mp3(argv[i]);
    }

    system("pause");
    return 0;
}
