/* Mark Ebden, c 2005

   Obscures text.  To use:
   1. Create extensionless text file (e.g. myfile)
   2. enshroud myfile 7

   To extract:
   1. gcc myfile.c; a.out > myfile.c
   2. Repeat until it errors out
   3. cat myfile.c
*/

#include <stdio.h>
#include <stdlib.h>

main (int argc, char *argv[]) {

  FILE *source_fp, *dest_fp;
  int ch, n;
  char s[200], f1[200], f2[200];

  n = atoi(argv[2]);
  strcpy (f1, argv[1]);
  strcpy (f2, "TEMP_FILE"); /*strcpy (f2, argv[2]);*/

  if (argc != 3) {
    fprintf(stderr, "usage: enshroud source n\n");
    exit(EXIT_FAILURE);
  }
  if ((source_fp = fopen(argv[1], "rb")) == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  if ((dest_fp = fopen(f2, "wb")) == NULL) {
    fprintf(stderr, "Can't open %s\n", f2);
    fclose(source_fp);
    exit(EXIT_FAILURE);
  }
  sprintf (s, "cp %s %s%d\n", f1, f1, n);
  system(s);

  /*printf("%d muddifies.\n", n);*/
  do {
    sprintf (s, "./muddify %s%d %s%d\n", f1, n, f2, n-1); system (s);
    /*printf ("%s",s);*/
    sprintf (s, "rm %s%d\n", f1,n); system(s);
    strcpy (f1, f2);
  } while (--n > 0);

  sprintf (s, "mv %s0 %s.c\n", f2, argv[1]);  system(s);
  sprintf (s, "rm %s\n", f2);  system(s);

  fclose(source_fp);  fclose(dest_fp);
  return 0;

}

