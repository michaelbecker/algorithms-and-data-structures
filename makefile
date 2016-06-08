all:single_list_unit_test_a \
	single_list_unit_test_b

GCC=gcc -std=c99 -Wall

single_list_unit_test_a: single_list_a.c single_list_a.h single_list_unit_test_a.c
	${GCC} single_list_a.c single_list_unit_test_a.c -o single_list_unit_test_a

single_list_unit_test_b: single_list_b.c single_list_b.h single_list_unit_test_b.c
	${GCC} single_list_b.c single_list_unit_test_b.c -o single_list_unit_test_b

.PHONEY:clean
clean:
	- rm *~
	- rm single_list_unit_test_a
	- rm single_list_unit_test_b


