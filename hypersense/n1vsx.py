import ctypes
from pathlib import Path
base = Path(__file__).parent
from hypersense.utils import to_df

def get_func(ntype='static', function='static_sw'):
    wd = base.parent/'build'
    lib = ctypes.cdll.LoadLibrary(wd/f'n1vsx_{ntype}.so')
    func = getattr(lib, function)
    func.argtypes = [ctypes.c_int, ctypes.c_int,
                     ctypes.c_double, ctypes.c_double,
                     ctypes.c_double]
    func.restype = ctypes.c_char_p
    return func

def static_sw(n, k, p, b, c):
    func = get_func('static', 'static_sw')
    result = func(n, k, p, b, c)
    result = to_df(result)
    return result

def dynamic_sw(n, k, p, b, c):
    func = get_func('dynamic', 'dynamic_sw')
    result = func(n, k, p, b, c)
    result = to_df(result)
    return result

if __name__=='__main__':
    df = static_sw(10, 2, 0.1, -0.5, 1)
    df = dynamic_sw(10, 2, 0.1, -0.5, 1)
