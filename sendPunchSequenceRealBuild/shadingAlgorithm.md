## How the shading algorithm works

### `generateShadedPunchPattern(byte *patternBuffer)`

Averages the image colours and map it to a shaded punch pattern.
The final image resolution will be reduced to 16x16 consisting of 2x2 pixels.
2x2 'pixels' with more holes denotes a brighter colour. Fewer holes indicate darker colours.
See the [Notion page](https://www.notion.so/SendPunchSequence-struct-punch_encoding-pattern-78d25b63250348c6a8cfb363eebb98ca) for more info.

### `int computeAverageColour(int rowTopL, int colTopL)`

Returns a number from 0 to 4, 0 for darkest colours, 4 for lightest colours.

Computes an 'average color' by averaging all Red and Green values from 2x2 leds,
then maps this 'average' to an int from 0 to 4.

Average calculations for all etch a sketch colours, where `avg = (colour.red + colour.green)/2`:
```
RED
R: 255
G: 0
B: 0
avg = 128

YELLOW
R: 255
G: 255
B: 0
avg = 255

GREEN
R: 144
G: 238
B: 144
avg = 191

BLUE
R: 135
G: 206
B: 235
avg = 170

PURPLE
R: 147
G: 112
B: 219
avg = 130
```

The thresholds were calculated by averaging four leds of adjacent colours,
e.g. an 'average' value of 2 green and 2 yellow leds results in 220.
If you have 4 leds with contrasting colours, eg 2 yellow, 2 black, the result will be
something in between all of the colours.