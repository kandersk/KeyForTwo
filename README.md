# KeyForTwo

Simple Keylogger application for Mac OS made in C

## Libraries

Mac OS comes with built in accessibility features that we can use in C just by including a couple libraries.
```
#include <Carbon/Carbon.h>
#include <ApplicationServices/ApplicationServices.h>
```
These are for manipulating the world of accessibility in Mac OS. These are also quite old and no longer supported by Apple. So they might not work for everyone (I was able to run them on Mac OS 10.12.6)

## Implementation

Following a lot of helpful examples:

- [Receiving, Filtering, and Modifying Key Presses and Releases](www.osxbook.com/book/bonus/chapter2/alterkeys/)
- [keyremap by atr00 on GitHub](https://gist.github.com/atr000/387590)
- [keylogger by GiacomoLaw on GitHub](https://github.com/GiacomoLaw/Keylogger)

I was able to develop an understanding of the built in Apple API that let's us do all kinds of fun things, like manipulate keyboard inputs and how keys are treated. So from here I developed a simple script that while active will print out all the buttons that have been pressed by the user.

## Usage

Clone the repo and within the directory simply type
`make` to compile and `sudo ./logger` to run `control + C` to quit

## Issues and other monsters

- Accessibility has to be enabled
- When running, the user must have admin privileges (run with sudo)
- This will only look at the keyboard when not typing into protected fields such as passwords
- The running terminal script makes it very obvious (but I am sure there are ways around that)
- Caps lock registers the same way no matter if it is enabled or disabled
- There is a delay with inputs, so don't type too fast.

### KeyCodes

Apple has setup a system of referincing each key with a code in a way that might looks quite inconsistent so most. I am not sure why this is the case, but a more indepth look can be found under [this link on keycodes](https://eastmanreference.com/complete-list-of-applescript-key-codes/).

# Looking towards the future

While this was a blast to make, I am getting quite a lot of fun ideas as to what can be done with knowledge of this kind of system

__For Example__: We could create statistics reports showing what are the most common patterns of typing by the user. We could even analyze the words typed and show which words are most often misspelled.