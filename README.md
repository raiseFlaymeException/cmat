# cmat

A c library for matrix

## Table of Contents

- [Install](#install)
- [Usage](#usage)
- [Example](#example)
- [Maintainers](#maintainers)
- [Contributing](#contributing)
- [License](#license)

## Install

compile and run the test program:
```cmd
make run

```
or

```cmd
gcc -o main.c main.exe -I src/include
```

the library is in the folder [src/include/](src/include/)

## Usage

I try to comment stuff in [main](#main) and in the library to make it easier

```c
// include the implementation (see stb style library:
// https://github.com/nothings/stb)
#define CMAT_IMPL
#include "cmat.h"

int main(int argc, char *argv[]) {
    // create a 2x3 matrix
    CMatType arr1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    CMat     cmat1      = CMat_from_2darr(arr1);

    // create a 3x2 matrix
    CMatType arr2[3][2] = {{10, 11}, {20, 21}, {30, 31}};
    CMat     cmat2      = CMat_from_2darr(arr2);

    // create an uninitialized 2x2 matrix
    CMatType arr3[2][2];
    CMat     cmat3 = CMat_from_2darr(arr3);

    // create a 2x2 matrix
    CMatType arr_expected[2][2] = {{140, 146}, {320, 335}};
    CMat     cmat_expected      = CMat_from_2darr(arr_expected);

    // do a dot product between matrix 1 and matrix 2 and store the result in 3
    CMat_dot(&cmat3, &cmat1, &cmat2);

    // print the matrix
    CMat_print(&cmat3);

    // output:
    // --                     --
    // | 140.000000 146.000000 |
    // | 320.000000 335.000000 |
    // --                     -- 
}
```

## Example

A better example in the file [main.c](main.c)

## Maintainers

[@raiseFlaymeException](https://github.com/raiseFlaymeException).

## Contributing

Feel free to contibute [Open an issue](https://github.com/raiseFlaymeException/cmat/issues/new) or submit PRs.

## License

[ZLIB](LICENSE) © raiseFlaymeException
