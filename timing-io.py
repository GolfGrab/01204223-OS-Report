import time
from typing import Callable


def timeit(func: Callable) -> Callable:
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()

        print(f"running {func.__name__} took {end - start : .8f} seconds")
        return result

    return wrapper


@timeit
def normal_func(n) -> None:
    result = 1
    for i in range(n):
        result *= i + 1


@timeit
def io_func(n) -> None:
    for _ in range(n):
        with open("test.txt", "w") as f:
            f.write("test")


print("Timing normal_func and io_func with 1000 iterations each...")
normal_func(1000)
io_func(1000)
print("Timing normal_func and io_func with 10000 iterations each...")
normal_func(10000)
io_func(10000)
print("Timing normal_func and io_func with 100000 iterations each...")
normal_func(100000)
io_func(100000)
