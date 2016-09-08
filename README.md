# FIA-NET cpp-commons

This package contains some of the software we're using and developing daily at
Fia-Net, for our own products (Certissim, TULIPE). We started to build this
component collection in 2008 and since that time, we have been constantly
adding and updating stuff. Time has come to share some of our source code with
the open-source community.

We will be gradually adding components, but we need to make the source code
readable (with comments in English).

This software started being written at Fia-Net during the summer of 2008, while
we were working on a complete rewrite of our scoring engine. It was originally
written on Solaris 8 (Sparc CPUs) with GCC 3, and migrated to GNU/Linux on
x86 in 2013.

As usual, some choices and compromises had to be made. Every class in this
repository has been written so that it could be quickly used. Some libraries
and classes have been re-factored many times while some are almost identical
to their original form.

## Supported platforms
Our source code is known to work on Linux / x86, on 32 and 64 bit platforms.

## How to build
See the BUILD file for more details.

## Examples
There is no example code for now. But we try to provide unit tests in each
library folder so you can have a glimpse of how to use the libs.

## Contributing
This software package is provided "as-is".
You can report bugs and issues on [github](https://github.com/fia-net/cpp-commons/issues)

## License
This software is licensed under the
[Apache License v2.0](http://www.apache.org/licenses/LICENSE-2.0).
