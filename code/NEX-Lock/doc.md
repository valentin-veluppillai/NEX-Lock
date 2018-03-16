# NEX-Lock.ino
This is the same as uid_servo, but with added PIN functionality. Anytime the
correct UID is detected, the Arduino waits for a PIN entered via the matrix. It
can also be opened form the inside by pressing a button. An SD card addition is planned
keypad.
## v0.4 [16.3.18]
The door can now be unlocked from two sides (kinda useful, right?). When the door is open, it waits for a button press on the override/close button or the keypad, depending on the side the door was opened from.
* renamed file/folder to NEX-Lock, as I decided to stay on the Arduino instead of moving to an Raspberry Pi, the user functionality will be realised by adding an SD Card module, probably going to use one from adafruit
* tested (and fixed) override/close button (formerly manual unlock button)
* cleaned up code and comments

## v0.3 [28.2.18]
* added manual unlock button
* moved servo from pin 3 to pin 6 (needed to freee up pin 3 for interrupt)
* cleaned up code a bunch

### problems
* didn't test it

## v0.2 [22.2.18]
Now multiple users are possible
* added support for multiple UIDs/PINs
* fixed bug: every pin working with every uid
* cleaned up code a bit

## v0.1 [20.2.18]
* Copied uid_servo and added PIN functionality

### problems
when a key on the matrix keypad is pressed at an unexpected time, the lock won't
open, possible workaround: when the button is pressed accidentally, press it
three more times
