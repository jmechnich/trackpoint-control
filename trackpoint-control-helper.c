#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <libgen.h>

const char* basepath = "/sys/devices/platform/i8042";

char* progname = NULL;

int setValue( const char* path, const char* value)
{
  FILE* f = fopen( path, "w");
  if( !f)
  {
    printf( "Could not open '%s'\n", path);
    return 1;
  }

  size_t written = fwrite( value, sizeof(char), strlen(value), f);

  fclose( f);

  if( written != strlen(value))
  {
    printf( "Error writing %lu bytes to file, got %lu\n", strlen(value), written);
    return 1;
  }

  return 0;
}

void checkNumber(const char* arg, const char* val)
{
  char* endptr = NULL;

  /* check first if value starts with digit */
  if(!isdigit(*val)) goto ABORT;

  /* try conversion and check errno */
  errno = 0;
  strtol(val,&endptr,10);
  if(errno != 0) goto ABORT;

  /* check if conversion ended prematurely */
  if(strlen(val)!=(endptr-val)) goto ABORT;

  return;

  ABORT:
  printf("invalid value for argument '%s': %s\n", arg, val);
  abort();
}

void help()
{
  printf("usage: %s options\n", basename(progname));
  printf("  -h  --help          print this text and exit\n");
  printf("  -p  --path PATH     relative path to trackpoint parameter\n");
  printf("  -v  --value VALUE   value to trackpoint parameters directory\n");
}

int main( int argc, char** argv)
{
  progname = argv[0];
  
  char path[PATH_MAX];
  memset( path, 0, PATH_MAX);

  const size_t value_maxlength = 3;
  char value[value_maxlength+1];
  memset( value, 0, value_maxlength+1);
  
  int c;
  while (1)
  {
  
    static struct option long_options[] =
        {
            /* These options set a flag. */
            {"path", required_argument, 0, 'p'},
            {"value", required_argument, 0, 'v'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
        };
    /* getopt_long stores the option index here. */
    int option_index = 0;
    c = getopt_long (argc, argv, "p:v:h", long_options, &option_index);
    
    /* Detect the end of the options. */
    if (c == -1)
        break;
    
    switch (c)
    {
    case 'p':
#ifdef DEBUG
      printf("path: %s\n", optarg);
#endif
      if( (realpath(optarg,path) != path) || (strstr(path,basepath) != path)) {
        printf("Invalid path '%s'\n", optarg);
        abort();
      }
      break;
    case 'v':
#ifdef DEBUG
      printf("value: %s\n", optarg);
#endif
      strncpy(value, optarg, value_maxlength);
      checkNumber("value",value);
      break;
    case 'h':
      help();
      exit(0);
      break;
    case '?':
      abort();
      break;
    default:
#ifdef DEBUG
      printf("Unknown command line flag '%c'\n", c);
#endif
      abort();
    }
  }

  if( !*path || !*value)
  {
    printf("Path and value are required arguments\n");
    abort();
  }

  return setValue(path,value);
}
