#!/usr/bin/env python
#
# Setup script for Berkeley DB XML package
# $Id: setup.py.in,v 1.47 2005/12/19 19:52:38 gmf Exp $

import os, sys
from distutils.core import setup, Extension

#
# Posix:
#
# db_home, xquery_home, pathan_home, and xerces_home are
# set based on the arguments  passed to the configure script.
# This can be overridden with the --with-berkeleydb, --with-xquery, 
# --with-xerces, and --with-pathan arguments.
#
# Windows: may require further editing to reflect site specifics.
#
if os.name == "posix":
  db_home = "/usr/local/BerkeleyDB.4.4"
  xerces_home = "/Users/gmf/sc/install"
  pathan_home = "/Users/gmf/sc/install"
  xquery_home = "/Users/gmf/sc/install"
else:
  xerces_home = "../../../xerces-c-src"
  pathan_home = "../../../pathan"
  xquery_home = "../../../xquery-1.2.0"
  db_home = "../../../db-4.3.29"

for arg in sys.argv:
  if arg.startswith('--with-berkeleydb='):
    db_home = arg.split('=')[1]
  elif arg.startswith('--with-xerces='):
    xerces_home = arg.split('=')[1]
  elif arg.startswith('--with-pathan='):
    pathan_home = arg.split('=')[1]
  elif arg.startswith('--with-xquery='):
    xquery_home = arg.split('=')[1]

sys.argv = filter(lambda x: not x.startswith("--with-"), sys.argv)

debug = "--debug" in sys.argv or "-g" in sys.argv

# setup complains when passed debug flags for install
if "install" in sys.argv and not "build" in sys.argv:
  sys.argv = filter(lambda x: (x != "--debug") and (x != "-g"), sys.argv)

if os.name == "posix":
  INCLUDES =    ["../../include",
                 os.path.join(db_home, "include")]

  LIBDIRS =     ["../../build_unix/.libs",
                 os.path.join(db_home, "lib"),
                 os.path.join(pathan_home, "lib"),
                 os.path.join(xquery_home, "lib"),
                 os.path.join(xerces_home, "lib")]

  LIBS =        ["dbxml-2",
                 "db_cxx-4",
                 "xquery", "pathan", "xerces-c"]

  DATAFILES =   []

elif os.name == "nt":
  INCLUDES =    ["../../include",
                 os.path.join(db_home, "build_win32"),
                 os.path.join(db_home, "dbinc")]

  if debug:
    LIBDIRS =   ["../../../lib",
                 "../../build_win32/Debug",
                 os.path.join(db_home, "build_win32/Debug"),
                 os.path.join(pathan_home, "lib"),
                 os.path.join(xquery_home, "lib"),
                 os.path.join(xerces_home, "Build/Win32/VC7")]
  
    LIBS =      ["libdbxml22D",
                 "libdb43D", "libxquery12d",
                 "PathanD_7.1", "xerces-c_2D"]

    DATAFILES = [("", ["../../../bin/debug/libdbxml22D.dll",
                       "../../../bin/debug/libdb43D.dll",
                       "../../../bin/debug/libxquery12d.dll",
                       "../../../bin/debug/PathanD_7.1.dll",
                       "../../../bin/debug/xerces-c_2_7D.dll"])]
  else:
    LIBDIRS =   ["../../../lib",
                 "../../build_win32/Release",
                 os.path.join(db_home, "build_win32/Release"),
                 os.path.join(xquery_home, "lib"),
                 os.path.join(pathan_home, "lib"),
                 os.path.join(xerces_home, "Build/Win32/VC7")]
  
    LIBS =      ["libdbxml22",
                 "libdb43", "libxquery12",
                 "Pathan_7.1", "xerces-c_2"]

    DATAFILES = [("", ["../../../bin/libdbxml22.dll",
                       "../../../bin/libdb43.dll",
                       "../../../bin/libxquery12.dll",
                       "../../../bin/Pathan_7.1.dll",
                       "../../../bin/xerces-c_2_7.dll"])]

else:
  print "I don't know anything about your platform '%s'." % os.name
  print "Please check the build instructions for more information"
  sys.exit(1)

# Now run with whatever settings we've got
setup(name = "dbxml",
      version = "2.2.13",
      description = "Berkeley DB XML Python API",
      long_description = """\
      This module provides a complete wrapping of the C++ API
      to the Berkeley DB XML (BDB XML) native XML database.  BDB
      XML can be used to store, retrieve, manage, and query (using
      XQuery) XML documents.""",
      author = "Sleepycat Software",
      author_email = "support@sleepycat.com",
      url = "http://www.sleepycat.com/products/bdbxml.html",
      py_modules = ["dbxml"],
      ext_modules = [Extension("_dbxml", ["dbxml_python_wrap.cpp"],
                               include_dirs = INCLUDES,
                               library_dirs = LIBDIRS,
                               libraries = LIBS)],
      data_files = DATAFILES)
