all:
  ## компилируем последний урок
	@echo compiling `ls -l | grep lesson_ | tail -1 | sed 's/.* //g'`....
	@gcc `ls -l | grep lesson | tail -1 | sed 's/.* //g'` -o tmp
	@echo done.
