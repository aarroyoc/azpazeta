Name: Azpazeta
Version: 2.0.0
Release: 2
URL: http://sites.google.com/site/divelmedia
Summary: Azpazeta
License: GPL
Group: Games
BuildRoot: %{_tmppath}/%{name}-%{version}-buildroot

%description
Azpazeta is the sandbox strategy-economic game.

%prep
cmake . -DCMAKE_INSTALL_PREFIX=%{buildroot}/usr

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
/usr/bin/AZPAZETA_JUNO

%changelog
* Mon Nov 5 2012 Adrian Arroyo Calle
- Compatible con Divel RT
* Mon Oct 16 2012 Adrian Arroyo Calle
- Ahora con GUI y en Java
* Wed May 23 2012 Adrian Arroyo Calle
- Primera version
