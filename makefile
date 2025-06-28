name = comparar
especie = especie/

NP ?= 4

com:
	@gcc $(especie)especieArchivo.c $(especie)similitudEspecie.c compararNormal.c -o $(name)

exe: com
	@./$(name)

mpicom:
	@mpicc $(especie)especieArchivo.c $(especie)similitudEspecie.c compararParalelo.c -o $(name)

mpirun: mpicom
	@mpirun -np $(NP) ./$(name)

run: exe clean

mpi: mpirun clean

clean:
	@rm -f *.o $(name)