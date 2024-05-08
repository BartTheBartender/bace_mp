import random
import subprocess
import os
import string


def generate_test():
    M = 1
    h = random.randint(1, 5000)
    w = random.randint(1, 5000)
    output = " ".join([str(x) for x in [M, h, w]]) + "\n"
    pixels = []
    for _ in range(h * w):
        pixels.append(random.choice(["o", "x"]))
    output += " ".join(pixels)

    print("\tTest generated")
    return output


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

    error_found = False
    for i in range(10000):
        print(f"Trial no. {i}")
        if error_found:
            break

        test_input = generate_test()
        # print(test_input)
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
            error_found = True
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
            error_found = True
        print(f"\t{second} ran")

        if first_out != second_out:
            error_found = True

    if os.path.exists("first_bin"):
        os.remove("first_bin")
    if os.path.exists("second_bin"):
        os.remove("second_bin")

    if error_found:
        print("Error found!")
        with open("test", "w") as test:
            test.write(test_input)
    else:
        print("No differences found")


benchmark("main.cpp", "krzysiek.cpp")
# print(generate_test())
