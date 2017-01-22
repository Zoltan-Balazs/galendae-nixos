/******************************************************************************
 *                                                                            *
 *                galandae copyright (c) 2016 Chris Marsh                     *
 *               <https://github.com/chris-marsh/gcalendar                    *
 *                                                                            *
 * this program is free software: you can redistribute it and/or modify it    *
 * under the terms of the gnu general public license as published by the      *
 * free software foundation, either version 3 of the license, or any later    *
 * version.                                                                   *
 *                                                                            *
 * this program is distributed in the hope that it will be useful, but        *
 * without any warranty; without even the implied warranty of merchantability *
 * or fitness for a particular purpose.  see the gnu general public license   *
 * at <http://www.gnu.org/licenses/> for more details.                        *
 *                                                                            *
 ******************************************************************************/



#include <gtk/gtk.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include "gui.h"
#include "common.h"


/*
 * Output help/usage and exit the program
 */
static void usage(int exit_code)
{
    puts("\nUSAGE");
    puts("    galandae [OPTION ...] \n");
    puts("DESCRIPTION");
    puts("    Galandae displays a gui calendar. Keys:");
    puts("        h|Left    - decrease month");
    puts("        l|Right   - increase month");
    puts("        k|Up      - increase year");
    puts("        j|Down    - decrease year\n");
    puts("        g|Home    - return to current date\n");
    puts("        q|Esc     - exit the calendar\n");
    puts("OPTIONS");
    puts("    -c, --config FILE   - config file to load");
    puts("    -h, --help          - display this help and exit");
    puts("    -v, --version       - output version information\n");

    exit(exit_code);
}


/*
 * Output version information to the console and exit.
*/
static void version(void)
{
    printf(APP_NAME " version %s (compiled %s)\n", VERSION, __DATE__);
    exit(0);
}


/*
 * Process the commandline arguments passed to our app. This basic app
 * runs a GUI and only expects very 'basic' arguments, help, version and config.
 * more detailed options are provided by a config file.
*/
static char *process_arguments(int argc, char *argv[])
{
    int optc = 0;
    char *config_filename = NULL;
    static struct option const longopts[] = {
        {"config",   no_argument, NULL, 'c'},
        {"help",     no_argument, NULL, 'h'},
        {"version",  no_argument, NULL, 'V'},
        {NULL, 0, NULL, 0}
    };

    while ((optc = getopt_long(argc, argv, "c:hv", longopts, NULL)) != -1) {
        switch (optc) {
            case 'c':
                config_filename = strdup(optarg);
                break;
            case 'h':
                usage(0);
                break;
            case 'v':
                version();
                break;
            default:
                usage (-1);
        }
    }

    if (optind < argc) {
        if (argc-optind > 0) {
            /* Get the other arguments from argv[optind]*/
        } else
            usage(-1);
    }

    return config_filename;
}


/*
 * Create a main window and start the gtk event loop.
*/
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    char *config_filename = process_arguments(argc, argv);
    CalendarPtr window = create_calendar(config_filename);
    gtk_main();
    destroy_calendar(window);
    if (config_filename)
        free(config_filename);
    return 0;
}
