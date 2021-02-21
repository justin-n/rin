#ifndef Options_H
#define Options_H

namespace opts {

    typedef int option_fields;

    const int recursive          = 0x001;
    const int ignore_case        = 0x002;
    const int print_line_numbers = 0x004;
    const int search_single_file = 0x008;
    const int regex_search       = 0x010;
    const int verbose            = 0x020;
    const int file_name_match    = 0x040;
    const int max_depth          = 0x080;
    const int negative_search    = 0x100;
}

#endif
