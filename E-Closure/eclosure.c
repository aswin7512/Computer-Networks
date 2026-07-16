#include <stdio.h>

#define MAX 20

int n, t;
char states[MAX];
char from[MAX], symbol[MAX], to[MAX];
int visited[MAX];

// Function to get index of a state
int getIndex(char ch)
{
    for (int i = 0; i < n; i++)
    {
        if (states[i] == ch)
            return i;
    }
    return -1;
}

// Function to find epsilon closure using DFS
void epsilonClosure(char state)
{
    int idx = getIndex(state);

    if (visited[idx])
        return;

    visited[idx] = 1;
    printf("%c ", state);

    // Check all transitions
    for (int i = 0; i < t; i++)
    {
        if (from[i] == state && symbol[i] == 'e')
        {
            epsilonClosure(to[i]);
        }
    }
}

int main()
{
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter the states:\n");
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &states[i]);
    }

    printf("Enter number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (From Symbol To)\n");
    printf("Use 'e' for epsilon.\n");

    for (int i = 0; i < t; i++)
    {
        scanf(" %c %c %c", &from[i], &symbol[i], &to[i]);
    }

    printf("\nEpsilon Closures:\n");

    for (int i = 0; i < n; i++)
    {
        // Reset visited array
        for (int j = 0; j < n; j++)
            visited[j] = 0;

        printf("E-Closure(%c) = { ", states[i]);
        epsilonClosure(states[i]);
        printf("}\n");
    }

    return 0;
}
