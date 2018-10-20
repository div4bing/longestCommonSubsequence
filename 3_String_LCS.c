#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  // char x[] = {'A', 'B', 'C', 'B', 'D', 'A', 'B'};
  // char y[] = {'B', 'D', 'C', 'A', 'B', 'A'};

  // char x[] = {'A', 'B', 'C', 'B'};
  // char y[] = {'B', 'D', 'C', 'A'};

  char x[] = {'C', 'A', 'C', 'M', 'Y', 'C', 'C', 'A'};
  char y[] = {'Y', 'M', 'C', 'M', 'A', 'M', 'Y', 'Y', 'C', 'M', 'A'};

  int sizeX = (sizeof(x)/sizeof(char)) + 1;   // Added 1 to have 0th column
  int sizeY = (sizeof(y)/sizeof(char)) + 1;   // Added 1 to have 0th row

  int lcsMaxLen = (sizeX + sizeY)/2;
  char LCS[lcsMaxLen];
  int lenLCS = 0;

  int i, j;

  int *C[sizeX];
  for (i = 0; i < sizeX; i++)
  {
    C[i] = (int *)malloc(sizeY * sizeof(int));
  }

  char *B[sizeX];
  for (i = 0; i < sizeX; i++)
  {
    B[i] = (char *)malloc(sizeY * sizeof(char));
  }

  for (i = 0; i <  sizeX; i++)
  {
    C[i][0] = 0;
    B[i][0] = 'Z';
  }

  for (j = 0; j < sizeY; j++)
  {
    C[0][j] = 0;
    B[0][j] = 'Z';
  }

  // printf("X array is: \n");
  // for (i = 0; i < sizeX-1; i++)
  // {
  //   printf("%C ", x[i]);
  // }
  // printf("\n");

  //******************************************************
  for (i = 1; i < sizeX; i++)
  {
    for (j = 1; j< sizeY; j++)
    {
      // printf("x=%C and y=%C\n",x[i-1], y[j-1]);
      if (x[i-1] == y[j-1])                         // If both are same, then diagonal + 1
      {
        C[i][j] = C[i-1][j-1] + 1;              // Added 1 as we start from 0 not 1
        B[i][j] = 'D';
      }
      else
      {
        if (C[i-1][j] >= C[i][j-1])             // If top element is bigger or equals to left element then copy top element
        {
          C[i][j] = C[i-1][j];
          B[i][j] = 'U';
        }
        else                                    // Else copy left element
        {
          C[i][j] = C[i][j-1];
          B[i][j] = 'L';
        }
      }
    }
  }

  printf("C Matrix:\n\n");
  for (i = 0; i <  sizeX; i++)
  {
    for (j = 0; j < sizeY; j++)
    {
      printf("%d ", C[i][j]);
    }
    printf("\n");
  }

  printf("\nB Matrix:\n\n");
  for (i = 0; i <  sizeX; i++)
  {
    for (j = 0; j < sizeY; j++)
    {
      printf("%C ", B[i][j]);
    }
    printf("\n");
  }

  // Follow arrow and store the LCS
  i = sizeX-1;
  j = sizeY-1;
  lenLCS = 0;

  while (B[i][j] != 'Z')      // If we reach 1st element in the 2D array, then break
  {
    // printf("i=%d j=%d B[%d][%d]=%C\n",i, j, i, j, B[i][j]);

    if (B[i][j] == 'U')       // If UP arrow
    {
      i = i - 1;
      continue;
    }
    else if (B[i][j] == 'L')
    {
      j = j - 1;
      continue;
    }
    else if (B[i][j] == 'D')    // Found the diagonal arrow, store it in our LCS and increase LCS count
    {
      // printf("Loading x[%d]=%C\n",i-1, x[i-1]);
      LCS[lenLCS] = x[i-1];                       // LCS is in reverse order
      lenLCS++;
      i = i - 1;
      j = j - 1;
    }
  }

  // Reverse the LCS
  j = lenLCS - 1;
  i = 0;
  char tempChar;

  while (i < j)
  {
     tempChar = LCS[i];
     LCS[i] = LCS[j];
     LCS[j] = tempChar;
     i++;
     j--;
  }

  printf("\nLCS is:\n");
  for (i = 0; i < lenLCS; i++)
  {
    printf("%C ", LCS[i]);
  }
  printf("\nLength of LCS is: %d\n", lenLCS);

  //******************************************************

  for (i = 0; i < sizeX; i++)
  {
    free(C[i]);
    free(B[i]);
  }

  return 0;
}
