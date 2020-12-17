import subprocess
import os
import time
import shutil


main_dir = os.getcwd()

for i in range(10):
    for it in range(10):
        if os.path.exists(main_dir + f"/mut{i}_launch{it}"):
            shutil.rmtree(main_dir + f"/mut{i}_launch{it}")
        os.makedirs(f"mut{i}_launch{it}")
        os.chdir(main_dir + f"/mut{i}_launch{it}")
        start_time = time.time()
        subprocess.check_call([f"../../cmake-build-debug/Genetic_Algorithm {i}  {it}"], shell=True)
        end_time = time.time()
        f = open(f'series_{i}_best_result_{it}.txt', "a")
        f.write('\n')
        f.write(str(end_time - start_time))
        f.close()

        os.chdir(main_dir)

        time.sleep(1)