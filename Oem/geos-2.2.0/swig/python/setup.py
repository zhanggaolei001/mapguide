# $Id: setup.py,v 1.2 2004/07/26 15:40:58 sgillies Exp $
#   
# PyGEOS distutils setup script
#
# Copyright 2004 Sean Gillies, sgillies@frii.com
#
# This is free software; you can redistribute and/or modify it under
# the terms of the GNU Lesser General Public Licence as published
# by the Free Software Foundation. 
# See the COPYING file for more information.
#
# ===========================================================================
#
# Test before installation
#
# $ python setup.py build
# $ python tests/runtests.py -v
# $ sudo python setup.py install
#
# ===========================================================================

from distutils.core import setup, Extension

# We're skipping the metadata for now

# the extension module, source was generated by SWIG from geos.i
#
# Note that until geos is ready to be installed, we're linking against
# the pre-installed library in source/geom/.libs.
extmod = Extension("_geos", ["geos_wrap.cxx"],
                   include_dirs = ["../../source/headers",
                                   "../../source/headers/geos"],
                   libraries = ["stdc++"],
                   extra_objects = ["../../source/geom/.libs/libgeos.a"])

# the python module, generated by SWIG from geos.i
pymod = "geos"

# The setup function
setup(name = "PyGEOS", ext_modules = [extmod], py_modules = [pymod])
