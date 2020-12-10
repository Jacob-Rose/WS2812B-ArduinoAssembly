# WS2812_Arduino
Various .ino files that control WS2812 Lights. This uses zero external libraries, as well as a bit of assembly as well to get the timing correct.

The development process was written in LaTeX as part of the assignment requirements, hope this could also help somebody who is looking for an introduction to that as well.

Bug Warning: There is some issue with the writeZero() function that is slightly unreliable. This has no affects on the color or intensity of the lights, but some bits in the color might be read as a 1 instead of a zero by the LED strip, leading to some pixels flickering random colors. It is not extreme, but it is noticable. I have tried so many different timing variations to no avail. No matter how many tweaks I made, this could not be fixed by my efforts. Let me know if you see a good solution, I feel painfully close to finding the solution.
