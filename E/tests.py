from sympy import symbols, diff, cos, sin, Matrix, exp
import random
import subprocess
import inspect
import re

# Parameters:
nof_trials = 100


def f(x, y):
    return x / y


# Functions:
def eval(x0, y0):
    x, y = symbols("x y")

    f_x = diff(f(x, y), x)
    f_y = diff(f(x, y), y)
    f_xx = diff(f_x, x)
    f_xy = diff(f_x, y)
    f_yy = diff(f_y, y)

    return [
        expr.subs({x: x0, y: y0}).evalf(20)
        for expr in [f(x, y), f_x, f_y, f_xx, f_xy, f_yy]
    ]


def cpp_input(x, y):
    return "1\n" + str(x) + " " + str(y)


def save_input(x, y):
    with open("test", "w") as file:
        file.write(cpp_input(x, y))
        file.close()


### The script:

compile_command = "g++ -o main main.cpp -O2 -std=c++11"
run_command = "./main"
new_return_value = re.search(r"return(.*)", inspect.getsource(f)).group(0)

print('Updating "funkcja.h" and compiling "main.cpp"... ', end="")
with open("funkcja.h", "r") as file:
    content = file.read()

pattern = r"return\s+.*?;"

modified_content = re.sub(pattern, new_return_value + ";", content, count=1)

with open("funkcja.h", "w") as file:
    file.write(modified_content)
try:
    subprocess.run(compile_command, shell=True, check=True)
except subprocess.CalledProcessError as e:
    print("Compilation error:", e)
    # exit(1)
print("done.")
for i in range(nof_trials):
    print(f"Trial no: {i}, calculation by python ... ", end="")
    x = random.uniform(-1e10, 1e10)
    y = random.uniform(-1e10, 1e10)
    try:
        python_result = [round(expr, 15) for expr in eval(x, y)]
    except Exception as e:
        print("Error:", e)
        save_input(x, y)
        exit(1)
    print("done, now calculation by cpp ... ", end="")
    try:
        process = subprocess.Popen(
            [run_command], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True
        )
        raw_result, _ = process.communicate(cpp_input(x, y))
    except subprocess.CalledProcessError as e:
        print("Error:", e)
        save_input(x, y)
        exit(1)

    cpp_result = [float(expr) for expr in raw_result.split(" ")]
    try:
        assert all(
            lambda p: abs(p[0] - p[1]) < 1e-8 for p in zip(python_result, cpp_result)
        ), rf"Result from python:\n{python_result}\nresult from cpp\n{cpp_result}"
    except AssertionError as e:
        print("Error:", e)
        save_input(x, y)
        exit(1)
    print("done.", end="\r")
