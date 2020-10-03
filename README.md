#### Instructions for building l4 related stuff

##### This builds everything 
You can just go to obj/l4/ and run hello program [fiasco build](http://os.inf.tu-dresden.de/fiasco/build.html)

[L4RE build](https://l4re.org/build.html)

after unpacking snapshot:
* make setup (gives at the end:)
```
Boot-images for ARM targets will be placed into obj/l4/arm-*/images.
Boot-images for MIPS targets will be placed into obj/l4/mips32/images.
Check obj/l4/.../conf/Makeconf.boot for path configuration during image builds.
```
* make


#### Building separately:
##### Build Fiasco.OC kernel (for processor family) 
[fiasco build](http://os.inf.tu-dresden.de/fiasco/build.html)

```
cd src/fiasco
make BUILDDIR=mybuild
cd mybuild
make config
make -j8
```

After a successful build the kernel binary will be called *fiasco*. 

-----

##### Build L4Re (for architecture)
```
cd src/l4
mkdir mybuild
make O=mybuild config
cd mybuild
make -j8
```

Run example:
```
make qemu E=hello MODULE_SEARCH_PATH=/path/to/fiasco-build-dir
```
-----
##### Building images
###### Configuration settings/paths
* Configuration settings for building images are taken from *src/l4/conf/Makeconf.boot* 
```
cp src/l4/conf/Makeconf.boot.example src/l4/conf/Makeconf.boot
```
* Add fiasco build directory to MODULE_SEARCH_PATH in Makeconf.boot
* Build images or test it
```
make qemu E=hello

make uimage E=hello 
(images/bootstrap_hello.uimage)
```
* Makeconf.boot can be stored in a build directory under conf/

###### Configure contents of images and generally the entries to boot
```
src/l4/conf/modules.list
```

###### Adding own code
Software is put into packages with structure:
```
pkgname/
        doc/               - Documentation for the package
        include/           - Public headers for the package
        lib/               - Library code
          src/
        server/            - Program code
          src/
```
What is build is defined in the Makefiles in each directory. Typical(more templates in *l4/mk/tmpl*):
```
PKGDIR  ?= .
L4DIR   ?= path/to/your/l4dir

# Statements specific to the used role

include $(L4DIR)/mk/<role>.mk
```

Roles:
* subdir - descent to further subdirectories
* lib - buil library
* prog - build program
* include  - process include files

Example:
```
$ mkdir /tmp/myfirstpkg
$ cd /tmp/myfirstpkg
$ editor Makefile
$ cat Makefile
PKGDIR  ?= .
L4DIR   ?= /path/to/snapshot/src/l4

TARGET          = myfirstprogram
SRC_C           = main.c

include $(L4DIR)/mk/prog.mk
$ editor main.c
$ cat main.c
#include <stdio.h>

int main(void)
{
  printf("Hello!\n");
  return 0;
}
$ make O=/path/to/snapshot/obj/l4/arm-rv-arm9
...
$ ls /path/to/snapshot/obj/l4/arm-rv-arm9/bin/arm_rv/l4f/myfirstprogram
/path/to/snapshot/obj/l4/arm-rv-arm9/bin/arm_rv/l4f/myfirstprogram
```

**TIP**: to not use build dir arg O= of the l4 (if using one build dir), put *O=/path/to/the/build-dir* into *L4DIR/Makeconf.local*

**Notes**
* explicit function parameters even for *void*
* modules.list possible settings can be seen in src/l4/conf/modules.list
* if using non-default MODULES_LIST, settings in Makeconf.boot are not used, therefore fiasco build dir needs to be added to MODULE_SEARCH_PATH
* if using *roottask moe --init=rom/hello0* in modules.list, then it just prints hello message, MOE starts the hello0 binary. If using hello0.cfg, MOE starts NED, and NED loads the hello0.cfg file, which in turn runs hello0 binary

-----

##### Build L4Linux
[L4Linux build](https://l4linux.org/build.shtml)
[L4 build is not set](http://os.inf.tu-dresden.de/pipermail/l4-hackers/2011/004605.html)
```
cd l4linux
mkdir mybuild
make O=mybuild x86_64_defconfig
cd mybuild
make menuconfig (set l4 build dir)
make -j8
```

Problems:

after bulding grub image the linux panics!

#### Custom code
afer unpacking in README.md or .html there are examples

