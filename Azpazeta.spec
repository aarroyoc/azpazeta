Name: Azpazeta
Version: 2.0.0
Release: 2
URL: http://sites.google.com/site/divelmedia
Summary: Strategic-economic game
License: GPLv2
Group: Games
Source: Azpazeta-2.0.0.tar.bz2
BuildRoot: %{_tmppath}/%{name}-%{version}-buildroot
%if 0%{?suse_version}
BuildRequires: libwx_gtk2u_gl-2_8-0-wxcontainer
BuildRequires: libwx_gtk2u_core-2_8-0-wxcontainer 
BuildRequires: libwx_baseu-2_8-0-wxcontainer
BuildRequires: wxWidgets-devel
%endif

%if 0%{?fedora}
BuildRequires: wxGTK-gl
BuildRequires: wxGTK-devel
%endif

%if 0%{?rhel version} || 0%{?centos version}
BuildRequires: wxGTK-gl
BuildRequires: wxGTK-devel

%endif
BuildRequires: cmake
BuildRequires: gcc-c++
BuildRequires: libstdc++-devel
BuildRequires: lua-devel


%description
Azpazeta is the sandbox strategy-economic game.

%prep
%setup -c
ls
cmake . -DCMAKE_INSTALL_PREFIX=%{buildroot}/opt

%build

make

%install
rm -rf $RPM_BUILD_ROOT
make install

%post


%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(0755,root,root)
/opt/azpazeta/bin/AZPAZETA_JUNO
/opt/azpazeta/lang/es/azpazeta.mo
/opt/azpazeta/lang/fr/azpazeta.mo
/opt/azpazeta/maps/core/OnInit.azps
/opt/azpazeta/maps/core/OnStation.azps
/opt/azpazeta/maps/core/end.xml
/opt/azpazeta/maps/core/mount.xml
/opt/azpazeta/maps/core/start.xml
/opt/azpazeta/maps/data.xml
/opt/azpazeta/maps/orwell/OnStation.azps
/opt/azpazeta/maps/orwell/mount.xml
/opt/azpazeta/maps/orwell/station.xml
/opt/azpazeta/media/azpazeta.png
/opt/azpazeta/media/green.png
/opt/azpazeta/media/red.png
/opt/azpazeta/options/options.xml
/opt/azpazeta/scripts/Init.azps
/opt/azpazeta/shaders/fragment.fs
/opt/azpazeta/shaders/vertex.vs

%dir /opt/azpazeta
%dir /opt/azpazeta/bin
%dir /opt/azpazeta/lang
%dir /opt/azpazeta/lang/es
%dir /opt/azpazeta/lang/fr
%dir /opt/azpazeta/maps
%dir /opt/azpazeta/maps/core
%dir /opt/azpazeta/maps/orwell
%dir /opt/azpazeta/media
%dir /opt/azpazeta/options
%dir /opt/azpazeta/scripts
%dir /opt/azpazeta/shaders

%changelog
* Sun Mar 17 2013 Adrian Arroyo Calle
- First release: Bazaar version 29
