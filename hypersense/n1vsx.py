import ctypes
from pathlib import Path
base = Path(__file__).parent
from hypersense.utils import to_df

def get_func(ntype='dynamic', function='static_sw'):
    wd = base.parent/'build'
    lib = ctypes.cdll.LoadLibrary(wd/f'n1vsx_{ntype}.so')
    func = getattr(lib, function)
    func.argtypes = [ctypes.c_int, ctypes.c_int,
                     ctypes.c_double, ctypes.c_double,
                     ctypes.c_double]
    func.restype = ctypes.c_char_p
    return func, lib.free_memory


def dynamic_sw_new(n, k, p, b, c):
    wd = base.parent/'build'
    lib = ctypes.cdll.LoadLibrary(wd/'n1vsx_dynamic.so')
    # Defining alloc function and it's return type
    func = lib.dynamic_sw
    func.restype = ctypes.POINTER(ctypes.c_char)
    func.argtypes = [ctypes.c_int, ctypes.c_int,
                     ctypes.c_double, ctypes.c_double,
                     ctypes.c_double]

    # Defining free function and it's return type
    free_func = lib.free_memory
    free_func.argtypes = [ctypes.POINTER(ctypes.c_char)]

    # Using the function to return a string
    cstring_pointer = func(n, k, p, b, c)
    s = ctypes.c_char_p.from_buffer(cstring_pointer)
    df = to_df(s.value)
    # Freeing memory
    free_func(cstring_pointer)
    return df



def static_sw(n, k, p, b, c):
    func = get_func('static', 'static_sw')
    result = func(n, k, p, b, c)
    result = to_df(result)
    return result

# def dynamic_sw(n, k, p, b, c):
#     func, free = get_func('dynamic', 'dynamic_sw')
#     result = func(n, k, p, b, c)
#     result = to_df(result)
#     return result

if __name__=='__main__':
    pass
    (n, k, p, b, c) = (10, 2, 0.1, -0.5, 1)
    # df = static_sw(10, 2, 0.1, -0.5, 1)
    df = dynamic_sw_new(n, k, p, b, c)
