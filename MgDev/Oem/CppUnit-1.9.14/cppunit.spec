%define  RELEASE 1
%define  rel     %{?CUSTOM_RELEASE} %{!?CUSTOM_RELEASE:%RELEASE}

%define lib_name cppunit

Name: cppunit
Version: 1.9.14
Release: %rel

Summary: C++ Port of JUnit Testing Framework
Copyright: LGPL
Group: Development/Libraries
Vendor: The CppUnit Project 
Packager: Bastiaan Bakker <bastiaan.bakker@lifeline.nl>
Url: http://cppunit.sourceforge.net/

Source: ftp://download.sourceforge.net/pub/sourceforge/cppunit/%name-%version.tar.gz

Prefix: %_prefix
BuildRoot: %_tmppath/%name-%version-root

%description
CppUnit is the C++ port of the famous JUnit framework for unit testing.
Test output is in XML for automatic testing and GUI based for supervised tests.

%package doc
Summary: HTML formatted API documention for Log for C++
Group: Development/Libraries
Requires: %name = %version

%description doc
The %name-doc package contains HTML formatted API documention generated by
the popular doxygen documentation generation tool.

%prep
rm -rf $RPM_BUILD_ROOT

%setup
CFLAGS="$RPM_OPT_FLAGS" ./configure --prefix=%{prefix} --enable-doxygen 

%build
make

%install
rm -rf $RPM_BUILD_ROOT

make prefix=$RPM_BUILD_ROOT%{prefix} install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,755)
%attr(755,root,root) %prefix/lib/lib*.so.*
%doc AUTHORS COPYING INSTALL NEWS README THANKS ChangeLog
%attr(755,root,root) %prefix/bin/cppunit-config
%prefix/include/*
%prefix/man/*
%prefix/share/*
%attr(755,root,root) %prefix/lib/lib*.so
%attr(644,root,root) %prefix/lib/*.*a

%files doc
%doc doc/html/*
