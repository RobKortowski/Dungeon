flags = [
'-Wall',
'-Wextra',
'-Werror',
'-std=c++11',
'-x',
'c++',
'-I',
'/home/rob/projects/Dungeon/src/main/headers',
'-isystem',
'/usr/local/include',
'-isystem',
'/usr/lib/llvm-3.8/bin/../lib/clang/3.8.0/include',
'-isystem',
'/usr/include/x86_64-linux-gnu',
'-isystem',
'/usr/include'
]

def FlagsForFile( filename, **kwargs ):
    return { 'flags': flags }
