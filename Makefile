WritingTestFiles = WritingTest.c platform/threads.c utility/benchmark.c

AlignmentTestFiles = AlignmentTest.c platform/threads.c platform/atomic.c utility/benchmark.c

all: writing crw crw_unaligned crw_unaligned_locked

writing: $(WritingTestFiles)
	gcc -o writing $(WritingTestFiles)

crw: $(AlignmentTestFiles)
	gcc -o crw $(AlignmentTestFiles)

crw_unaligned: $(AlignmentTestFiles)
	gcc -o crw_unaligned $(AlignmentTestFiles) -DUNALIGNED

crw_unaligned_locked: $(AlignmentTestFiles)
	gcc -o crw_unaligned_locked $(AlignmentTestFiles) -DUNALIGNED -DLOCKED
