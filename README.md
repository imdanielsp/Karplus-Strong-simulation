## Simuliation of a guitar string using the Karplus-Strong algorithm
### Daniel Santos

The Karplus-String algorithm is a method of physical modelling synthesis that
loops a short waveform through a filtered delay line to simulate the sound of a
hammered or plucked string or some types of percussion. This algorithm was
invented by Alexander String, and Kevin Karplus did the first analysis of how it
worked. [1]

Here we used a data structure known as ring buffer, also know as circular
buffer. This data structure has a fixed-size, but the end is connected to the
start. This connection makes a circular behavoir in the representation of the
data.  We also used SFML, a C++ multimedia library, as an interface to produce
the sounds and graphics.

For more details about this project please check the [Princeton University page](http://www.cs.princeton.edu/courses/archive/spr15/cos126/assignments/guitar.html)
and [University of Massachusetts Lowell](http://www.cs.uml.edu/~ahatem/sp16/comp2040/assign/ps3-a.html)

Acknowledge: some of the code in this repository were provided by Prof. Ayat
Hatem as an academic resource.

Source:
[1] https://en.wikipedia.org/wiki/Karplus–Strong_string_synthesis