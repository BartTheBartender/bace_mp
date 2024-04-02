import random
import math
import os
import subprocess


def equal(p, q):
    return abs(p - q) < 10e-25 or abs((p - q) / p) < 10e-6


maxf = 3.40282347e36
minf = 1.17549435e-36


def test(file_path, n):
    compile_command = f"g++ -std=c++98 -O2 -Wall -Wextra {file_path} -o bin_test"
    try:
        subprocess.run(compile_command, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Compilation error of {file_path}")
        return

    print("File compiled successfully")

    for i in range(n):

        x = random.choice([-1, 1]) * random.uniform(minf, maxf)
        print(x)
        y = x ** (1 / 3)
        test_input = str(y)
        try:
            test_output = subprocess.run(
                ["./bin_test"],
                text=True,
                capture_output=True,
                check=True,
                input=test_input,
            ).stdout.strip()  # Strip extra whitespace
            print(test_output)
            if not equal(x, float(test_output)):
                with open("test", "w") as file:
                    file.write(test_output)
                raise ValueError(f"Incorrect value of cube root for x = {x}")
        except subprocess.CalledProcessError as e:
            print(f"Runtime error of {file_path}!")


test("source.cpp", 10)
