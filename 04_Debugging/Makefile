CFLAGS=-O0 -g
GENERATES=*.o range *.out

all: range

clean:
	rm -f $(GENERATES)

test-%: range
	gdb ./range -x gdb_scenario_$(subst test-,,$@).txt | grep @@@ > $(subst test-,,$@).out
	cmp $(subst test-,,$@).out correct_output_$(subst test-,,$@).txt

test: test-1 test-2

