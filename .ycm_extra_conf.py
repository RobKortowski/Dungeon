flags = [
'-Wall',
'-Wextra',
'-Werror',
'-std=c++11',
'-x',
'c++',
'-isystem',
'/usr/local/include',
'-isystem',
'/usr/lib/llvm-3.8/bin/../lib/clang/3.8.0/include',
'-isystem',
'/usr/include/x86_64-linux-gnu',
'-isystem',
'/usr/include',
'-I',
'./src/main/headers'
#'-isystem',
#'./tests/gmock/gtest',
#'-isystem',
#'./tests/gmock/gtest/include',
#'-isystem',
#'./tests/gmock',
#'-isystem',
#'./tests/gmock/include',
]




def FlagsForFile( filename, **kwargs ):
    return { 'flags': flags }
