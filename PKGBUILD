# Maintainer: Adrian Arroyo Calle <adrian.arroyocalle@gmail.com>


pkgname=azpazeta
pkgver=2.0.0
pkgrel=1
pkgdesc="The strategy, economic game"
arch=('i686' 'x86_64')
url="http://launchpad.net/azpazeta/"
license=('GPL2')
depends=('lua' 'glew' 'wxgtk' 'mesa-libgl' 'cmake')
#install="${pkgname}.install"

source=(Azpazeta-${pkgver}.tar.bz2)

md5sums=('6d5a580d000c33d1c652607bc1e60a31')

# Setting this to true activates the compilation and packaging
# of the plugins which are not yet officially released.
# NOTE: doesn't work at the moment.
_USE_PLUGINS=false

# Setting this to true activates the compilation and packaging
# of retroshare-nogui
_USE_NOGUI=true

# Setting this to true activates the sshserver in retroshare-nogui
_USE_SSHSERVER=false

build() {
  cd "${srcdir}"

  msg "Configuring Azpazeta"
  cmake . -DCMAKE_INSTALL_PREFIX=/opt
  msg "Building Azpazeta"
  make
}

package() {

  # --- Install Files ---

  msg "Installing files to fakeroot-environment..."

  make DESTDIR=${pkgdir} install
}

