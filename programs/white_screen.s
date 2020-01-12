mov 0xffff, r1 # choose a nice color
mov 0x1000, r3 # 256x256 bit == 4096 words - size of video memory
mov 0x2000, r2 # 0x2000B - where video memory starts. because fuck you, that's why.
mov r1, (r2)+  # paint it!
sob r3, 2 # decrement r3 and jump 2 words back
halt # exiting the loop when reaching r3 == 0

# Congrants, you are awesome!