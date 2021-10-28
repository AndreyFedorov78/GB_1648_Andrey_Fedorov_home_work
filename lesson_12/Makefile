APP=tmp
ALLFILES=`ls *.c`
all:
	  @echo compiling $(ALLFILES).
	  @gcc $(ALLFILES) -o $(APP)
		@echo use \'make help\' for info.
debug:
			  @echo compiling $(ALLFILES).
			  @gcc $(ALLFILES) -o $(APP) -DDEBUG
				@echo use \'make help\' for info.
run:
		@echo remooving $(APP).
		@rm -f $(APP)
		@echo compiling $(ALLFILES).
		@gcc $(ALLFILES) -o $(APP)
		@echo  starting $(APP):
		./$(APP)
help:
	  @echo ''
		@echo \'make\' or \'make all\'	compiling all .c files to $(APP);
		@echo \'make debug\'	compiling all .c files to $(APP) with DEBUG option;
		@echo \'make run\'	compiling all .c files to $(APP) and autostart $(APP);
		@echo \'make help\'	view keys info
	  @echo ''
