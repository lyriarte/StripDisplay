## StripDisplay


Display text and bitmaps on strip led panels. 

Fonts range between 4 cols x 6 lines and 8 cols x 13 lines. 
Panels must have at least 5 lines - to display 4x6 font in big caps only.

Strip led serpentine wrap on the panel is supported by columns or by lines, 
panel led origin can be at top left / top right / bottom left / bottom right, 
and it is possible to combine heterogeneous panels.


### Acknowledgements

This programs uses the [QDBMP](http://qdbmp.sourceforge.net) library for bitmap management. 
The fonts used are the ISO8859 FixedMedium from the /usr/share/fonts/X11/misc/ folder on Linux.


### API

Text and bitmap display APIs on [StripDisplay.h](StripDisplay.h)

### Code samples

Examples displaying text, sprites, and adressing pixels on 8 lines / 32 columns strip LED panels.

#### Basic text display

The [Hello.ino](examples/Hello/Hello.ino) example displays the string "Hello" in a 6x9 fixed font, on a 32x8 strip led panel.

#### Stacking, scrolling, pixels

The [Stacking.ino](examples/Stacking/Stacking.ino) example vertically stacks two 32x8 strip led panels to make a 32x16 bitmap.
In shows the bitmap-level pixel addressing by x,y coordinates API, low level text rendering, and high level text display API with scrolling.

#### All fonts

The [AllFonts.ino](examples/AllFonts/AllFonts.ino) example shows all available fonts, from 4x6 to 8x13 bold, on two stacked 32x8 strip led panels.

#### Space Invaders

The [SpaceInvaders.ino](examples/SpaceInvaders/SpaceInvaders.ino) example shows how to render sprites from xbm bitmaps.

#### Message Board

The [MessageBoard.ino](examples/MessageBoard/MessageBoard.ino) example continuously scrolls a text message at fixed speed, 
while reading text updates from the serial port.
