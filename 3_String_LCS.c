#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Main function
int main (int argc, char *argv[])
{
  if (argc != 4)                                                                // Make sure the number of input is correct
  {
    printf("Error! Invalid number of Arguments. Please run program as ./submission str1 str2 str3\n");
    return -1;
  }

  int sizeX = strlen(argv[1]) + 1;                                              // Added 1 to have 0th x
  int sizeY = strlen(argv[2]) + 1;                                              // Added 1 to have 0th y
  int sizeZ = strlen(argv[3]) + 1;                                              // Added 1 to have 0th z

  int lcsMaxLen =  ((((sizeX > sizeY)? sizeX : sizeY) > sizeZ)? ((sizeX > sizeY)? sizeX : sizeY) : sizeZ);    // Get max length from 3 string
  char LCS[lcsMaxLen];
  int lenLCS = 0;
  int i, j, k;
  int C[sizeX][sizeY][sizeZ];                                                   // C Table to store the count
  char B[sizeX][sizeY][sizeZ];                                                  // B Table to store the trace for arrows

  for (i = 0; i <  sizeX; i++)                                                  // Initialize the B and C Tables
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

  for (i = 0; i <  sizeX; i++)                                                  // Put Z on the X axis of B table to identify base case
  {
    C[i][0][0] = 0;
    B[i][0][0] = 'Z';
  }

  for (j = 0; j < sizeY; j++)                                                   // Put Z on the Y axis of B table to identify base case
  {
    C[0][j][0] = 0;
    B[0][j][0] = 'Z';
  }

  for (k = 0; k < sizeZ; k++)                                                   // Put Z on the Z axis of B table to identify base case
  {
    C[0][0][k] = 0;
    B[0][0][k] = 'Z';
  }

  for (i = 1; i < sizeX; i++)                                                   // Main algorithm to calculate the C table and update B table
  {
    for (j = 1; j < sizeY; j++)
    {
      for (k = 1; k < sizeZ; k++)
      {
        if ((argv[1][i-1] == argv[2][j-1]) && (argv[1][i-1] == argv[3][k-1]))   // If X, Y, Z same, then diagonal + 1 and store Diagonal 'D' as arrow
        {
          C[i][j][k] = C[i-1][j-1][k-1] + 1;                                    // Added 1 as we start from 0 not 1
          B[i][j][k] = 'D';
        }
        else
        {
          if ((C[i-1][j][k] >= C[i][j-1][k]) && ((C[i-1][j][k] >= C[i][j][k-1]))) // If top X element is bigger or equals then copy the element
          {
            C[i][j][k] = C[i-1][j][k];
            B[i][j][k] = '1';                                                   // Go up on X, Here 1 is unique identifier to go left on X axis
          }
          else if ((C[i][j-1][k] >= C[i-1][j][k]) && ((C[i][j-1][k] >= C[i][j][k-1]))) // If top Y element is bigger or equals then copy the element
          {
            C[i][j][k] = C[i][j-1][k];
            B[i][j][k] = '2';                                                   // Go up on Y, Here 2 is unique identifier to go left on Y axis
          }
          else                                                                  // Top Z element is bigger or equals then copy the element
          {
            C[i][j][k] = C[i][j][k-1];
            B[i][j][k] = '3';                                                   // Go up on Z, Here 3 is unique identifier to go left on Z axis
          }
        }
      }
    }
  }

  // Follow arrow and store the LCS
  i = sizeX-1;
  j = sizeY-1;
  k = sizeZ-1;
  lenLCS = 0;

  while ((i != 0) && (j != 0) && (k != 0))                                      // If we reach 1st element in the 2D array, then break
  {
    if (B[i][j][k] == '1')                                                      // If top X arrow
    {
      i = i - 1;
      continue;
    }
    else if (B[i][j][k] == '2')                                                 // If top Y arrow
    {
      j = j - 1;
      continue;
    }
    else if (B[i][j][k] == '3')                                                 // If top Z arrow
    {
      k = k - 1;
      continue;
    }
    else if (B[i][j][k] == 'D')                                                 // Found the diagonal arrow, store it in our LCS and increase LCS count and continue to diagonal element
    {
      LCS[lenLCS] = argv[1][i-1];                                               // LCS is in reverse order
      lenLCS++;
      i = i - 1;
      j = j - 1;
      k = k - 1;
    }
  }

  // Reverse the LCS to print in proper way
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

  printf("The length of the LCS= %d, and an LCS = ", lenLCS);                      // Print the LCS with length of LCS
  for (i = 0; i < lenLCS; i++)
  {
    printf("%C", LCS[i]);
  }
  printf("\n");

  return 0;
}
