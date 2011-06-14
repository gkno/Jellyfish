/*
  File autogenerated by gengetopt version 2.22.4
  generated with the following command:
  gengetopt --show-required --default-option -c cc -H hpp -F histo_cmdline -f histo_cmdline -a histo_args --unamed-opts=database.jf

  The developers of gengetopt consider the fixed text that goes in all
  gengetopt output files to be in the public domain:
  we make no copyright claims on it.
*/

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FIX_UNUSED
#define FIX_UNUSED(X) (void) (X) /* avoid warnings for unused params */
#endif

#include <getopt.h>

#include "histo_cmdline.hpp"

const char *histo_args_purpose = "Create an histogram of k-mer occurrences";

const char *histo_args_usage = "Usage: jellyfish histo [OPTIONS]... [database.jf]...";

const char *histo_args_description = "Create an histogram with the number of k-mers having a\ngiven count. In bucket 'i' are tallied the k-mers which have a count\n'c' satisfying 'low+i*inc <= c < low+(i+1)*inc'. Buckets in the output are\nlabeled by the low end point (low+i*inc).\n\nThe last bucket in the output behaves as a catchall: it tallies all\nk-mers with a count greater or equal to the low end point of this\nbucket.";

const char *histo_args_help[] = {
  "      --help                    Print help and exit",
  "  -V, --version                 Print version and exit",
  "  -s, --buffer-size=Buffer length\n                                Length in bytes of input buffer  \n                                  (default=`10000000')",
  "  -l, --low=LONG                Low count value of histogram  (default=`1')",
  "  -h, --high=LONG               High count value of histogram  \n                                  (default=`10000')",
  "  -i, --increment=LONG          Increment value for buckets  (default=`1')",
  "  -t, --threads=INT             Number of threads  (default=`1')",
  "  -f, --full                    Full histo. Don't skip count 0.  (default=off)",
  "  -o, --output=STRING           Output file  (default=`/dev/fd/1')",
    0
};

typedef enum {ARG_NO
  , ARG_FLAG
  , ARG_STRING
  , ARG_INT
  , ARG_LONG
} histo_cmdline_arg_type;

static
void clear_given (struct histo_args *args_info);
static
void clear_args (struct histo_args *args_info);

static int
histo_cmdline_internal (int argc, char **argv, struct histo_args *args_info,
                        struct histo_cmdline_params *params, const char *additional_error);


static char *
gengetopt_strdup (const char *s);

static
void clear_given (struct histo_args *args_info)
{
  args_info->help_given = 0 ;
  args_info->version_given = 0 ;
  args_info->buffer_size_given = 0 ;
  args_info->low_given = 0 ;
  args_info->high_given = 0 ;
  args_info->increment_given = 0 ;
  args_info->threads_given = 0 ;
  args_info->full_given = 0 ;
  args_info->output_given = 0 ;
}

static
void clear_args (struct histo_args *args_info)
{
  FIX_UNUSED (args_info);
  args_info->buffer_size_arg = 10000000;
  args_info->buffer_size_orig = NULL;
  args_info->low_arg = 1;
  args_info->low_orig = NULL;
  args_info->high_arg = 10000;
  args_info->high_orig = NULL;
  args_info->increment_arg = 1;
  args_info->increment_orig = NULL;
  args_info->threads_arg = 1;
  args_info->threads_orig = NULL;
  args_info->full_flag = 0;
  args_info->output_arg = gengetopt_strdup ("/dev/fd/1");
  args_info->output_orig = NULL;
  
}

static
void init_args_info(struct histo_args *args_info)
{


  args_info->help_help = histo_args_help[0] ;
  args_info->version_help = histo_args_help[1] ;
  args_info->buffer_size_help = histo_args_help[2] ;
  args_info->low_help = histo_args_help[3] ;
  args_info->high_help = histo_args_help[4] ;
  args_info->increment_help = histo_args_help[5] ;
  args_info->threads_help = histo_args_help[6] ;
  args_info->full_help = histo_args_help[7] ;
  args_info->output_help = histo_args_help[8] ;
  
}

void
histo_cmdline_print_version (void)
{
  printf ("%s %s\n",
     (strlen(HISTO_CMDLINE_PACKAGE_NAME) ? HISTO_CMDLINE_PACKAGE_NAME : HISTO_CMDLINE_PACKAGE),
     HISTO_CMDLINE_VERSION);
}

static void print_help_common(void) {
  histo_cmdline_print_version ();

  if (strlen(histo_args_purpose) > 0)
    printf("\n%s\n", histo_args_purpose);

  if (strlen(histo_args_usage) > 0)
    printf("\n%s\n", histo_args_usage);

  printf("\n");

  if (strlen(histo_args_description) > 0)
    printf("%s\n\n", histo_args_description);
}

void
histo_cmdline_print_help (void)
{
  int i = 0;
  print_help_common();
  while (histo_args_help[i])
    printf("%s\n", histo_args_help[i++]);
}

void
histo_cmdline_init (struct histo_args *args_info)
{
  clear_given (args_info);
  clear_args (args_info);
  init_args_info (args_info);

  args_info->inputs = 0;
  args_info->inputs_num = 0;
}

void
histo_cmdline_params_init(struct histo_cmdline_params *params)
{
  if (params)
    { 
      params->override = 0;
      params->initialize = 1;
      params->check_required = 1;
      params->check_ambiguity = 0;
      params->print_errors = 1;
    }
}

struct histo_cmdline_params *
histo_cmdline_params_create(void)
{
  struct histo_cmdline_params *params = 
    (struct histo_cmdline_params *)malloc(sizeof(struct histo_cmdline_params));
  histo_cmdline_params_init(params);  
  return params;
}

static void
free_string_field (char **s)
{
  if (*s)
    {
      free (*s);
      *s = 0;
    }
}


static void
histo_cmdline_release (struct histo_args *args_info)
{
  unsigned int i;
  free_string_field (&(args_info->buffer_size_orig));
  free_string_field (&(args_info->low_orig));
  free_string_field (&(args_info->high_orig));
  free_string_field (&(args_info->increment_orig));
  free_string_field (&(args_info->threads_orig));
  free_string_field (&(args_info->output_arg));
  free_string_field (&(args_info->output_orig));
  
  
  for (i = 0; i < args_info->inputs_num; ++i)
    free (args_info->inputs [i]);

  if (args_info->inputs_num)
    free (args_info->inputs);

  clear_given (args_info);
}


static void
write_into_file(FILE *outfile, const char *opt, const char *arg, const char *values[])
{
  FIX_UNUSED (values);
  if (arg) {
    fprintf(outfile, "%s=\"%s\"\n", opt, arg);
  } else {
    fprintf(outfile, "%s\n", opt);
  }
}


int
histo_cmdline_dump(FILE *outfile, struct histo_args *args_info)
{
  int i = 0;

  if (!outfile)
    {
      fprintf (stderr, "%s: cannot dump options to stream\n", HISTO_CMDLINE_PACKAGE);
      return EXIT_FAILURE;
    }

  if (args_info->help_given)
    write_into_file(outfile, "help", 0, 0 );
  if (args_info->version_given)
    write_into_file(outfile, "version", 0, 0 );
  if (args_info->buffer_size_given)
    write_into_file(outfile, "buffer-size", args_info->buffer_size_orig, 0);
  if (args_info->low_given)
    write_into_file(outfile, "low", args_info->low_orig, 0);
  if (args_info->high_given)
    write_into_file(outfile, "high", args_info->high_orig, 0);
  if (args_info->increment_given)
    write_into_file(outfile, "increment", args_info->increment_orig, 0);
  if (args_info->threads_given)
    write_into_file(outfile, "threads", args_info->threads_orig, 0);
  if (args_info->full_given)
    write_into_file(outfile, "full", 0, 0 );
  if (args_info->output_given)
    write_into_file(outfile, "output", args_info->output_orig, 0);
  

  i = EXIT_SUCCESS;
  return i;
}

int
histo_cmdline_file_save(const char *filename, struct histo_args *args_info)
{
  FILE *outfile;
  int i = 0;

  outfile = fopen(filename, "w");

  if (!outfile)
    {
      fprintf (stderr, "%s: cannot open file for writing: %s\n", HISTO_CMDLINE_PACKAGE, filename);
      return EXIT_FAILURE;
    }

  i = histo_cmdline_dump(outfile, args_info);
  fclose (outfile);

  return i;
}

void
histo_cmdline_free (struct histo_args *args_info)
{
  histo_cmdline_release (args_info);
}

/** @brief replacement of strdup, which is not standard */
char *
gengetopt_strdup (const char *s)
{
  char *result = 0;
  if (!s)
    return result;

  result = (char*)malloc(strlen(s) + 1);
  if (result == (char*)0)
    return (char*)0;
  strcpy(result, s);
  return result;
}

int
histo_cmdline (int argc, char **argv, struct histo_args *args_info)
{
  return histo_cmdline2 (argc, argv, args_info, 0, 1, 1);
}

int
histo_cmdline_ext (int argc, char **argv, struct histo_args *args_info,
                   struct histo_cmdline_params *params)
{
  int result;
  result = histo_cmdline_internal (argc, argv, args_info, params, 0);

  if (result == EXIT_FAILURE)
    {
      histo_cmdline_free (args_info);
      exit (EXIT_FAILURE);
    }
  
  return result;
}

int
histo_cmdline2 (int argc, char **argv, struct histo_args *args_info, int override, int initialize, int check_required)
{
  int result;
  struct histo_cmdline_params params;
  
  params.override = override;
  params.initialize = initialize;
  params.check_required = check_required;
  params.check_ambiguity = 0;
  params.print_errors = 1;

  result = histo_cmdline_internal (argc, argv, args_info, &params, 0);

  if (result == EXIT_FAILURE)
    {
      histo_cmdline_free (args_info);
      exit (EXIT_FAILURE);
    }
  
  return result;
}

int
histo_cmdline_required (struct histo_args *args_info, const char *prog_name)
{
  FIX_UNUSED (args_info);
  FIX_UNUSED (prog_name);
  return EXIT_SUCCESS;
}


static char *package_name = 0;

/**
 * @brief updates an option
 * @param field the generic pointer to the field to update
 * @param orig_field the pointer to the orig field
 * @param field_given the pointer to the number of occurrence of this option
 * @param prev_given the pointer to the number of occurrence already seen
 * @param value the argument for this option (if null no arg was specified)
 * @param possible_values the possible values for this option (if specified)
 * @param default_value the default value (in case the option only accepts fixed values)
 * @param arg_type the type of this option
 * @param check_ambiguity @see histo_cmdline_params.check_ambiguity
 * @param override @see histo_cmdline_params.override
 * @param no_free whether to free a possible previous value
 * @param multiple_option whether this is a multiple option
 * @param long_opt the corresponding long option
 * @param short_opt the corresponding short option (or '-' if none)
 * @param additional_error possible further error specification
 */
static
int update_arg(void *field, char **orig_field,
               unsigned int *field_given, unsigned int *prev_given, 
               char *value, const char *possible_values[],
               const char *default_value,
               histo_cmdline_arg_type arg_type,
               int check_ambiguity, int override,
               int no_free, int multiple_option,
               const char *long_opt, char short_opt,
               const char *additional_error)
{
  char *stop_char = 0;
  const char *val = value;
  int found;
  char **string_field;
  FIX_UNUSED (field);

  stop_char = 0;
  found = 0;

  if (!multiple_option && prev_given && (*prev_given || (check_ambiguity && *field_given)))
    {
      if (short_opt != '-')
        fprintf (stderr, "%s: `--%s' (`-%c') option given more than once%s\n", 
               package_name, long_opt, short_opt,
               (additional_error ? additional_error : ""));
      else
        fprintf (stderr, "%s: `--%s' option given more than once%s\n", 
               package_name, long_opt,
               (additional_error ? additional_error : ""));
      return 1; /* failure */
    }

  FIX_UNUSED (default_value);
    
  if (field_given && *field_given && ! override)
    return 0;
  if (prev_given)
    (*prev_given)++;
  if (field_given)
    (*field_given)++;
  if (possible_values)
    val = possible_values[found];

  switch(arg_type) {
  case ARG_FLAG:
    *((int *)field) = !*((int *)field);
    break;
  case ARG_INT:
    if (val) *((int *)field) = strtol (val, &stop_char, 0);
    break;
  case ARG_LONG:
    if (val) *((long *)field) = (long)strtol (val, &stop_char, 0);
    break;
  case ARG_STRING:
    if (val) {
      string_field = (char **)field;
      if (!no_free && *string_field)
        free (*string_field); /* free previous string */
      *string_field = gengetopt_strdup (val);
    }
    break;
  default:
    break;
  };

  /* check numeric conversion */
  switch(arg_type) {
  case ARG_INT:
  case ARG_LONG:
    if (val && !(stop_char && *stop_char == '\0')) {
      fprintf(stderr, "%s: invalid numeric value: %s\n", package_name, val);
      return 1; /* failure */
    }
    break;
  default:
    ;
  };

  /* store the original value */
  switch(arg_type) {
  case ARG_NO:
  case ARG_FLAG:
    break;
  default:
    if (value && orig_field) {
      if (no_free) {
        *orig_field = value;
      } else {
        if (*orig_field)
          free (*orig_field); /* free previous string */
        *orig_field = gengetopt_strdup (value);
      }
    }
  };

  return 0; /* OK */
}


int
histo_cmdline_internal (
  int argc, char **argv, struct histo_args *args_info,
                        struct histo_cmdline_params *params, const char *additional_error)
{
  int c;	/* Character of the parsed option.  */

  int error = 0;
  struct histo_args local_args_info;
  
  int override;
  int initialize;
  int check_required;
  int check_ambiguity;
  
  package_name = argv[0];
  
  override = params->override;
  initialize = params->initialize;
  check_required = params->check_required;
  check_ambiguity = params->check_ambiguity;

  if (initialize)
    histo_cmdline_init (args_info);

  histo_cmdline_init (&local_args_info);

  optarg = 0;
  optind = 0;
  opterr = params->print_errors;
  optopt = '?';

  while (1)
    {
      int option_index = 0;

      static struct option long_options[] = {
        { "help",	0, NULL, 0 },
        { "version",	0, NULL, 'V' },
        { "buffer-size",	1, NULL, 's' },
        { "low",	1, NULL, 'l' },
        { "high",	1, NULL, 'h' },
        { "increment",	1, NULL, 'i' },
        { "threads",	1, NULL, 't' },
        { "full",	0, NULL, 'f' },
        { "output",	1, NULL, 'o' },
        { 0,  0, 0, 0 }
      };

      c = getopt_long (argc, argv, "Vs:l:h:i:t:fo:", long_options, &option_index);

      if (c == -1) break;	/* Exit from `while (1)' loop.  */

      switch (c)
        {
        case 'V':	/* Print version and exit.  */
          histo_cmdline_print_version ();
          histo_cmdline_free (&local_args_info);
          exit (EXIT_SUCCESS);

        case 's':	/* Length in bytes of input buffer.  */
        
        
          if (update_arg( (void *)&(args_info->buffer_size_arg), 
               &(args_info->buffer_size_orig), &(args_info->buffer_size_given),
              &(local_args_info.buffer_size_given), optarg, 0, "10000000", ARG_LONG,
              check_ambiguity, override, 0, 0,
              "buffer-size", 's',
              additional_error))
            goto failure;
        
          break;
        case 'l':	/* Low count value of histogram.  */
        
        
          if (update_arg( (void *)&(args_info->low_arg), 
               &(args_info->low_orig), &(args_info->low_given),
              &(local_args_info.low_given), optarg, 0, "1", ARG_LONG,
              check_ambiguity, override, 0, 0,
              "low", 'l',
              additional_error))
            goto failure;
        
          break;
        case 'h':	/* High count value of histogram.  */
        
        
          if (update_arg( (void *)&(args_info->high_arg), 
               &(args_info->high_orig), &(args_info->high_given),
              &(local_args_info.high_given), optarg, 0, "10000", ARG_LONG,
              check_ambiguity, override, 0, 0,
              "high", 'h',
              additional_error))
            goto failure;
        
          break;
        case 'i':	/* Increment value for buckets.  */
        
        
          if (update_arg( (void *)&(args_info->increment_arg), 
               &(args_info->increment_orig), &(args_info->increment_given),
              &(local_args_info.increment_given), optarg, 0, "1", ARG_LONG,
              check_ambiguity, override, 0, 0,
              "increment", 'i',
              additional_error))
            goto failure;
        
          break;
        case 't':	/* Number of threads.  */
        
        
          if (update_arg( (void *)&(args_info->threads_arg), 
               &(args_info->threads_orig), &(args_info->threads_given),
              &(local_args_info.threads_given), optarg, 0, "1", ARG_INT,
              check_ambiguity, override, 0, 0,
              "threads", 't',
              additional_error))
            goto failure;
        
          break;
        case 'f':	/* Full histo. Don't skip count 0..  */
        
        
          if (update_arg((void *)&(args_info->full_flag), 0, &(args_info->full_given),
              &(local_args_info.full_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "full", 'f',
              additional_error))
            goto failure;
        
          break;
        case 'o':	/* Output file.  */
        
        
          if (update_arg( (void *)&(args_info->output_arg), 
               &(args_info->output_orig), &(args_info->output_given),
              &(local_args_info.output_given), optarg, 0, "/dev/fd/1", ARG_STRING,
              check_ambiguity, override, 0, 0,
              "output", 'o',
              additional_error))
            goto failure;
        
          break;

        case 0:	/* Long option with no short option */
          if (strcmp (long_options[option_index].name, "help") == 0) {
            histo_cmdline_print_help ();
            histo_cmdline_free (&local_args_info);
            exit (EXIT_SUCCESS);
          }

        case '?':	/* Invalid option.  */
          /* `getopt_long' already printed an error message.  */
          goto failure;

        default:	/* bug: option not considered.  */
          fprintf (stderr, "%s: option unknown: %c%s\n", HISTO_CMDLINE_PACKAGE, c, (additional_error ? additional_error : ""));
          abort ();
        } /* switch */
    } /* while */




  histo_cmdline_release (&local_args_info);

  if ( error )
    return (EXIT_FAILURE);

  if (optind < argc)
    {
      int i = 0 ;
      int found_prog_name = 0;
      /* whether program name, i.e., argv[0], is in the remaining args
         (this may happen with some implementations of getopt,
          but surely not with the one included by gengetopt) */

      i = optind;
      while (i < argc)
        if (argv[i++] == argv[0]) {
          found_prog_name = 1;
          break;
        }
      i = 0;

      args_info->inputs_num = argc - optind - found_prog_name;
      args_info->inputs =
        (char **)(malloc ((args_info->inputs_num)*sizeof(char *))) ;
      while (optind < argc)
        if (argv[optind++] != argv[0])
          args_info->inputs[ i++ ] = gengetopt_strdup (argv[optind-1]) ;
    }

  return 0;

failure:
  
  histo_cmdline_release (&local_args_info);
  return (EXIT_FAILURE);
}