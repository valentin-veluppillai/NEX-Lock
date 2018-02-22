# NEX-Lock_arduino
This is the same as uid_servo, but with added PIN functionality. Anytime the
correct UID is detected, the Arduino waits for a PIN entered via the matrix
keypad.
## v0.1 [22.2.18]
* added support for multiple UIDs/PINs
* fixed bug: every pin working with every uid
* cleaned up code a bbit

## v0.1 [20.2.18]
* Copied uid_servo and added PIN functionality

### problems
when a key on the matrix keypad is pressed at an unexpected time, the lock won't
open, possible workaround: when the button is pressed accidentally, press it
three more times
