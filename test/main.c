#define CTEST_MAIN
#define CTEST_SEGFAULT

#include <ctest.h>

int move_num = 1;

int main(int argc, const char* argv[]) {
	return ctest_main(argc, argv);
}