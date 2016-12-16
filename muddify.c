#include <stdio.h>
#include <stdlib.h>

main (int argc, char *argv[]) {

  FILE *source_fp, *dest_fp;
  int ch;

  if (argc != 3) {
    fprintf(stderr, "usage: muddify source dest\n");
    exit(EXIT_FAILURE);
  }

  if ((source_fp = fopen(argv[1], "rb")) == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  if ((dest_fp = fopen(argv[2], "wb")) == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[2]);
    fclose(source_fp);
    exit(EXIT_FAILURE);
  }

  fprintf(dest_fp, "#include <stdio.h>\n");
  fprintf(dest_fp, "main(){\n  int i=0,z[99999]={\n");

  while ((ch = getc(source_fp)) != EOF)
    fprintf(dest_fp, "%d,", ch-44);

  fprintf(dest_fp,"-34};\n");
  fprintf(dest_fp, "  while(z[i]|z[i+1]) printf(\"%%c\",z[i++]+44);\n  return 0;\n}\n");

  fclose(source_fp);
  fclose(dest_fp);
  return 0;
  
}

