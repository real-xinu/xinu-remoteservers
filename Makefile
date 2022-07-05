all:
	@echo recompiling the remote file server
	@(cd rfserver; make)
	@echo recompiling the remote disk server
	@(cd rdserver; make)

