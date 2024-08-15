
#include "reference.h"

#include <iostream>

void PrintHelpReference() {
    std::cout << "No filters are specified or too few arguments (must have atleast input and output). How to use:\n"
              << "To apply filters, first specify input path and output path"
                 "(ending files of both paths must be in .bmp format)\n"
              << "then give sequence of filters and their parameters alternating, to specify filter name write "
                 "-filer_name, example:\n"
              << "image processor.exe input_file_path output_file_path -filte1 param1 param2 -filter2 -filter3 "
                 "-param.\n"
              << "There are available basic filters:\n"
              << "1. Crop (-crop width height) too big numbers may cause error.\n"
              << "2. Grayscale (-gs) no params.\n"
              << "3. Negative (-neg) no params.\n"
              << "4. Sharpening (-sharp) no params.\n"
              << "5. Edge Detection (-edge threshold) threshold is real number in [0, 255],"
                 "bigger threshold implies darker output.\n"
              << "6. Gaussian Blur (-blur sigma) sigma is real number > 0, also too big sigma may cause error.\n"
              << "7. Amusing (-amuse vert rev) vert in {0, 1}, rev in {0, 1}."
                 "(basicly, this filter sorts pixels with a certain rule)"
                 "if vert=1 filter applies vertically, horisontally otherwise."
                 "if rev=1 filter applies sorting in reverse order.";
}

void PrintRuntineError(const std::runtime_error& e) {
    std::cerr << "Something went wrong!\nThere are possible reasons:\n"
              << "1. some of the specified filter names are wrong.\n"
              << "2. some of the filter's parameters specified incorrectly.\n"
              << "3. input output or output file is not in .bmp format.\n"
              << "4. input output or output file can't be accessed.\n"
              << "5. input output or output file has unsupported .bmp format (e.x.: any .bmp with compression).\n"
              << "6. input output or output file is broken.\n"
              << "To see help reference call this program without any arguments.\n"
              << "Actual error message:\n"
              << e.what() << '\n';
}

void PrintBadAllocError(const std::bad_alloc& e) {
    std::cerr << "Something went wrong!\nThere are possible reasons:\n"
              << "1. input output or output file is too big\n"
              << "2. too many arguments (filters and params). least likly.\n"
              << "Anyway in either case your computer doesn't have enough memory for this operation.\n"
              << "To see help reference call this program without any arguments.\n"
              << "Actual error message:\n"
              << e.what() << '\n';
}

void PrintUnknownError(const std::exception& e) {
    std::cerr << "Something went wrong!\n"
              << "It is not clear, what actually caused en error.\n"
              << "It is suggested to check that input and output files are correct and nothing"
                 "and nothing except with program is trying to access them duping filter process.\n"
              << "Secondly, make sure, that filters and parameters are specified correctly.\n"
              << "To see help reference call this program without any arguments.\n"
              << "Actual error message:\n"
              << e.what() << '\n';
}

void PrintBadUnknownError() {
    std::cerr << "Something went wrong!\n"
              << "It is not clear, what actually caused en error.\n"
              << "It is suggested to check that input and output files are correct and nothing"
                 "and nothing except with program is trying to access them duping filter process.\n"
              << "Secondly, make sure, that filters and parameters are specified correctly.\n"
              << "To see help reference call this program without any arguments.\n";
}