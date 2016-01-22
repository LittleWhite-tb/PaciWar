set terminal png enhanced size 2048,1024
set output "paciwar.png"
set title "Frame deltatime over game execution"
set yrange [0:60]
set y2tics
set y2range [0:1000]
plot "./paciwar.ntrace" using 1:2 title "Delta Time", \
	 "./paciwar.ntrace" using 1:3 title "Nb ennemies" with line axes x1y2
