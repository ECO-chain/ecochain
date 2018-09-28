
Debian
====================
This directory contains files used to package ecocd/ecoc-qt
for Debian-based Linux systems. If you compile ecocd/ecoc-qt yourself, there are some useful files here.

## ecoc: URI support ##


ecoc-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install ecoc-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your ecoc-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

ecoc-qt.protocol (KDE)

