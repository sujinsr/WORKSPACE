all : ipcm

ipcm: ipcmanager.o sysv_ipc.o ipclist.o
	gcc ipcmanager.o sysv_ipc.o ipclist.o -o ipcm
	
ipcmanager.o: ipcmanager.c
	gcc -c ipcmanager.c

sysv_ipc.o: sysv_ipc.c
	gcc -c sysv_ipc.c
	
ipclist.o: ipclist.c
	gcc -c ipclist.c

clean:
	rm *.o ipcm