GENERATES=move my_unlink.so
TRASH=*.in *.out

define test_strace=
	echo abc > 1.in && \
	ecode=`errno $(2) | grep -hIPo '\d+'` && \
	strace -e fault=$(1):error=$(2) -P $(3) ./move 1.in 1.out; \
	[ $$? -eq $${ecode} ] && \
	rm -f 1.in ;
endef

%.so: %.c
	$(CC) -shared $(CFLAGS) -o $@ $<

all: move

test-ecodes: move
	$(foreach ename, EACCES EFAULT ELOOP ENAMETOOLONG ENOENT ENOMEM ENOTDIR EOVERFLOW, $(call test_strace,newfstatat,$(ename),1.in))

	$(foreach ename, EACCES EFAULT EINVAL ELOOP ENAMETOOLONG ENFILE ENOENT ENOMEM ENOTDIR ENXIO EOVERFLOW EPERM ETXTBSY, $(call test_strace,openat,$(ename),1.in))

	$(foreach ename, EFAULT EINTR EIO, $(call test_strace,read,$(ename),1.in))

	$(foreach ename, EINTR EIO, $(call test_strace,close,$(ename),1.in))

	$(foreach ename, EACCES EDQUOT EFAULT EINVAL EISDIR ELOOP ENAMETOOLONG ENFILE ENOENT ENOMEM ENOSPC ENOTDIR ENXIO EOVERFLOW EPERM EROFS ETXTBSY, $(call test_strace,openat,$(ename),1.out))

	$(foreach ename, EDQUOT EFAULT EFBIG EINTR EIO ENOSPC EPERM EPIPE, $(call test_strace,write,$(ename),1.out))

	$(foreach ename, EINTR EIO, $(call test_strace,close,$(ename),1.out))

	$(foreach ename, EACCES EBUSY EFAULT EIO EISDIR ELOOP ENAMETOOLONG ENOENT ENOMEM ENOTDIR EPERM EROFS, $(call test_strace,unlink,$(ename),1.in))

test-overwrite: move
	echo abc > 2.in
	echo This should be gone. > 2a.out
	cp 2a.out 2b.out
	./move 2.in 2a.out
	cmp 2a.out 2b.out; [ $$? -ne 0 ]

test-preload: move my_unlink.so
	echo This should stay. > 3PROTECT.in
	LD_PRELOAD=`pwd`/my_unlink.so ./move 3PROTECT.in 3.out
	[ -f 3PROTECT.in ]

test: test-ecodes test-overwrite test-preload

clean:
	rm -rf $(GENERATES) $(TRASH)
