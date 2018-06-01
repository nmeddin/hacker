
#include <sstream>
#include <thread>

#include <istream> 
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <crypt.h>



int main(int argc, char *argv[])
{

   printf("%s\n", crypt("abcq", "ab"));

   printf("%s\n", crypt("abcw", "ab"));

   printf("%s\n", crypt("abce", "ab"));

   printf("%s\n", crypt("abcr", "ab"));

   
   printf("%s\n", crypt("abct", "ab"));

   printf("%s\n", crypt("abcy", "ab"));

   printf("%s\n", crypt("abcu", "ab"));

   printf("%s\n", crypt("abci", "ab"));


   printf("%s\n", crypt("abca", "ab"));

   printf("%s\n", crypt("abcs", "ab"));

   printf("%s\n", crypt("abcd", "ab"));

   printf("%s\n", crypt("abcf", "ab"));

   
   printf("%s\n", crypt("abcg", "ab"));

   printf("%s\n", crypt("abch", "ab"));

   printf("%s\n", crypt("abcj", "ab"));

   printf("%s\n", crypt("abck", "ab"));


   printf("%s\n", crypt("abcK", "ab"));

   printf("%s\n", crypt("abcZ", "ab"));

   printf("%s\n", crypt("abcA", "ab"));

   printf("%s\n", crypt("abcF", "ab"));

   
   printf("%s\n", crypt("abcG", "ab"));

   printf("%s\n", crypt("abcH", "ab"));

   printf("%s\n", crypt("abcT", "ab"));

   printf("%s\n", crypt("abAA", "ab"));


	printf("%s\n", crypt("VWXY", "VW"));
	exit(0);

}
