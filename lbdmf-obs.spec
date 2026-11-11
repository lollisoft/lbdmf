Name:           lbdmf
Summary:        Distributed Multiplatform Framework
Version:        1.3.6
Release:        1
License:        LGPL-2.1-or-later
Group:          Development/Tools/Other
Source:         %{name}-%{version}.obscpio
Url:            http://lollisoft.de
Packager:       Lothar Behrens <lothar.behrens@lollisoft.de>

BuildRequires:  gcc-c++
BuildRequires:  bison
BuildRequires:  flex
BuildRequires:  pkgconfig
BuildRequires:  libxml2-devel
BuildRequires:  libxslt-devel
BuildRequires:  unixODBC-devel >= 2.2.11
BuildRequires:  update-desktop-files

# Parallelbetrieb-Weiche: Moderne Systeme nutzen wxWidgets 3.2, alte nutzen 2.8
%if 0%{?suse_version} >= 1500
BuildRequires:  wxWidgets-3_2-devel
%else
BuildRequires:  wxGTK-devel >= 2.8.12
%endif

# Laufzeitabhängigkeiten für Bibliotheken ermittelt RPM vollautomatisch
Requires:       unixODBC >= 2.2.11

%description
This is a framework to develop software. It's origin goal was to make me independent from other
(commercial) frameworks and development tools.

%prep
# Erstellt die von Ihrem configure-Wrapper und mkmk erwartete Struktur Projects/lbdmf/
mkdir -p Projects/lbdmf
find . -maxdepth 1 ! -name '.' ! -name 'Projects' ! -name 'BUILDROOT' -exec mv {} Projects/lbdmf/ \;

# Holen wir das configure-Skript auf die oberste Ebene zurück, damit es aus DEVROOT läuft
cp -p Projects/lbdmf/configure ./configure
chmod +x ./configure

%build
export DEVROOT=$(pwd)
export MODULELIB=lbModule.so
export LBXMLFUNCTOR=getlbDOMConfigInstance
export LBMODULEFUNCTOR=getlb_ModuleInstance
export OSTYPE=linux
export PATH=$(pwd)/bin:%{_bindir}:/usr/local/bin:$PATH
export LD_LIBRARY_PATH=$(pwd)/lib:$LD_LIBRARY_PATH

export CFLAGS="%{optflags}"
export CXXFLAGS="%{optflags}"
%if 0%{?suse_version} >= 1500
export WX_CONFIG=%{_bindir}/wx-config-3.2
%else
export WX_CONFIG=%{_bindir}/wx-config
%endif

mkdir -p bin lib plugins

# Ihr eigener configure-Wrapper erzeugt das passende Top-Level makefile mit RPMBUILD=yes
./configure --prefix=%{buildroot}%{_prefix}
make %{?_smp_mflags}

%install
export DEVROOT=$(pwd)
export MODULELIB=lbModule.so
export LBXMLFUNCTOR=getlbDOMConfigInstance
export LBMODULEFUNCTOR=getlb_ModuleInstance
export OSTYPE=linux
export PATH=$(pwd)/bin:%{_bindir}:/usr/local/bin:$PATH
export LD_LIBRARY_PATH=$(pwd)/lib:$LD_LIBRARY_PATH

# Nutzt das von Ihrem configure-Wrapper generierte install-strip Target
make install-strip

# Desktop-Verknüpfung sauber im Buildroot ablegen
mkdir -p %{buildroot}%{_datadir}/applications
cat <<EOF > %{buildroot}%{_datadir}/applications/wxWrapper.desktop
[Desktop Entry]
Encoding=UTF-8
Name=Rapid Database GUI Designer
Type=Application
Comment=Database designer based on wxWrapper
Exec=wxWrapper
TryExec=wxWrapper
Icon=%{_datadir}/lbdmf/lbdmf.png
Categories=Development;GUIDesigner;
EOF

%suse_update_desktop_file wxWrapper

# Standard-XSL-Einstellungen hinterlegen
mkdir -p %{buildroot}%{_datadir}/lbdmf/XMIToDMF
cat <<'EOF' > %{buildroot}%{_datadir}/lbdmf/XMIToDMF/XMISettings.xsl
<xsl:stylesheet version="1.1" xmlns:xsl="http://w3.org" xmlns:exsl="http://exslt.org" extension-element-prefixes="exsl">
<xsl:variable name="settingsfile_targetdatabase" select="'Sqlite'"/>
<xsl:variable name="settingsfile_execute_droprules" select="'no'"/>
<xsl:variable name="settingsfile_database_name" select="' '"/>
<xsl:variable name="settingsfile_database_user" select="'dbuser'"/>
<xsl:variable name="settingsfile_database_pass" select="'dbpass'"/>
</xsl:stylesheet>
EOF

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_bindir}/*
%{_datadir}/applications/wxWrapper.desktop
%{_datadir}/lbdmf/

%changelog
* Wed Nov 11 2026 Lothar Behrens <lothar.behrens@lollisoft.de> - 1.3.6-1
- Dedicated OBS spec file for automated 64-bit builds via mkmk
- Automated wxWidgets slot selection (3.2 vs 2.8)

