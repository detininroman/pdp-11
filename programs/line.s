mov 0xffff r1 # choose a nice color
mov 0x0000 r2 # choose a nice color
mov 0x002c r3 # number of lines we want to paint
mov 0x0040 r5 # the horizontal center of the screen
add 0x2500 r5 # r5 == 0x2540
mov r1 (r5)   # paint it!
add 0x80 r5   # next line
sob r3 0x0005 # decrement r3 and jump 5 words back before mov r1 (r5)
halt
