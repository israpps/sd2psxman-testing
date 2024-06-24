all::
	$(MAKE) -C sd2psxman MODE=FS
	$(MAKE) -C sd2psxman MODE=RPC
	$(MAKE) -C test_app

clean::
	$(MAKE) -C sd2psxman MODE=FS clean
	$(MAKE) -C sd2psxman MODE=RPC clean
	$(MAKE) -C test_app clean