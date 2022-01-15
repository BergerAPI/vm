import os

# Creating the build dir if it doesn't exist
if not os.path.exists('build'):
    os.makedirs('build')

os.chdir('build')

# Deleting the last compiled file
if os.path.exists('vm'):
    os.remove('vm')

start_time = os.times()

# Buliding the project
os.system("cmake ..")

# Make
os.system("make")

print("".join(["-" for i in range(0, 20)]))

# Printing in green if the compiled file ("vm") exists
if os.path.exists("vm"):
    print("\033[92m", "vm file compiled successfully! Took ", os.times()[4] - start_time[4], "\033[0m")
else:
    print("\033[91m", "vm file compilation failed!", "\033[0m")

print("".join(["-" for i in range(0, 20)]))