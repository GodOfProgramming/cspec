import os
import ycm_core

DIR_OF_THIS_SCRIPT = os.path.abspath( os.path.dirname( __file__ ) )

flags = [ 
    '-x',
    'c++',
    '-Wall',
    '-Wextra',
    '-std=c++17',
    '-Iinclude' 
]

def Settings( **kwargs ):
    return {
        'flags': flags,
        'include_paths_relative_to_dir': DIR_OF_THIS_SCRIPT
    }
