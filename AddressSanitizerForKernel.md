# Overview #

Kernel Address sanitizer (KASan) is a dynamic memory error detector. It provides
a fast and comprehensive solution for finding use-after-free and out-of-bounds
bugs.

Currently KASan is supported only for x86\_64 architecture and requires that the
kernel be built with the SLUB allocator.

AddressSanitizer for Linux kernel:
  * Is based on compiler instrumentation (fast)
  * Detects OOB for both writes and reads
  * Provides strong UAF detection (based on delayed memory reuse)
  * Does prompt detection of bad memory accesses
  * Prints informative reports

# Details #

Pre-alpha repository: https://github.com/google/kasan/tree/kasan . To checkout, do
```
git clone http://github.com/google/kasan -b kasan
```

More extensive documentation: https://github.com/google/kasan/blob/kasan/Documentation/kasan.txt

## Reports ##

To simplify reading the reports you can use our [symbolizer script](https://code.google.com/p/address-sanitizer/source/browse/trunk/tools/kasan_symbolize.py):
```
$ cat report
...
[  107.327411]  [<ffffffff8110424c>] call_usermodehelper_freeinfo+0x2c/0x30
[  107.328668]  [<ffffffff811049d5>] call_usermodehelper_exec+0xa5/0x1c0
[  107.329816]  [<ffffffff811052b0>] call_usermodehelper+0x40/0x60
[  107.330987]  [<ffffffff8146c15e>] kobject_uevent_env+0x5ee/0x620
[  107.332035]  [<ffffffff8146c19b>] kobject_uevent+0xb/0x10
[  107.333108]  [<ffffffff8173bd7f>] net_rx_queue_update_kobjects+0xaf/0x150
...
```
```
$ cat report | ./kasan_symbolize.py path/to/kernel/
...
 [<ffffffff8110424c>] call_usermodehelper_freeinfo+0x2c/0x30 ./kernel/kmod.c:265
 [<ffffffff811049d5>] call_usermodehelper_exec+0xa5/0x1c0 ./kernel/kmod.c:612
 [<ffffffff811052b0>] call_usermodehelper+0x40/0x60 ./kernel/kmod.c:642
 [<ffffffff8146c15e>] kobject_uevent_env+0x5ee/0x620 ./lib/kobject_uevent.c:311
 [<ffffffff8146c19b>] kobject_uevent+0xb/0x10 ./lib/kobject_uevent.c:333
 [<     inlined    >] net_rx_queue_update_kobjects+0xaf/0x150 rx_queue_add_kobject ./net/core/net-sysfs.c:771
 [<ffffffff8173bd7f>] net_rx_queue_update_kobjects+0xaf/0x150 ./net/core/net-sysfs.c:786
...
```

## Instrumentation ##

The most recent instructions are available at https://github.com/google/kasan/blob/kasan/Documentation/kasan.txt

KASan uses compile-time instrumentation for checking every memory access,
therefore you will need a certain version of GCC >= 4.9.2

Currently KASan is supported only for x86\_64 architecture and requires that the
kernel be built with the SLUB allocator.

To enable KASAN configure kernel with:

> CONFIG\_KASAN = y

and choose between CONFIG\_KASAN\_OUTLINE and CONFIG\_KASAN\_INLINE. Outline/inline
is compiler instrumentation types. The former produces smaller binary the
latter is 1.1 - 2 times faster. Inline instrumentation requires GCC 5.0 or
latter.

Currently KASAN works only with the SLUB memory allocator.
For better bug detection and nicer report, enable CONFIG\_STACKTRACE and put
at least 'slub\_debug=U' in the boot cmdline.

# Trophies #

**Fixed:**
  * Out-of-bounds read in net/ipv4:
http://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/commit/?id=aab515d7c32a34300312416c50314e755ea6f765

  * Out-of-bounds in sd\_revalidate\_disk (drivers/scsi/sd.c):
http://www.spinics.net/lists/linux-scsi/msg68519.html

http://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/commit/?id=984f1733fcee3fbc78d47e26c5096921c5d9946a

  * Use-after-free in aio\_migratepage:
Sent to  linux-aio mainling list, not visible on web.

https://code.google.com/p/address-sanitizer/wiki/AddressSanitizerForKernelReports

http://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/commit/?id=5e9ae2e5da0beb93f8557fc92a8f4fbc05ea448f

  * Out-of-bounds in ip6\_finish\_output2:
http://www.spinics.net/lists/netdev/msg250734.html

http://seclists.org/oss-sec/2013/q3/683

http://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/commit/?id=2811ebac2521ceac84f2bdae402455baa6a7fb47

http://www.spinics.net/lists/netdev/msg282080.html

  * Out-of-bounds in ftrace\_regex\_release (kernel/trace/ftrace.c):
http://www.spinics.net/lists/kernel/msg1612400.html

https://lkml.org/lkml/2013/10/20/126

  * Use-after-free in ext4\_mb\_new\_blocks:

http://permalink.gmane.org/gmane.comp.file-systems.ext4/40353

http://permalink.gmane.org/gmane.comp.file-systems.ext4/41108

  * Race (use-after-free) in ip4\_datagram\_release\_cb:
http://www.spinics.net/lists/netdev/msg285419.html

http://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/commit/?id=9709674e68646cee5a24e3000b3558d25412203a

**Confirmed:**

  * Use-after-free in put\_anon\_vma:
https://lkml.org/lkml/2014/6/6/186

  * Out-of-bounds read in d\_lookup\_rcu (fs/dcache.c):
https://code.google.com/p/address-sanitizer/wiki/AddressSanitizerForKernelReports

http://lkml.org/lkml/2013/10/3/493

  * Out-of-bounds in get\_wchan (arch/x86/kernel/process\_64.c):
http://lkml.org/lkml/2013/9/3/286

  * Stack-out-of-bounds in idr\_for\_each
https://lkml.org/lkml/2014/6/23/516

  * Out-of-bounds memory write in fs/ecryptfs/crypto.c
https://lkml.org/lkml/2014/11/21/230


**Not confirmed:**
  * Use-after-free in drivers/net/ethernet/intel/e1000:
http://permalink.gmane.org/gmane.linux.drivers.e1000.devel/12441
  * Use-after-free in call\_usermodehelper (kernel/kmod.c):
http://www.lkml.org/lkml/2013/8/21/431
  * Use-after-free in SyS\_remap\_file\_pages:
https://lkml.org/lkml/2013/9/17/30
    * Use-after-free in ata\_qc\_issue (drivers/ata/libata-core.c):
http://www.spinics.net/lists/linux-ide/msg46213.html
    * Racy use-after-free in list\_del\_event
https://lkml.org/lkml/2014/6/18/318

[Bugs found by external users](https://www.google.com/?gws_rd=ssl#q=site%3Alkml.org+%22Memory+state+around+the+buggy+address%22+%22Sasha+Levin%22)