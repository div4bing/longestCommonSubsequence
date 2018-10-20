#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
  char *x = "6541254939322816220209974565477289648317";
  char *y = "3142522751761601737419090933147067701840";
  char *z = "2807030561290354259513570160162463275171";

  int sizeX = strlen(x) + 1;   // Added 1 to have 0th x
  int sizeY = strlen(y) + 1;   // Added 1 to have 0th y
  int sizeZ = strlen(z) + 1;   // Added 1 to have 0th z

  int lcsMaxLen = ((sizeX > sizeY)? sizeX : sizeY); // TODO: Modify to include Z
  char LCS[lcsMaxLen];
  int lenLCS = 0;

  int i, j, k;

  int C[sizeX][sizeY][sizeZ];
  char B[sizeX][sizeY][sizeZ];

  for (i = 0; i <  sizeX; i++)
  {
    for (j = 0; j < sizeY; j++)
    {
      for (k = 0; k < sizeZ; k++)
      {
        B[i][j][k] = 0;
        C[i][j][k] = 0;
      }
    }
  }

  for (i = 0; i <  sizeX; i++)
  {
    C[i][0][0] = 0;
    B[i][0][0] = 'Z';
  }

  for (j = 0; j < sizeY; j++)
  {
    C[0][j][0] = 0;
    B[0][j][0] = 'Z';
  }

  for (k = 0; k < sizeZ; k++)
  {
    C[0][0][k] = 0;
    B[0][0][k] = 'Z';
  }

  printf("X array is: \n");
  for (i = 0; i < sizeX-1; i++)
  {
    printf("%C ", x[i]);
  }
  printf("\n");

  printf("Y array is: \n");
  for (i = 0; i < sizeY-1; i++)
  {
    printf("%C ", y[i]);
  }
  printf("\n");

  printf("Z array is: \n");
  for (i = 0; i < sizeZ-1; i++)
  {
    printf("%C ", z[i]);
  }
  printf("\n");
  //******************************************************
  for (i = 1; i < sizeX; i++)
  {
    for (j = 1; j < sizeY; j++)
    {
      for (k = 1; k < sizeZ; k++)
      {
        printf("x=%C, y=%C and z=%C\n",x[i-1], y[j-1], z[k-1]);
        if ((x[i-1] == y[j-1]) && (x[i-1] == z[k-1]))           // If all are same, then diagonal + 1
        {
          printf("FOUND MATCH\n");
          C[i][j][k] = C[i-1][j-1][k-1] + 1;              // Added 1 as we start from 0 not 1
          B[i][j][k] = 'D';
        }
        else
        {
          if ((C[i-1][j][k] >= C[i][j-1][k]) && ((C[i-1][j][k] >= C[i][j][k-1])))             // If top element is bigger or equals to left element then copy top element
          {
            C[i][j][k] = C[i-1][j][k];
            B[i][j][k] = '1'; // Go up on X
          }
          else if ((C[i][j-1][k] >= C[i-1][j][k]) && ((C[i][j-1][k] >= C[i][j][k-1])))
          {
            C[i][j][k] = C[i][j-1][k];
            B[i][j][k] = '2'; // Go up on Y
          }
          else
          {
            C[i][j][k] = C[i][j][k-1];
            B[i][j][k] = '3'; // Go up on Z
          }
        }
      }
    }
  }

  printf("C Matrix:\n\n");
  for (i = 0; i <  sizeX; i++)
  {
    for (j = 0; j < sizeY; j++)
    {
      for (k = 0; k < sizeZ; k++)
      {
        printf("%d ", C[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }

  printf("\nB Matrix:\n\n");
  for (i = 0; i <  sizeX; i++)
  {
    for (j = 0; j < sizeY; j++)
    {
      for (k = 0; k < sizeZ; k++)
      {
        printf("%C ", B[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }

  // Follow arrow and store the LCS
  i = sizeX-1;
  j = sizeY-1;
  k = sizeZ-1;
  lenLCS = 0;

  while ((i != 0) && (j != 0) && (k != 0))      // If we reach 1st element in the 2D array, then break
  {
    printf("i=%d j=%d k=%d B[%d][%d][%d]=%C\n",i, j, k, i, j, k, B[i][j][k]);

    if (B[i][j][k] == '1')       // If UP arrow
    {
      i = i - 1;
      continue;
    }
    else if (B[i][j][k] == '2')
    {
      j = j - 1;
      continue;
    }
    else if (B[i][j][k] == '3')
    {
      k = k - 1;
      continue;
    }
    else if (B[i][j][k] == 'D')    // Found the diagonal arrow, store it in our LCS and increase LCS count
    {
      printf("Loading x[%d]=%C\n",i-1, x[i-1]);
      LCS[lenLCS] = x[i-1];                       // LCS is in reverse order
      lenLCS++;
      i = i - 1;
      j = j - 1;
      k = k - 1;
    }
  }

  // Reverse the LCS
  j = lenLCS - 1;
  i = 0;
  int temp;

  while (i < j)
  {
     temp = LCS[i];
     LCS[i] = LCS[j];
     LCS[j] = temp;
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

  return 0;
}
