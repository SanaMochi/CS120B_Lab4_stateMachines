# Test file for "Lab4_stateMachines"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
#test "PINA: 0x00, PINB: 0x00 => PORTC: 0"
# Set inputs
#setPINA 0x00
#setPINB 0x00
# Continue for several ticks
#continue 2
# Set expect values
#expectPORTC 0
# Check pass/fail
#checkResult

# Test 1
test "All possible paths tested & increment on 0x09"
set state = Init
setPINA 0x00
continue 5
expect state wait
setPINA 0x00
continue 5
expect state wait
setPINA 0x01
continue 5
expect state waitInc
expectPORTC 0x08
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5 
expect state wait
setPINA 0x01
continue 5
expect state waitInc
expectPORTC 0x09
setPINA 0x00
continue 5
expect state wait
expectPORTC 0x09
setPINA 0x01
continue 5
expect state waitInc
expectPORTC 0x09
setPINA 0x03
continue 5
expect state waitReset
setPINA 0x00
continue 5
expect state wait
checkResult

# Test 2
test "PINA: 0x03 => PORTC: 0, state: wait"
set state = Init
setPINA 0x03
continue 5
expect state waitReset
expectPORTC 0x00
checkResult

# Test 3
test "PINA: 0x01 => PORTC: 8, state: waitInc"
set state = Init
setPINA 0x01
continue 5
expect state waitInc
expectPORTC 0x08
checkResult

# Test 4
test "PINA: 0x02 => PORTC: 6, state: waitDec"
set state = Init
setPINA 0x02
continue 5
expect state waitDec
expectPORTC 0x06
checkResult

# Test 5
test "Decrement on 0x00"
set state = Init
setPINA 0x02
continue 5
expectPORTC 0x06
expect state waitDec
setPINA 0x00
continue 5
expect state wait
setPINA 0x02
continue 5
expectPORTC 0x05
expect state waitDec
setPINA 0x00
continue 5
expect state wait
setPINA 0x03
continue 5
expectPORTC 0x00
expect state waitReset
setPINA 0x00
continue 5
expectPORTC 0x00
expect state wait
setPINA 0x02
continue 5
expectPORTC 0x00
expect state waitDec
#setPINA 0x00
#continue 5
#expectPORTB 0x01
#expect state waitRise1
#setPINA 0x01
#continue 5
#expectPORTB 0x02
#expect state waitFall1
checkResult

# Test 6
test "PINA: 0x00, 0x02, 0x00, 0x02, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 => PORTC: 0x08, state: waitInc"
set state = Init
setPINA 0x00
continue 5
expectPORTC 0x07
expect state wait
setPINA 0x02
continue 5
expect state waitDec
setPINA 0x00
continue 5
expectPORTC 0x06
expect state wait
setPINA 0x02
continue 5
expect state waitDec
setPINA 0x00
continue 5
expectPORTC 0x05
expect state wait
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5
expectPORTC 0x06
expect state wait
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5
expectPORTC 0x07
expect state wait
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5
expectPORTC 0x08
expect state wait
checkResult

# Test 7
test "PINA: 0x03, Inc to max => PORTC: 0x09, state: waitInc"
setPINA 0x03
continue 5
expect state waitReset
setPINA 0x00
continue 5
expectPORTC 0x00
expect state wait
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5
expectPORTC 0x01
expect state wait
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5
expectPORTC 0x02
expect state wait
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5
expectPORTC 0x03
expect state wait
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5
expectPORTC 0x04
expect state wait
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5
expectPORTC 0x05
expect state wait
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5
expectPORTC 0x06
expect state wait
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5
expectPORTC 0x07
expect state wait
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5
expectPORTC 0x08
expect state wait
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5
expectPORTC 0x09
expect state wait
setPINA 0x01
continue 5
expect state waitInc
setPINA 0x00
continue 5
expectPORTC 0x09
expect state wait
checkResult

#test “cntA0 > 100 => PORTB: 0x0F”
#set exampleTick::cntA0 = 101
#set state = pressA1
#setPINA 0x02
#continue 2
#expectPORTB 0x0F
#expect state pressA1
#checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
