// Created by codgician
// 12/01/2017 14:15:08

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _MSC_VER
#define _Bool short int
#else
#include <stdbool.h>
#endif

#define INVALID_YEAR 0
#define INVALID_MONTH 1
#define INVALID_DAY 2
#define BUFFER_SIZE 100

typedef struct _Date {
    int year;
    int month;
    int day;
} Date;

int monthDayNum[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31};

void flushStdin();
void printErrorMsg();
_Bool isLeapYear(int year);
_Bool isNumber(char* str);
Date getInput(char *str);
_Bool valiDateInput(Date a);
char* getSuffix(int n);

// This function flushes stdin.
void flushStdin()
{
    char c = 0;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// This function prints error message if error occurs.
void printErrorMsg(int errorType)
{
    printf("Invalid ");
    switch (errorType)
    {
        case INVALID_DAY:
            printf("day");
            break;
        case INVALID_MONTH:
            printf("month");
            break;
        case INVALID_YEAR:
            printf("year");
            break;
    }
    printf(". Please check your input and try again...\n\n");
}

// This function checks whether the given year is a leap year.
_Bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

// This function checks whether a given string is number.
_Bool isNumber(char* str)
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }

    return true;
}

// This function retrieves user input.
Date getInput(char* str)
{
    Date d;
    char yearBuffer[BUFFER_SIZE], monthBuffer[BUFFER_SIZE], dayBuffer[BUFFER_SIZE];

    sscanf(str, "%s%s%s", yearBuffer, monthBuffer, dayBuffer);

    if (isNumber(yearBuffer))
        // Only the last three digits are required to check whether it is leap year.
        d.year = atoi(yearBuffer + strlen(yearBuffer) - 3);
    else
        d.year = -1;

    if (strlen(monthBuffer) > 0 && strlen(monthBuffer) < 3 && isNumber(monthBuffer))
        d.month = atoi(monthBuffer);
    else
        d.month = -1;

    if (strlen(monthBuffer) > 0 && strlen(monthBuffer) < 3 && isNumber(dayBuffer))
        d.day = atoi(dayBuffer);
    else
        d.day = -1;

    return d;
}

// This function validates user input.
_Bool validateInput(Date a)
{
    // Validate year.
    if (a.year < 0)
    {
        printErrorMsg(INVALID_YEAR);
        return false;
    }
    // Validate month.
    if (a.month < 0 || a.month > 12)
    {
        printErrorMsg(INVALID_MONTH);
        return false;
    }

    // Process leap year.
    if (isLeapYear(a.year))
        monthDayNum[1] = 29;
    else
        monthDayNum[1] = 28;

    // Validate day.
    if (a.day < 0 || a.day > monthDayNum[a.month - 1])
    {
        printErrorMsg(INVALID_DAY);
        return false;
    }

    return true;
}


// This function returns the suffix for any integer number.
char* getSuffix(int n)
{
    char* ans = "th";

    if (n <= 10 || n >= 20)
    {
        switch (n % 10)
        {
            case 1:
                ans = "st";
                break;
            case 2:
                ans = "nd";
                break;
            case 3:
                ans = "rd";
                break;
            default:
                break;
        }
    }

    return ans;
}

// Core function.
int getAnswer(Date n)
{
    int i, ans = 0;
    for (i = 0; i < n.month - 1; i++)
    {
        ans += monthDayNum[i];
    }
    ans += n.day;

    return ans;
}

int main()
{
    // Program Title.
    system("title Day Checker by codgician");
    printf("Day Checker by codgician\n");
    printf("==============================\n");
    printf("Please input Date using the following format: YYYY MM DD (e.g. 2017 12 01):\nPress Ctrl + C to exit the program.\n");

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, sizeof(buffer), stdin))
    {
        // Do not process ENTER.
        if (buffer[0] == '\n')
            continue;

        // Flush stdin if user input exceeds buffer size.
        if (strlen(buffer) == BUFFER_SIZE - 1)
        {
            flushStdin();
        }

        // Phrase input.
        Date d = getInput(buffer);

        // Validate input.
        if (!validateInput(d))
            continue;

        int ans = getAnswer(d);
        printf("This is the %d%s day.\n\n", ans, getSuffix(ans));
    }

    return 0;
}
