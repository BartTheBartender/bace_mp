import random
import subprocess
import os
import string


def generate_test():
    m = random.randint(1, 7)
    n = random.randint(1, 5)
    i = 0
    xs = ""
    while i < m:
        repetitions = random.randint(1, int(m / 2) + 2)
        x = random.uniform(-1e2, 1e2)
        i += repetitions
        xs += " ".join([str(x) for _ in range(repetitions)]) + " "

    ys = " ".join([str(random.uniform(-1e2, 1e2)) for _ in range(m)])

    ts = " ".join([str(random.uniform(-1e2, 1e2)) for _ in range(n)])

    return "\n".join([str(m) + " ", str(n), xs, ys, ts])


def clear():

    if os.path.exists("first_bin"):
        os.remove("first_bin")
    if os.path.exists("second_bin"):
        os.remove("second_bin")


def benchmark(first, second):
    first_out = ""
    second_out = ""

    compile_command = f"g++ -std=c++11 -O2 -Wall -Wextra {first} -o first_bin"
    try:
        subprocess.run(compile_command, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Compilation error of {first}")
        return

    compile_command = f"g++ -std=c++11 -O2 -Wall -Wextra {second} -o second_bin"
    try:
        subprocess.run(compile_command, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Compilation error of {second}")
        return

    print("Files compiled sucessfully")

    # now run both files as long as the outputs are the same or one of the programs crashes

    for i in range(500):
        print(f"Trial no. {i}")

        test_input = generate_test()

        with open("test", "w") as test:
            test.write(test_input)
        try:
            first_out = subprocess.run(
                ["./first_bin"],
                text=True,
                capture_output=True,
                check=True,
                input=test_input,
            ).stdout
        except subprocess.CalledProcessError as e:
            print(f"Runtime error of {first}!")
            clear()
            return
        print(f"\t{first} ran")

        try:
            second_out = subprocess.run(
                ["./second_bin"],
                text=True,
                capture_output=True,
                check=True,
                input=test_input,
            ).stdout
        except subprocess.CalledProcessError as e:
            print(f"Runtime error of {second}!")
            clear()
            return
        print(f"\t{second} ran")

        if first_out != second_out:
            print("Difference found")
            clear()
            return

    print("No differences found")


benchmark("main.cpp", "optimized.cpp")
# print(generate_test())
