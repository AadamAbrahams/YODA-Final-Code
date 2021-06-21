#include <stdio.h>
#include <time.h>
#include <string.h>
#include "global.h"
#include "MD5.h"

static void MDString PROTO_LIST ((char *));
static void MDPrint PROTO_LIST ((unsigned char [16]));

#define MD_CTX MD5_CTX
#define MDInit MD5Init
#define MDUpdate MD5Update
#define MDFinal MD5Final


/* Main driver
 */
int main ()
{
  struct timespec startTime, endTime;
  float total, single;
  for (int i = 0; i < 10; i++){
  clock_gettime (CLOCK_REALTIME, &startTime);
  MDString ("abcde");
  MDString ("bcdef");
  MDString ("cdefg");
  MDString ("defgh");
  MDString ("efghi");


  clock_gettime (CLOCK_REALTIME, &endTime);
  single = endTime.tv_nsec - startTime.tv_nsec;
  total += single;
  printf ("\nTime = %.4f ms\n", (float)(single/1000000));
  }
  printf ("\nTime = %.4f ms\n", (float)(total/1000000));
  return (0);
}

/* Digests a string and prints the result.
 */
static void MDString (char *string)
{
  MD_CTX context;
  unsigned char digest[16];
  unsigned int len = strlen (string);

  MDInit (&context);
  MDUpdate (&context, string, len);
  MDFinal (digest, &context);
  MDPrint (digest);
  printf ("\n");
}

/* Prints a message digest in hexadecimal.
 */
static void MDPrint (unsigned char digest[])
{
  unsigned int i;

  for (i = 0; i < 16; i++)
 printf ("%02x", digest[i]);
}
