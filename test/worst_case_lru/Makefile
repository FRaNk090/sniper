TARGET=worst_case_lru
include ../shared/Makefile.shared

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -o $(TARGET)

run_$(TARGET):
	../../run-sniper -v -n 1 -c gainestown -c fan --roi -- ./worst_case_lru -p 1

CLEAN_EXTRA=viz
