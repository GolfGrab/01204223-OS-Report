import time
from typing import Callable


def timeit(func: Callable) -> Callable:
    def wrapper():
        start = time.time()
        result = func()
        end = time.time()

        print(f"running {func.__name__} took {end - start} seconds")
        return result

    return wrapper


@timeit
def normal_func():
    result = 0
    for i in range(10000):
        result *= i


@timeit
def io_func():
    for _ in range(10000):
        with open("test.txt", "w") as f:
            f.write("test")


normal_func()
io_func()
