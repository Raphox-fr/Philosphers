Philosophers is a concurrency and multithreading project from 42 School, inspired by the famous Dining Philosophers Problem. 
The goal is to implement a simulation where philosophers sit around a table, alternating between eating, thinking, and sleeping while following strict synchronization rules.

🏆 Objectives
Learn multithreading and process management.
Handle race conditions, deadlocks, and data synchronization.
Use mutexes and/or semaphores to ensure proper resource allocation.

📌 Project Details
Each philosopher must take two forks (one at a time) to eat.
They must not starve and should alternate between eating, thinking, and sleeping.
The simulation must not cause deadlocks.
The solution must be implemented using threads (or processes in the philo_bonus version).

⚙️ Technologies
C programming
POSIX threads (pthread)
Mutexes & semaphores
Time management & synchronization
This project is an excellent introduction to concurrent programming and thread synchronization, helping students develop a deeper understanding of parallel execution in real-world applications.
