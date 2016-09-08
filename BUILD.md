# FIA-NET cpp-commons

## Building the packages

We have developped our build system around GNU make. By using some macro and
configuration files, we are able to build libraries and applications quite
quickly.

There is no autoconf / automake steps because our software is built on a
relatively stable environment and we do not have the need for
using GNU auto-tools.

The top-level Makefile defines a FIANET_COMMONS_DIR variable, that contains
the acces path to the config/ directory of this software package.

The config/ directory contains some configuration files that
you should copy and modify to suit your environment.

Once configured, building the libraries is done by running "make" from the
top-level directory or the src/ directory.