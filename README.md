# Philosophers

Solve the Philosophers problem via Multithreading in C.

<b>Steps to run the program:</b>
    1. make
    2. Run the program: ./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat (optional)]

<b>Argument Description:</b>
◦ number_of_philosophers: The number of philosophers and also the number
of forks.

◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the sim-
ulation, they die.

◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.

◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.

◦ number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

<b>Acceptance Tests:</b>
    DONT'S:
        Do not test with more than 200 philosophers.
	    Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.
							
    Test I: 1 800 200 200 -> Expected: The philosopher should not eat and should die.
	
    Test II: 5 800 200 200 -> Expected: No philosopher should die.
	
    Test III: 5 800 200 200 7 -> Expected: No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
	
    Test IV: 4 410 200 200 -> Expected: No philosopher should die.
	
    Test V: 4 310 200 100 -> Expected: One philosopher should die.
	
    Test VI: Test with 2 philosophers and check the different times -> Expected: A death delayed by more than 10 ms is unacceptable.
	
    Test with any values of your choice to verify all the requirements.
    
    Ensure philosophers die at the right time, that they don't steal forks, and so forth.

    Thank you for appreciating the project ;)