Name: Azpazeta
Version: 2.0.0
Release: 2
URL: http://sites.google.com/site/divelmedia
Summary: Strategic-economic game
License: GPL-2
Group: Games
Source: Azpazeta-2.0.0.tar.bz2
BuildRoot: %{_tmppath}/%{name}-%{version}-buildroot
%if 0%{?suse_version}
BuildRequires: libwx_gtk2u_gl-2_8-0-wxcontainer
BuildRequires: libwx_gtk2u_core-2_8-0-wxcontainer 
BuildRequires: libwx_baseu-2_8-0-wxcontainer
BuildRequires: wxWidgets-devel
BuildRequires: glew-devel
%endif

%if 0%{?fedora}
BuildRequires: wxGTK-gl
BuildRequires: wxGTK-devel
BuildRequires: glew-devel
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
/opt/azpazeta/AZPAZETA_JUNO
/opt/azpazeta/lang/es/azpazeta.mo
/opt/azpazeta/lang/fr/azpazeta.mo
/opt/azpazeta/maps/core/OnInit.azps
/opt/azpazeta/maps/core/OnStation.azps
/opt/azpazeta/maps/core/end.xml
/opt/azpazeta/maps/core/mount.xml
/opt/azpazeta/maps/core/start.xml
/opt/azpazeta/maps/core/main.tmx
/opt/azpazeta/AZPSERVER
/opt/azpazeta/maps/core/OnCorner.azps
/opt/azpazeta/maps/core/OnExecutedExtern.azps
/opt/azpazeta/maps/core/database.xml
/opt/azpazeta/maps/core/station.tmx
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
/opt/azpazeta/maps/core/info.xml
/opt/azpazeta/maps/core/main-event.xml
/opt/azpazeta/maps/core/main.tmx
/opt/azpazeta/media/azpazeta.svg
/opt/azpazeta/media/azpmarket.png
/opt/azpazeta/media/blank.png
/opt/azpazeta/media/blank.png0
/opt/azpazeta/media/blank.png1
/opt/azpazeta/media/blank.png2
/opt/azpazeta/media/blank.png3
/opt/azpazeta/media/donate.png
/opt/azpazeta/media/dualsprite.png
/opt/azpazeta/media/housemain.png
/opt/azpazeta/media/water.png
/opt/azpazeta/media/loadgame.png
/opt/azpazeta/media/mapmanager.png
/opt/azpazeta/media/multiplayer.png
/opt/azpazeta/media/options.png
/opt/azpazeta/media/options.xcf
/opt/azpazeta/media/singleplayer.png
/opt/azpazeta/media/vadrixmain.png
/opt/azpazeta/maps/core/INTRODUCTION
/opt/azpazeta/maps/core/rocky-event.xml
/opt/azpazeta/maps/core/rocky.tmx
/opt/azpazeta/maps/core/station-duo-event.xml
/opt/azpazeta/maps/core/station-duo.tmx
/opt/azpazeta/maps/core/station-event.xml
/opt/azpazeta/maps/orwell/info.xml
/opt/azpazeta/maps/orwell/station-event.xml
/opt/azpazeta/maps/orwell/station.tmx
/opt/azpazeta/media/anti-vadrixmain.png
/opt/azpazeta/media/azpazeta.ico
/opt/azpazeta/media/housered.png
/opt/azpazeta/media/houseyellow.png
/opt/azpazeta/media/mountain-inside.png
/opt/azpazeta/media/mountain.png
/opt/azpazeta/media/palacetower.png
/opt/azpazeta/media/road.png
/opt/azpazeta/media/vandraxamain.png
/opt/azpazeta/media/villagers.png
/opt/azpazeta/media/wadrixmain.png

%dir /opt/azpazeta
%dir /opt/azpazeta
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
* Tue Aug 06 2013 Adrian Arroyo Calle
- Ready to release
* Sun Mar 17 2013 Adrian Arroyo Calle
- First release: Bazaar version 50
