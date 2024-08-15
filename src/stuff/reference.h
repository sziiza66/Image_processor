
#ifndef IMG_PROC_REFERENCE_H
#define IMG_PROC_REFERENCE_H

#include <stdexcept>

void PrintHelpReference();
void PrintRuntineError(const std::runtime_error& e);
void PrintBadAllocError(const std::bad_alloc& e);
void PrintUnknownError(const std::exception& e);
void PrintBadUnknownError();

#endif  // IMG_PROC_REFERENCE_H
