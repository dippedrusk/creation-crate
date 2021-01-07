# Getting Started: Notes

* Batteries don't kill you because they're low amperage
* P (power) = I (current) * V (voltage)
* Longer lead == positive side, shorter lead == negative side (LED)
* R (resistance) = V (voltage) / I (current) - ohm's law!
* Current flows from positive -> negative

## Questions

1. Why did connecting the LEDs in parallel not work?
My initial guess was that the current prefers the first/closest path and so it picked the red LED.
But then I tested my hypothesis by changing the relative positions of the red LED, the blue LED and the negative end of the jumper wire. No dice - it was always the red one that lit up.
New hypothesis - maybe not the closest path but the _easiest_ path? Is there something about the blue LED that maybe has more resistance and is therefore dispreferred?
2. Is there a quicker way to reset what I've uploaded to my pins?
3. Do I need to "compile" everytime?
It seems not to generate any binaries, so my guess is no
