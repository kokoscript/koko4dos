# koko4dos
Simple program made with Allegro, feat. my fursona.
- bounce.c has a simple bouncing movement, akin to the famous "DVD logo" screen.
- bounceg.c introduces (really basic) gravity.

## Compiling
On a DOS machine:
1. [Get DJGPP + Allegro 4.2.3](http://www.mrdictionary.net/allegro/#directory)
2. Run `gcc <filename>.c -o <outputName>.exe -lalleg`

Will also work on Windows, provided you setup Allegro for use with your compiler of choice *and* modify the GFX mode towards the beginning of main.

Pre-compiled EXEs are provided on the releases page for convenience.
