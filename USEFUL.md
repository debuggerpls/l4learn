#### Useful tips/tricks:

* If using VS Code: Add *L4_Build/../include* to *includePath* in *c_cpp_properties.json*. 
* If using C++ Standard Library, add this to Makefile
```
REQUIRES_LIBS    = libstdc++
DEPENDS_PKGS     = $(REQUIRES_LIBS)
```
