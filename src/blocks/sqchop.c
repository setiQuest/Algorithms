/*******************************************************************************

  File:    sqchop.c
  Project: SETIkit
  Authors: Gerry Harp <gharp at seti dot org>

  Copyright 2011 The SETI Institute

  SETIkit is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  SETIkit is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with SETIkit.  If not, see <http://www.gnu.org/licenses/>.

  Implementers of this code are requested to include the caption
  "Licensed through SETI" with a link to setiQuest.org.

  For alternate licensing arrangements, please contact
  The SETI Institute at www.seti.org or setiquest.org. 

*******************************************************************************/

#ifndef __x86_64__
#   define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sq_constants.h>
#include <sq_dsp.h>
#include <sq_utils.h>

//          1         2         3         4         5         6         7
// 123456789012345678901234567890123456789012345678901234567890123456789012
char *usage_text[] = 
{
    "                                                                        ",
    "NAME                                                                    ",
    "  sqchop -  chop off a fixed fraction of samples from left and right    ",
    "SYNOPSIS                                                                ",
    "  sqchop [OPTIONS] ...                                                  ",
    "DESCRIPTION                                                             ",
    "  -l  Input number of samples                                           ",
    "  -x  Fraction (<0.5) of samples to chop from each end                  ",
    "                                                                        "
};
int arrlen = sizeof(usage_text)/sizeof(*usage_text);

unsigned int in_length = SMPLS_PER_READ;
float discard_fraction = 0.125;

int main(int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "hl:x:")) != -1)
    {
        switch (opt)
        {
            case 'h':
                print_usage(usage_text, arrlen);
                exit(EXIT_FAILURE);
            case 'l':
                sscanf(optarg, "%u", &in_length);
                break;
            case 'x':
                sscanf(optarg, "%f", &discard_fraction);
                break;
            default:
                print_usage(usage_text, arrlen);
                exit(EXIT_FAILURE);
        }
    }

    int status = sq_chop(stdin, stdout, in_length, discard_fraction);
    
    if(status < 0)
    {
        fprintf(stderr, "%s encountered a fatal error.", argv[0]);
        sq_error_handle(status);
        print_usage(usage_text, arrlen);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
