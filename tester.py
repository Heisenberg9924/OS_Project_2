import subprocess
import os

ranges = [
    (1, 500000),
    (1, 1000000),
    (1, 2000000)
]

n_cores = os.cpu_count()

n_values = list(range(1, n_cores + 1))

if os.path.exists("time.txt"):
    os.remove("time.txt")

print("Testing...\n")

for start,end in ranges:
    print(f"Testing with range {start} to {end}...")
    
    for n in n_values:
        print(f"Testing with n = {n}")
        
        subprocess.run(["./primes", str(start), str(end), str(n)])

print("\nTesting completed. Results saved in time.txt")