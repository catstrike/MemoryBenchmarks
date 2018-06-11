WritingTest: WritingTest.c platform/threads.c
	gcc -o WritingTest WritingTest.c platform/threads.c

AlignmentTest: AlignmentTest.c platform/threads.c
	gcc -o AlignmentTest AlignmentTest.c platform/threads.c
