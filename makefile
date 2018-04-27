all: 
	+$(MAKE) -C R*
	+$(MAKE) -C C*
clean:
	rm -f C*/*.o C*/sim_checkout 
	rm -f ReadBinaryFilePractice/*.o ReadBinaryFilePractice/rbc
