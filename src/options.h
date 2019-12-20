#ifndef Options_H
#define Options_H

namespace opts {

    typedef int option_fields;

    const int recursive          = 0x01;
    const int ignore_case        = 0x02;
    const int print_line_numbers = 0x04;
    const int search_single_file = 0x08;
    const int regex_search       = 0x10;
    const int verbose            = 0x20;

}

#endif
