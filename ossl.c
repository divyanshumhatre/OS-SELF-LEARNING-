#include <stdio.h>
#include <conio.h>
#include <dos.h>

int absVal(int x)
{
    if(x < 0)
        return -x;
    else
        return x;
}

void line(void)
{
    textcolor(CYAN);
    cprintf("\n========================================\n");
    textcolor(WHITE);
}

void animateMove(int from, int to)
{
    int i;

    textcolor(YELLOW);
    cprintf("\nMoving Head: ");

    if(from < to)
    {
        for(i = from; i <= to; i += 5)
        {
            cprintf("%d ", i);
            delay(120);
        }
    }
    else
    {
        for(i = from; i >= to; i -= 5)
        {
            cprintf("%d ", i);
            delay(120);
        }
    }

    textcolor(RED);
    cprintf(" ---> ");

    textcolor(GREEN);
    cprintf("%d\n", to);

    delay(400);
}

void SSTF(int req[], int n, int head)
{
    int visited[20];
    int seek = 0;
    int i, j, index, min, dist;

    for(i = 0; i < 20; i++)
        visited[i] = 0;

    line();
    textcolor(LIGHTMAGENTA);
    cprintf("        SSTF DISK SCHEDULING\n");
    line();

    delay(3000);   /* narration pause */

    for(i = 0; i < n; i++)
    {
        min = 9999;

        for(j = 0; j < n; j++)
        {
            if(!visited[j])
            {
                dist = absVal(head - req[j]);

                if(dist < min)
                {
                    min = dist;
                    index = j;
                }
            }
        }

        visited[index] = 1;

        animateMove(head, req[index]);

        seek += min;
        head = req[index];
    }

    textcolor(LIGHTCYAN);
    cprintf("\nTotal Seek Time = %d\n", seek);

    delay(4000);
}

void LOOK(int req[], int n, int head)
{
    int i, j, temp;
    int seek = 0;

    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(req[i] > req[j])
            {
                temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }
        }
    }

    line();
    textcolor(LIGHTMAGENTA);
    cprintf("        LOOK DISK SCHEDULING\n");
    line();

    delay(3000);

    for(i = 0; i < n; i++)
    {
        if(req[i] >= head)
        {
            animateMove(head, req[i]);
            seek += absVal(head - req[i]);
            head = req[i];
        }
    }

    for(i = n - 1; i >= 0; i--)
    {
        if(req[i] < head)
        {
            animateMove(head, req[i]);
            seek += absVal(head - req[i]);
            head = req[i];
        }
    }

    textcolor(LIGHTCYAN);
    cprintf("\nTotal Seek Time = %d\n", seek);

    delay(4000);
}

void CLOOK(int req[], int n, int head)
{
    int i, j, temp;
    int seek = 0;

    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(req[i] > req[j])
            {
                temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }
        }
    }

    line();
    textcolor(LIGHTMAGENTA);
    cprintf("        C-LOOK DISK SCHEDULING\n");
    line();

    delay(3000);

    for(i = 0; i < n; i++)
    {
        if(req[i] >= head)
        {
            animateMove(head, req[i]);
            seek += absVal(head - req[i]);
            head = req[i];
        }
    }

    for(i = 0; i < n; i++)
    {
        if(req[i] < head)
        {
            animateMove(head, req[i]);
            seek += absVal(head - req[i]);
            head = req[i];
        }
    }

    textcolor(LIGHTCYAN);
    cprintf("\nTotal Seek Time = %d\n", seek);

    delay(4000);
}

void main(void)
{
    int req[20], n, head, i;

    clrscr();

    textcolor(WHITE);
    cprintf("=========== DISK SCHEDULING VISUALIZER ===========\n");

    line();

    delay(4000);  /* intro narration */

    cprintf("Enter number of requests: ");
    scanf("%d", &n);

    cprintf("Enter request sequence:\n");

    for(i = 0; i < n; i++)
        scanf("%d", &req[i]);

    cprintf("Enter initial head position: ");
    scanf("%d", &head);

    delay(2000);

    SSTF(req, n, head);
    LOOK(req, n, head);
    CLOOK(req, n, head);

    line();

    textcolor(LIGHTGREEN);
    cprintf("            DONE\n");

    getch();
}