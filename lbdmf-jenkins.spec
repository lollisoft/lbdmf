Name: lbdmf
Summary: Distributed Multiplatform Framework
Version: 1.0.4.3_final
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

%define _rpmdir .

%if %suse_version <= 910
BuildRequires: bison flex wxGTK-devel >= 2.6.2 unixODBC-devel >= 2.2.11 update-desktop-files gcc-c++
Requires: unixODBC >= 2.2.11 desktop-file-utils
%else
BuildRequires: bison flex wxGTK-devel >= 2.8.8 desktop-file-utils unixODBC-devel >= 2.2.11 gcc-c++
Requires: unixODBC >= 2.2.11 desktop-file-utils
%endif


%description
This is a framework to develop software. It's origin goal was to make me independent from other
(commercial) frameworks and development tools.

This release also is tested to build properly on SuSE Linux 9.1, openSuSE 10.1 and 11.1.

You will need to install the following packages when building on 10.1:

*	GTK+-devel from DVD/CD
*	latest wxGTK version in src tgz from www.wxwidgets.org 
*	pkgconfig from your install DVD/CD
*	unixODBC from the vendor at www.unixodbc.org and compile it.
*	pgsqlodbc.so in version 07.03.0200 from www.postgresql.org

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
echo "[Desktop Entry]" > "%{prefix}/share/applications/wxWrapper.desktop"
echo "Encoding=UTF-8" >> "%{prefix}/share/applications/wxWrapper.desktop"
echo "Name=Rapid Database GUI Designer" >> "%{prefix}/share/applications/wxWrapper.desktop"
echo "Type=Application" >> "%{prefix}/share/applications/wxWrapper.desktop"
echo "Comment=Database designer based on wxWrapper" >> "%{prefix}/share/applications/wxWrapper.desktop"
echo "Exec=wxWrapper" >> "%{prefix}/share/applications/wxWrapper.desktop"
echo "TryExec=wxWrapper" >> "%{prefix}/share/applications/wxWrapper.desktop"
echo "Icon=%{prefix}/share/lbdmf/lbdmf.png" >> "%{prefix}/share/applications/wxWrapper.desktop"
echo "Categories=Development;" >> "%{prefix}/share/applications/wxWrapper.desktop"
rm -f %{prefix}/share/lbdmf/XMIToDMF/XMISettings.xsl
rm -f %{prefix}/share/lbdmf/DMFToXMI/XMISettings.xsl
cat <<'EOF' > %{prefix}/share/lbdmf/XMIToDMF/XMISettings.xsl
<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:variable name="settingsfile_targetdatabase" select="'Sqlite'"/><!-- Preparing a default to use sqlite database  -->
<xsl:variable name="settingsfile_execute_droprules" select="'no'"/><!-- Do not generate drop statements. Default to be used with new models. -->
<xsl:variable name="settingsfile_database_name" select="' '"/>
<xsl:variable name="settingsfile_database_user" select="'dbuser'"/>
<xsl:variable name="settingsfile_database_pass" select="'dbpass'"/>
</xsl:stylesheet>
EOF


ldconfig

%postun

rm %{prefix}/share/applications/wxWrapper.desktop

%clean
rm -rf $RPM_BUILD_ROOT
rm -rf $RPM_BUILD_DIR/file.list.%{name}
rm -rf $RPM_BUILD_DIR/file.list.%{name}.libs
rm -rf $RPM_BUILD_DIR/file.list.%{name}.files
rm -rf $RPM_BUILD_DIR/file.list.%{name}.files.tmp
rm -rf $RPM_BUILD_DIR/file.list.%{name}.dirs

%files -f ../file.list.%{name}
%attr(4755, root, users) %{prefix}/share/lbdmf
%defattr(-,root,root,0755)
