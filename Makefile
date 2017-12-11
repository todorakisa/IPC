make:
	gcc cyclicWrite.c -lrt -o write.out 
	#gnome-terminal -x sh -c "sudo ./write.out"
	gcc cyclicRead.c -lrt -o read.out
	sudo gnome-terminal -x sh -c "sudo ./write.out"
	sudo ./read.out
