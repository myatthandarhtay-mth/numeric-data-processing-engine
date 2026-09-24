#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX 10
#define EPS 1e-6
#define BUFFER 256

void change_lowercase(char *str)
{
    int i;
    for (i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

int checking_range(double x)
{
    if (x < -100 || x > 100)
        return 0;
    return 1;
}

void determine_decimal_place_print(double x)
{
    if (fabs(x - (int)x) < EPS)
        printf("%d", (int)x);
    else
    {
        double temp = (int)(x * 100) / 100.0;
        printf("%.2f", temp);
    }
}

void print_stage(double arr[], int size)
{
    int i;
    if (size == 0)
    {
        printf("empty\n");
        return;
    }

    for (i = 0; i < size; i++)
    {
        determine_decimal_place_print(arr[i]);
        if (i != size - 1)
            printf(" ");
    }
    printf("\n");
}

int reading_elements(char *input, double arr[], int *size)
{
    char *token;
    int count = 0;
    double temp[MAX];

    token = strtok(input, " ");
    token = strtok(NULL, " ");

    while (token != NULL)
    {
        if (count >= MAX)
            break;

        char *endptr;
        double value = strtod(token, &endptr);

        if (*endptr != '\0' || !checking_range(value))
            return 0;

        temp[count++] = value;
        token = strtok(NULL, " ");
    }

    if (count == 0)
        return 0;

    int i;
    for (i = 0; i < count; i++)
    {
        arr[i] = temp[i];
    }

    *size = count;
    return 1;
}

void clear_elements(int *size)
{
    *size = 0;
}

int map_abs(double arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        arr[i] = fabs(arr[i]);
    }
    return 1;
}

int map_square(double arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        arr[i] = arr[i] * arr[i];
    }
    return 1;
}

int map_sqrt(double arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr[i] < 0)
            return 0;
        arr[i] = sqrt(arr[i]);
    }
    return 1;
}

int scale(double arr[], int size, double factor)
{
    int i;
    for (i = 0; i < size; i++)
    {
        arr[i] *= factor;
    }
    return 1;
}

int filter_positive(double arr[], int *size)
{
    int i, j = 0;
    for (i = 0; i < *size; i++)
    {
        if (arr[i] > 0)
            arr[j++] = arr[i];
    }
    *size = j;
    return 1;
}

int filter_negative(double arr[], int *size)
{
    int i, j = 0;
    for (i = 0; i < *size; i++)
    {
        if (arr[i] < 0)
            arr[j++] = arr[i];
    }
    *size = j;
    return 1;
}

int unique(double arr[], int *size)
{
    int i, j, k;
    for (i = 0; i < *size; i++)
    {
        for (j = i + 1; j < *size;)
        {
            if (fabs(arr[i] - arr[j]) < EPS)
            {
                for (k = j; k < *size - 1; k++)
                {
                    arr[k] = arr[k + 1];
                }
                (*size)--;
            }
            else
                j++;
        }
    }
    return 1;
}

int sorting_elements(double arr[], int size, int ascending)
{
    int i, j;
    for (i = 0; i < size - 1; i++)
    {
        for (j = i + 1; j < size; j++)
        {
            if ((ascending && arr[i] > arr[j]) ||
                (!ascending && arr[i] < arr[j]))
            {
                double temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return 1;
}

int reduce(double arr[], int *size, char *type)
{
    if (*size == 0)
        return 0;

    double result;
    int i;

    if (strcmp(type, "sum") == 0)
    {
        result = 0;
        for (i = 0; i < *size; i++)
            result += arr[i];
    }
    else if (strcmp(type, "min") == 0)
    {
        result = arr[0];
        for (i = 1; i < *size; i++)
            if (arr[i] < result)
                result = arr[i];
    }
    else if (strcmp(type, "max") == 0)
    {
        result = arr[0];
        for (i = 1; i < *size; i++)
            if (arr[i] > result)
                result = arr[i];
    }
    else if (strcmp(type, "avg") == 0)
    {
        result = 0;
        for (i = 0; i < *size; i++)
            result += arr[i];
        result /= *size;
    }
    else if (strcmp(type, "count") == 0)
    {
        result = *size;
    }
    else
        return 0;

    determine_decimal_place_print(result);
    printf("\n");
    return 2;
}

int main()
{
    double arr[MAX];
    int size = 0;
    char input[BUFFER];

    while (fgets(input, BUFFER, stdin))
    {
        input[strcspn(input, "\n")] = '\0';
        change_lowercase(input);

        if (strcmp(input, "exit") == 0)
            break;

        if (strcmp(input, "print") == 0)
        {
            print_stage(arr, size);
            continue;
        }

        if (strncmp(input, "load ", 5) == 0)
        {
            if (!reading_elements(input, arr, &size))
                printf("error\n");
            else
                print_stage(arr, size);
            continue;
        }

        if (strcmp(input, "clear") == 0)
        {
            clear_elements(&size);
            printf("empty\n");
            continue;
        }

        if (size == 0)
        {
            printf("error\n");
            continue;
        }

        if (strcmp(input, "map abs") == 0)
        {
            map_abs(arr, size);
            print_stage(arr, size);
        }
        else if (strcmp(input, "map square") == 0)
        {
            map_square(arr, size);
            print_stage(arr, size);
        }
        else if (strcmp(input, "map sqrt") == 0)
        {
            if (!map_sqrt(arr, size))
                printf("error\n");
            else
                print_stage(arr, size);
        }
        else if (strncmp(input, "scale ", 6) == 0)
        {
            double factor = atof(input + 6);
            scale(arr, size, factor);
            print_stage(arr, size);
        }
        else if (strcmp(input, "filter positive") == 0)
        {
            filter_positive(arr, &size);
            print_stage(arr, size);
        }
        else if (strcmp(input, "filter negative") == 0)
        {
            filter_negative(arr, &size);
            print_stage(arr, size);
        }
        else if (strcmp(input, "unique") == 0)
        {
            unique(arr, &size);
            print_stage(arr, size);
        }
        else if (strcmp(input, "sort asc") == 0)
        {
            sorting_elements(arr, size, 1);
            print_stage(arr, size);
        }
        else if (strcmp(input, "sort desc") == 0)
        {
            sorting_elements(arr, size, 0);
            print_stage(arr, size);
        }
        else if (strncmp(input, "reduce ", 7) == 0)
        {
            int r = reduce(arr, &size, input + 7);
            if (r == 0)
                printf("error\n");
        }
        else
        {
            printf("error\n");
        }
    }

    return 0;
}