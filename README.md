# Philosophers
This project represent the dining philosopher problem, using threads and mutex.

## Table of contents
  
  *	[General Info](#general-information)
  *	[Screenshots](#screenshots)
  *	[Usage](#usage)
  *	[Project status](#project-status)
  *	[Room for improvement](#room-for-improvement)
  *	[Contact](#contact)

## General information
This is the subject from 42 school, philosopher's. We've got n philosopher sitting around a table, with a bowl of spaghetti in the center of the table. Each philosopher, represented by a thread, has 1 fork at his left, and need 2 fork to eat. Each fork is represented by a mutex. The philosopher's eat, sleep or think. They have to start eating before _time_to_die_ is superior to they're last meal, or the start of the simulation, or they will die. If a philosopher die, the simulation should stop.

One of the problem was to avoid a deadlock situation : all the philosophers took a fork, and nobody can eat, because they need two fork to eat.

The simulation will stop if a philosopher die, or if each philosopher eats _number_of_eats_needed_.
## Usage
`git clone` the project, then `make` it

to launch it :

`./philo [number_of_philo][time_to_die_in_ms][time_to_eat_in_ms][time_to_sleep_in_ms][number_of_eats_needed(optionnal)]`
