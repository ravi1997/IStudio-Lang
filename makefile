all:
	$(MAKE) --no-print-directory stage1
	$(MAKE) --no-print-directory stage2
	$(MAKE) --no-print-directory stage3


run1:
	$(MAKE) --no-print-directory -C stageI run


stage1:
	$(MAKE) --no-print-directory -C stageI all

stage2:
	$(MAKE) --no-print-directory all

stage3:
	cd stage\ III
	$(MAKE) --no-print-directory all

clean:
	cd stage\ I
	$(MAKE) --no-print-directory clean
	cd stage\ II
	$(MAKE) --no-print-directory clean
	cd stage\ III
	$(MAKE) --no-print-directory clean

.PHONY: all clean stage1 stage2 stage3 preprocess