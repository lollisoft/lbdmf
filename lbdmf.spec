Name: lbdmf
Summary: Distributed Multiplatform Framework
Version: 1.0rc1
Release: 1
License: LGPL
Group: Development/Tools
Source: %{name}-%{version}.tgz
BuildRoot: %{_tmppath}/%{name}-%{version}-buildroot
Packager: Lothar Behrens <lothar.behrens@lollisoft.de>
Distribution: SUSE
Prefix: /usr
Url: http://www.lollisoft.de
Autoreqprov: on
Provides: lbdmf



%description
This is a framework to develop software. It's origin goal was to make me independent from other
(commercial) frameworks and development tools.

%prep
rm -rf $RPM_BUILD_ROOT 
mkdir $RPM_BUILD_ROOT

%setup -q

%build
CFLAGS="$RPM_OPT_FLAGS" CXXFLAGS="$RPM_OPT_FLAGS" \
./configure --prefix=$RPM_BUILD_ROOT%{prefix}
if [ "$SMP" != "" ]; then
  make -j 2
else
  make
fi

%install
make DESTDIR="%{buildroot}" install-strip

cd $RPM_BUILD_ROOT

find . -type d -fprint $RPM_BUILD_DIR/file.list.%{name}.dirs
find . -type f -fprint $RPM_BUILD_DIR/file.list.%{name}.files.tmp
sed '/\/man\//s/$/.gz/g' $RPM_BUILD_DIR/file.list.%{name}.files.tmp > $RPM_BUILD_DIR/file.list.%{name}.files
find . -type l -fprint $RPM_BUILD_DIR/file.list.%{name}.libs
sed '1,2d;s,^\.,\%attr(-\,root\,root) \%dir ,' $RPM_BUILD_DIR/file.list.%{name}.dirs > $RPM_BUILD_DIR/file.list.%{name}
sed 's,^\.,\%attr(-\,root\,root) ,' $RPM_BUILD_DIR/file.list.%{name}.files >> $RPM_BUILD_DIR/file.list.%{name}
sed 's,^\.,\%attr(-\,root\,root) ,' $RPM_BUILD_DIR/file.list.%{name}.libs >> $RPM_BUILD_DIR/file.list.%{name}

%post
ldconfig

%clean
rm -rf $RPM_BUILD_ROOT
rm -rf $RPM_BUILD_DIR/file.list.%{name}
rm -rf $RPM_BUILD_DIR/file.list.%{name}.libs
rm -rf $RPM_BUILD_DIR/file.list.%{name}.files
rm -rf $RPM_BUILD_DIR/file.list.%{name}.files.tmp
rm -rf $RPM_BUILD_DIR/file.list.%{name}.dirs

%files -f ../file.list.%{name}

%defattr(-,root,root,0755)
