set terminal png enhanced size 2048,1024
set output "paciwar.png"
set title "Frame deltatime over game execution"
plot "./paciwar.ntrace" using 1:2
