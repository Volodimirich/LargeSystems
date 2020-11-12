import subprocess

for i in range(10):
    subprocess.check_call(["../cmake-build-debug/Simulated_annealing 1 0 >> Result.txt"], shell=True)
    subprocess.check_call(["../cmake-build-debug/Simulated_annealing 0 1 >> Result.txt"], shell=True)
    subprocess.check_call(["../cmake-build-debug/Simulated_annealing 0 2 >> Result.txt"], shell=True)

