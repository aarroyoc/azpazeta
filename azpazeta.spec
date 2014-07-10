Name:           azpazeta
Version:        2.1
Release:        1%{?dist}
Summary:        Play custom adventures every day

License:        GPL-2
URL:            http://github.com/AdrianArroyoCalle/azpazeta
Source0:        azpazeta-%{version}.tar.gz

%if 0%{fedora}
BuildRequires:  wxGTK-devel
BuildRequires: 	wxGTK-gl
BuildRequires:	portaudio-devel  
%endif

%if 0%{suse_version}
BuildRequires: libwx_gtk2u_gl-2_8-0-wxcontainer
BuildRequires: libwx_gtk2u_core-2_8-0-wxcontainer 
BuildRequires: libwx_baseu-2_8-0-wxcontainer
BuildRequires: wxWidgets-devel
BuildRequires: alsa-devel
%endif

BuildRequires:	cmake
BuildRequires: 	gcc-c++
BuildRequires:	libstdc++-devel
BuildRequires:	lua-devel
BuildRequires:	glew-devel
BuildRequires:	libogg-devel
BuildRequires:	libvorbis-devel

%description
Azpazeta is a game where you can always find new adventures thanks to the
integrated store

%prep
%setup -q -n azpazeta-%{version}


%build
cmake . -DCMAKE_INSTALL_PREFIX=%{buildroot}/opt
make 

%install
make install


%files
/opt/%{name}

%changelog
* Thu Jul 10 2014 Adrián Arroyo Calle
- New upstream release
