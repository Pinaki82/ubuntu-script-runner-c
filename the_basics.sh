#!/bin/bash

yes | sudo apt update && sudo apt upgrade && \
yes | sudo apt update && \
yes | sudo apt list --upgradable && \
yes | sudo apt upgrade && \
yes | sudo apt update && \
yes | sudo apt install -f && \

# --download-only

sudo apt --download-only build-essential && \
sudo apt --download-only wget && \
sudo apt --download-only curl && \
sudo apt --download-only git && \
sudo apt --download-only git-lfs && \
sudo apt --download-only gitk && \
sudo apt --download-only git-gui && \
sudo apt --download-only patch && \
sudo apt --download-only make && \
sudo apt --download-only cmake && \
sudo apt --download-only diffutils && \
sudo apt --download-only git-extras && \
sudo apt --download-only git-flow && \
sudo apt --download-only diffstat && \
sudo apt --download-only bash && \
sudo apt --download-only fish && \
sudo apt --download-only llvm && \
sudo apt --download-only clang && \
sudo apt --download-only clangd && \
sudo apt --download-only clang-tidy && \
sudo apt --download-only clang-tools && \
sudo apt --download-only lld && \
sudo apt --download-only python3-pip && \

sudo apt --download-only ntp && \
sudo apt --download-only gnome-disk-utility && \
sudo apt --download-only rsync && \
sudo apt --download-only timeshift && \
sudo apt --download-only grsync && \
python -m pip --download-only --upgrade pip && \
python3 -m pip --download-only --upgrade pip && \
sudo apt --download-only pipx && \
sudo apt --download-only gufw && \
sudo apt --download-only resolvconf && \
sudo apt --download-only clamtk-gnome && \
sudo apt --download-only chkrootkit && \
sudo apt --download-only rkhunter && \
sudo apt --download-only firejail && \
sudo apt --download-only fish && \





# install from downloaded cache
sudo apt install build-essential && \
sudo apt install wget && \
sudo apt install curl && \
sudo apt install git && \
sudo apt install git-lfs && \
sudo apt install gitk && \
sudo apt install git-gui && \
sudo apt install patch && \
sudo apt install make && \
sudo apt install cmake && \
sudo apt install diffutils && \
sudo apt install git-extras && \
sudo apt install git-flow && \
sudo apt install diffstat && \
sudo apt install bash && \
sudo apt install fish && \
sudo apt install llvm && \
sudo apt install clang && \
sudo apt install clangd && \
sudo apt install clang-tidy && \
sudo apt install clang-tools && \
sudo apt install lld && \
sudo apt install python3-pip && \

sudo apt install ntp && \
sudo apt install gnome-disk-utility && \
sudo apt install rsync && \
sudo apt install timeshift && \
sudo apt install grsync && \
python -m pip install --upgrade pip && \
python3 -m pip install --upgrade pip && \
sudo apt install pipx && \
sudo apt install gufw && \
sudo apt install resolvconf && \
sudo apt install clamtk-gnome && \
sudo apt install chkrootkit && \
sudo apt install rkhunter && \
sudo apt install firejail && \
sudo apt install fish && \

# ======================INSTALL OH-MY-BASH======================================
# ------------------------------------------------------------------------------
# OH-MY-BASH:
bash -c "$(curl -fsSL https://raw.githubusercontent.com/ohmybash/oh-my-bash/master/tools/install.sh)"
# ------------------------------------------------------------------------------
# Bash Language Server
# https://github.com/bash-lsp/bash-language-server.git
yes | sudo npm i -g bash-language-server && \
# bash-language-server --help
# ------------------------------------------------------------------------------
# Fish-shell-like autocompletion in Bash-shell
# Ecosia: fish shell like autocomplete in bash
# https://unix.stackexchange.com/questions/109366/does-bash-have-similar-features-such-as-fishs-autosuggestions-and-highlighting
# https://github.com/akinomyoga/ble.sh
# https://github.com/dvorka/hstr


yes | sudo apt install trash-cli && \

git clone --recursive --depth 1 --shallow-submodules https://github.com/akinomyoga/ble.sh.git && \
make -C ble.sh install PREFIX=~/.local && \
echo 'source ~/.local/share/blesh/ble.sh' >> ~/.bashrc && \
source ~/.bashrc && \
source ~/.bash_aliases && \
trash ble.sh && \

# Intel CPU support:
yes | sudo apt install software-properties-common apt-transport-https ca-certificates curl -y && \
yes | sudo apt install xserver-xorg-video-intel && \
yes | sudo apt install mesa-utils && \
yes | sudo apt install intel-opencl-icd libmfx1 && \
yes | sudo apt install vainfo && \
yes | sudo apt install libmfx1 && \
yes | sudo apt install i965-va-driver && \

# Install the most essential core build tool:

yes | sudo apt install build-essential dkms module-assistant linux-headers-$(uname -r) && \

# Install the common properties package (will be needed later):

yes | sudo apt install software-properties-common && \


# Install 'c': Use C as a shell scripting language:
# https://github.com/ryanmjacobs/c

cd ~/ && \
yes | sudo apt install build-essential trash-cli && \
wget https://raw.githubusercontent.com/ryanmjacobs/c/master/c && \
sudo install -m 755 c /usr/bin/c && \
trash c && \

# Install hdparm (to run commands like: sudo hdparm -I /dev/sdX | grep "Security"):
# https://installati.one/install-hdparm-debian-11/
sudo apt -y install hdparm


# Install GVim+Vim:

# apt search vim-gtk
yes | sudo apt install vim-gtk3 && \
# Or, if you do not want the GUI Vim,
yes | sudo apt install vim && \


# LSB support:
yes | sudo apt install lsb-release && \

# Codecs:
# https://www.sys-hint.com/1075-Installing-Multimedia-Codecs-on-Debian-10
# https://phoenixnap.com/kb/add-apt-repository-command-not-found-ubuntu

yes | sudo apt install software-properties-common && \
yes | sudo apt-add-repository non-free && \
yes | sudo apt-add-repository contrib && \
# https://serverfault.com/questions/240920/how-do-i-enable-non-free-packages-on-debian
yes | sudo apt-add-repository --component non-free && \

yes | sudo apt update && sudo apt upgrade && \
yes | sudo apt install firmware-linux-nonfree && \


# Intel CPU support:
yes | sudo apt install software-properties-common apt-transport-https ca-certificates curl -y && \
yes | sudo apt install xserver-xorg-video-intel && \
yes | sudo apt install mesa-utils && \
yes | sudo apt install intel-opencl-icd libmfx1 && \
# yes | sudo apt install vlc (Choose the Flatpak version. Do it later.)
yes | sudo apt install libavcodec-extra && \
yes | sudo apt install libdvdread4 libdvdcss2 && \
yes | sudo dpkg-reconfigure libdvd-pkg && \

# Winamp alternative
# https://www.reddit.com/r/Ubuntu/comments/tno11g/looking_for_a_winamp_equivalent_for_ubuntu/
yes | sudo apt install audacious && \

# HDMI Display support:
yes | sudo apt install autorandr && \
yes | sudo apt install arandr && \

# MS Core Fonts:
# https://www.linuxcapable.com/how-to-install-microsoft-fonts-on-debian-linux/

yes | sudo apt update && sudo apt upgrade && \
yes | sudo apt-add-repository contrib non-free && \

# If the command fails,

yes | sudo apt install software-properties-common && \

# Install MS Fonts,

yes | sudo apt update && sudo apt upgrade && \
yes | sudo apt-add-repository contrib non-free && \
yes | sudo apt install ttf-mscorefonts-installer && \
# https://averagelinuxuser.com/microsoft-fonts-linux/#:~:text=Calibri%20and%20Cambria%20fonts,-Unfortunately%2C%20this%20package&text=These%20Google%20fonts%20are%20metric,package%20manager%20and%20install%20them
yes | sudo apt install fonts-crosextra-carlito fonts-crosextra-caladea && \
sudo fc-cache && \

yes | sudo apt install fonts-texgyre fonts-texgyre-math fonts-urw-base35 && \
yes | sudo apt install fonts-apropal fonts-beteckna fonts-breip fonts-cabin && \
yes | sudo apt install fonts-liberation fonts-liberation2 fonts-lindenhill fonts-oxygen && \
yes | sudo apt install fonts-play fonts-ubuntu fonts-ubuntu-console fonts-tiresias && \
yes | sudo apt install texlive-fonts-extra && \
yes | sudo apt install fonts-croscore && \
sudo fc-cache && \

yes | sudo apt install fonts-courier-prime && \
sudo fc-cache && \

yes | sudo apt install "fonts-gnutypewriter" && \
sudo fc-cache && \

# Charmap
yes | sudo apt install charmap.app && \


# Display dialog boxes
yes | sudo apt install zenity && \

# Themes and Icons:
# Search the web version of the Debian repository for the package.
# search the apt repo from the command line.
# Gray Bird:
# apt search greybird-gtk-theme
yes | sudo apt install greybird-gtk-theme && \
# Papyrus:
# apt search papirus-icon-theme
yes | sudo apt install papirus-icon-theme && \
# Numix:
yes | sudo apt install numix-* && \
# Paper:
yes | sudo apt install paper-icon-theme && \
# Obsidian:
yes | sudo apt install obsidian-icon-theme && \
# arc-theme
yes | sudo apt install arc-theme && \

# ================================================================================
#        PYTHON, PIP3, PIPX, CONDA (MINI), AND PYTORCH (CPU)
# ================================================================================
yes | sudo apt install python3-pip && \
# Don't issue the command: python -m pip install --upgrade pip
pip install pip-autoremove && \
#usage: pip-autoremove -y <package_name>
yes | sudo apt install pipx && \
# ================================================================================

yes | sudo apt install gnome-weather && \

# Note: You will need to follow the instructions on OpenSubtitlesDownload which requires python and zenity.

# https://github.com/emericg/OpenSubtitlesDownload.git

mkdir -p ~/.local/share/nautilus/scripts/ && \
cd ~/.local/share/nautilus/scripts/ && \
wget https://raw.githubusercontent.com/emericg/OpenSubtitlesDownload/master/OpenSubtitlesDownload.py && \
chmod u+x OpenSubtitlesDownload.py && \


# Rofi App Finder:

yes | sudo apt install rofi && \

yes | sudo apt install neofetch && \
yes | sudo apt install htop && \

# Snap and Flatpak:
# Synaptic Package Manager:
# yes | sudo apt install synaptic
# Install GNOME Software:
yes | sudo apt install gnome-software && \

# Snap:
yes | sudo apt update && sudo apt upgrade && \
yes | sudo apt install snapd && \
yes | sudo snap install core && \
yes | sudo snap install snap-store && \
# Update Snaps:
snap refresh --list && \
sudo snap refresh && \

# add '/snap/bin' to '$PATH'
# https://askubuntu.com/questions/965599/where-is-the-install-location-for-the-snap-download-tool
# .bashrc or .bash_aliases
export PATH="$PATH:/snap/bin/" && \

# Install a Firewall:
yes | sudo apt install gufw && \

# Install an Antivirus:
yes | sudo apt install chkrootkit && \

# Install System Restore/Maintenance Tools:
# Network Time Protocol daemon/utilities
yes | sudo apt install ntp && \
# tool for selecting tasks
yes | sudo apt install tasksel && \
# Partition Manager
yes | sudo apt install gparted && \
yes | sudo apt install gnome-disk-utility && \
# Volume/Drive/Container Encryption
## https://www.cyberciti.biz/security/howto-linux-hard-disk-encryption-with-luks-cryptsetup-command/
## http://security.stackexchange.com/questions/4590/ddg#4592
yes | sudo apt install gnome-disk-utility && \
yes | sudo apt install zulucrypt-gui zulucrypt-cli zulumount-gui libzulucrypt-plugins && \
yes | sudo apt install pmount && \
yes | sudo apt install luckyluks && \
yes | sudo apt install cryptsetup cryptmount cryptsetup-bin cryptsetup-initramfs cryptsetup-nuke-password && \
# File Sync
yes | sudo apt install rsync && \
yes | sudo apt install grsync && \
# System Restore
yes | sudo apt install timeshift && \
# Load Program Faster while launching for the second time
yes | sudo apt install preload && \
# seahorse: GUI Keyring Manager
# https://mexpolk.wordpress.com/2008/02/06/ubuntu-change-default-keyring-password/
yes | sudo apt install seahorse && \
# Reduce Eyestrain
yes | sudo apt install redshift-gtk && \
# Prevent Screen from falling asleep
#yes | sudo apt install caffeine
# Command-line system info tool
yes | sudo apt install hardinfo && \
# New hardware (firmware)
sudo update-initramfs -u && \
sudo apt-get install apt-file && \
sudo apt-file update && \

# The Fish Shell
yes | sudo apt install fish && \
# Power management utility for laptops.
yes | sudo apt install tlp && \
yes | sudo apt install tlp-rdw && \
# Set Up Bluetooth
# https://www.howtogeek.com/829360/how-to-set-up-bluetooth-on-linux/
yes | sudo apt install bluetooth bluemon bluez blueman && \
sudo systemctl enable bluetooth.service && \
sudo systemctl start bluetooth.service && \
rfkill unblock bluetooth && \

# Install OH-MY-BASH:
yes | sudo apt install curl git git-lfs fish -y && \
bash -c "$(curl -fsSL https://raw.githubusercontent.com/ohmybash/oh-my-bash/master/tools/install.sh)" && \

# Change the theme: .bashrc -> Uncomment:

# OSH_THEME="powerline-plain"
# OSH_THEME="powerline"
## OSH_THEME="brunton"
## OSH_THEME="kitsune"
# OSH_THEME="mairan"
# OSH_THEME="rr"

source ~/.bashrc && \

# autojump
# https://github.com/wting/autojump.git
yes | sudo apt install autojump && \
yes | sudo apt install fzf && \
echo '. /usr/share/autojump/autojump.sh' >> ~/.bashrc && \
source ~/.bashrc

# Or, (OMF:- OH-MY-FISH)
# https://github.com/oh-my-fish/oh-my-fish
yes | sudo apt install curl git fish -y && \
curl -L https://get.oh-my.fish | fish && \
# fish
# Theming:
# omf list
# omf theme
# omf install bobthefish
# omf install agnoster
# omf reload


# tldr
# https://github.com/tldr-pages/tldr.git
yes | sudo apt install python3-pip -y && \
pipx install tldr && \
# ---------
yes | sudo apt install libfuse2 && \
yes | sudo apt install psensor && \
yes | sudo apt install transmission && \
yes | sudo apt install surf && \

# A cross-platform dictionary similar to Wordweb
yes | sudo apt install artha && \
yes | sudo apt install bzip2 && \
yes | sudo apt install tar && \
yes | sudo apt install unrar && \
yes | sudo apt install rar && \
yes | sudo apt install xz-utils && \
yes | sudo apt install lrzip && \
yes | sudo apt install pixz && \
yes | sudo apt install wmctrl && \
yes | sudo apt install nscd && \
yes | sudo apt install xclip && \
yes | sudo apt install uget && \
yes | sudo apt install aria2 && \
yes | sudo apt install xarchiver && \
yes | sudo apt install thunar-archive-plugin && \
yes | sudo apt install wavemon && \
# Monitor the status of an 802.11 wireless ethernet link.
yes | sudo apt install wmwave && \
# Description: WiFi Share and Connect with QR.
yes | sudo apt install wifi-qr && \
# Launcher.
yes | sudo apt install rofi && \
# Description: graphical wireless scanner.
yes | sudo apt install linssid && \
# Screenshot Utility.
yes | sudo apt install flameshot && \
# Defrag NTFS Volumes.
yes | sudo apt install ntfs-3g && \

# Download Manager programs
yes | sudo apt install uget && \

# Basic build tools you'll need:

yes | sudo apt install build-essential && \
yes | sudo apt install patch && \
yes | sudo apt install make && \
yes | sudo apt install bear && \
yes | sudo apt install cmake && \
yes | sudo apt install diffutils && \

yes | sudo apt install libomp-dev && \
yes | sudo apt install curl && \
yes | sudo apt install python3-pip && \
python -m pip install --upgrade pip && \
yes | sudo apt install pipx && \

yes | sudo apt install git git-lfs gitk git-gui && \
yes | sudo apt install unzip && \
# MATE archive manager. Works in XFCE
yes | sudo apt install engrampa engrampa-common && \
# Generic archive manager. Works in XFCE
yes | sudo apt install xarchiver && \
yes | sudo apt install thunar-archive-plugin && \
yes | sudo apt install wget curl && \

yes | sudo apt install notepadqq && \

sudo apt update && \
sudo apt list --upgradable && \
sudo apt upgrade && \
sudo apt update && \
yes | sudo apt install -f && \
yes | sudo apt install nodejs && \
yes | sudo apt install jq && \
# Description: package manager for Node.js
# (npm: Unmet dependencies)

yes | sudo apt install npm && \

# Update Node.js with NPM (Node Package Manager)
# https://phoenixnap.com/kb/update-node-js-version

yes | sudo apt install npm && \
npm cache clean -f && \
sudo npm install -g n && \
sudo n stable && \

# How To Compare Two Directories on Linux:
# https://www.baeldung.com/linux/compare-two-directories
# https://askubuntu.com/questions/651166/best-alternative-for-winmerge#661055

yes | sudo apt install meld && \
yes | sudo apt install diffuse && \
yes | sudo apt install kdiff3-qt  && \

# Command-line file manager:
yes | sudo apt install mc && \

# You might be interested in the following also:

yes | sudo apt install llvm && \
yes | sudo apt install clang && \
yes | sudo apt install clangd && \
yes | sudo apt install clang-tidy && \
yes | sudo apt install clang-tools && \
yes | sudo apt install lld && \
pipx install flawfinder && \
pipx install lizard && \
# https://github.com/joeyespo/grip
# Render local readme files before sending off to GitHub.
pipx install grip && \
# https://github.com/friendlyanon/cmake-init
pipx install cmake-init && \
# https://github.com/gni/offvsix
# offvsix: Offline Visual Studio Code Extension Downloader
pipx install offvsix && \

# Bash Language Server
# https://github.com/bash-lsp/bash-language-server.git
sudo npm i -g bash-language-server && \
# bash-language-server --help

# Description: blackbox testing of Unix command line programs
# cmdtest black box tests Unix command line tools. Roughly, it is given a
# script, its input files, and its expected output files. cmdtest runs
# the script, and checks the output is as expected.
yes | sudo apt install cmdtest && \
# pnpm package manager
# https://pnpm.io/installation
curl -fsSL https://get.pnpm.io/install.sh | sh - && \
# other essential development utilities
yes | sudo apt install cdecl && \
yes | sudo apt install cutils && \
yes | sudo apt install kitty && \
yes | sudo apt install sakura && \
# yes | sudo apt install gnome-terminal
yes | sudo apt install tree && \
yes | sudo apt install mc && \
yes | sudo apt install xclip && \
yes | sudo apt install vim-gtk3 && \
yes | sudo apt install kate && \
yes | sudo apt install cppcheck && \
yes | sudo apt install cppcheck-gui && \
yes | sudo apt install splint && \
yes | sudo apt install cmake cmake-gui && \
yes | sudo apt install wget && \
yes | sudo apt install unzip && \
yes | sudo apt install git && \
yes | sudo apt install git-lfs && \

# https://softwarerecs.stackexchange.com/questions/30351/visualizing-git-diff-linux#30352
# gitk & git-gui
# Both can show results graphically when launched from the directory
# containing .git folder. These are the simplest alternatives
# to dealing with the command-line diff/merge/commit/stage/push tools.
# Can be supplementary utilities even when a CUI is preferred over the GUI.

yes | sudo apt install gitk && \
yes | sudo apt install git-gui && \
yes | sudo apt install giggle && \

# Below are some (terminal-based) utilities for adding more
# functionalities to the existing Git installation

yes | sudo apt install git-extras && \
yes | sudo apt install git-flow && \
yes | sudo apt install diffutils && \
yes | sudo apt install diffstat && \

# Debuggers, code profilers, memory leak testers, build tools,
# code formatting, code/directory compare applications and more

yes | sudo apt install ddd && \
yes | sudo apt install valgrind && \
yes | sudo apt install cgdb && \
yes | sudo apt install astyle && \
yes | sudo apt install universal-ctags && \
yes | sudo apt install autoconf && \
yes | sudo apt install pkg-config && \
yes | sudo apt install libx11-dev && \
yes | sudo apt install libglib2.0-doc && \
yes | sudo apt install libtool && \
yes | sudo apt install autoproject && \
yes | sudo apt install autogen && \
yes | sudo apt install autotools-dev && \
yes | sudo apt install automake && \
yes | sudo apt install m4 && \
yes | sudo apt install make && \
yes | sudo apt install ninja-build && \
yes | sudo apt install meld && \

# Markdown to HTML etc.
yes | sudo apt install markdown && \

# Text search utilities
yes | sudo apt install regexxer && \
# yes | sudo apt install vizigrep
yes | sudo apt install searchmonkey && \

yes | sudo apt install ripgrep ugrep && \
# ugrep --help

# PlatformIO ===========================================================
# CuteCOM: GUI Serial Monitor
# https://www.pragmaticlinux.com/2021/11/how-to-monitor-the-serial-port-in-linux/
yes | sudo apt install cutecom && \

# Req. by PlatformIO CORE CLI

# yes | sudo apt autoremove brltty
# or,
sudo apt purge --auto-remove brltty && \

yes | sudo apt update
# https://www.pragmaticlinux.com/2021/11/how-to-monitor-the-serial-port-in-linux/
yes | sudo apt install -y cutecom && \
# https://askubuntu.com/questions/786367/setting-up-arduino-uno-ide-on-ubuntu
# https://askubuntu.com/questions/781571/how-to-identify-devices-connected-to-serial-port
# https://unix.stackexchange.com/questions/390184/dmesg-read-kernel-buffer-failed-permission-denied
# https://0xsuk.github.io/posts/2022-07-19-how-to-install-ch340-on-ubuntu-22.04/
yes | sudo apt install -y hwinfo && \
yes | sudo apt install -y setserial && \
pipx install esptool && \

######################################################## TicTacSync
# https://sr.ht/~proflutz/TicTacSync/
# https://tictacsync.org/

yes | sudo apt install sox && \
pipx install tictacsync && \
pipx upgrade-all && \
# tictacsync -v sampleFiles
########################################################

# GIMP Essentials:
yes | sudo apt install abr2gbr && \
yes | sudo apt install gimp-data && \
yes | sudo apt install gimp-data-extras && \
yes | sudo apt install gimp-gmic && \
yes | sudo apt install gimp-gutenprint && \
yes | sudo apt install gimp-help-common && \
yes | sudo apt install gimp-help-en-gb && \
yes | sudo apt install gimp-lensfun && \
yes | sudo apt install gimp-plugin-registry && \
yes | sudo apt install gimp-texturize && \
yes | sudo apt install gimp-lensfun && \
yes | sudo apt install gtkam-gimp && \
yes | sudo apt install icc-profiles && \
yes | sudo apt install icc-profiles-free && \
yes | sudo apt install gegl && \
yes | sudo apt install xzgv && \

# GIMP:
yes | sudo apt install gimp gimp-data gimp-data-extras gimp-gmic gimp-gutenprint gimp-help-common gimp-help-en-gb gimp-lensfun gimp-plugin-registry gimp-texturize icc-profiles icc-profiles-free gegl gtkam-gimp xzgv && \

# converter between LibreOffice document formats
# This package provides a commandline utility which can convert from
# any document format that LibreOffice can import to any document format
# it can export. It uses LibreOffice's UNO bindings for non-interactive
# conversion of documents.

yes | sudo apt install unoconv && \

# Webcam
# https://www.makeuseof.com/best-camera-apps-linux/
# https://www.linuxlinks.com/webcam/
yes | sudo apt install cheese && \

# The Suckless ST Terminal Emulator basic package:
# yes | sudo apt install stterm && \
# Or, Build it from the source
# https://github.com/bakkeby/st-flexipatch.git

# Terminal Fonts (MUST):
# * Without these fonts, you'll miss the proper console characters and see boxes everywhere.
yes | sudo apt install fonts-terminus fonts-terminus-otb xfonts-terminus && \
yes | sudo apt install xfonts-terminus-dos xfonts-terminus-oblique && \
yes | sudo apt install xfonts-mona fonts-firacode fonts-league-mono fonts-agave && \
yes | sudo apt install fonts-inconsolata fonts-ricty-diminished && \
yes | sudo apt install fonts-jetbrains-mono fonts-anonymous-pro && \
yes | sudo apt install fonts-monoid fonts-monoid-halfloose && \
yes | sudo apt install fonts-monoid-halftight fonts-monoid-loose fonts-monoid-tight && \
yes | sudo apt install fonts-fantasque-sans fonts-hermit fonts-powerline && \
# https://github.com/ryanoasis/nerd-fonts

# Bangla/Hindi Support
# apt search bengali
# apt search beng
# apt search hin
# apt search hindi
# https://packages.debian.org/en/stable/fonts-indic
# https://medium.com/the-blog-of-ehsan-nazim/write-bangla-easily-on-debian-9xfce-4470019d6272
# https://www.quora.com/How-can-I-install-Hindi-and-other-Indian-language-fonts-on-Kali-Linux
yes | sudo apt install fonts-indic && \
yes | sudo apt install ibus ibus-m17n m17n-db ibus-gtk && \
yes | sudo apt install fonts-beng fonts-beng-extra fonts-lohit-beng-bengali firefox-esr-l10n-bn && \
# Hindi:
yes | sudo apt install fonts-indic firefox-esr-l10n-hi-in fonts-deva-extra fonts-gargi fonts-lohit-deva && \

# Dictionary support for gnu-aspell (if req.):
yes | sudo apt install aspell-bn && \
yes | sudo apt install aspell-hi && \

# Install Fonts in Debian:
# https://vitux.com/how-to-install-custom-fonts-in-debian/
sudo apt update && sudo apt -y install font-manager && \
# Restart the machine.

# pnpm package manager:
echo "If you've executed the first install script 01_debian_essential.sh already, you have pnpm installed on your system. (yes I did = 1. No, I did not = 0)"
read choice
if [ "${choice}" != '1' ]; then
  echo "Ok!"
   sleep 1
   # https://pnpm.io/installation
   curl -fsSL https://get.pnpm.io/install.sh | sh -

fi

# Install 'c': Use C as a shell scripting language:
echo "If you've installed the 'c' scripting language support already, type 0 to skip installing it again. Type any other numbers to proceed with the installation."
echo "https://github.com/ryanmjacobs/c"
read choice
if [ "${choice}" != '0' ]; then
  echo "Ok! You'll install the 'c' scripting language support."
   sleep 1
   # ------------------------------------------------------------------------------
   # Install 'c': Use C as a shell scripting language:
   # Refer to '01_debian_essential.sh'.
   # https://github.com/ryanmjacobs/c
   cd ~/
   yes | sudo apt install build-essential trash-cli
   wget https://raw.githubusercontent.com/ryanmjacobs/c/master/c
   sudo install -m 755 c /usr/bin/c
   trash c
   # ------------------------------------------------------------------------------
else
  echo "Skipping..."
  sleep 1

fi

# =================================================================
# # https://askubuntu.com/questions/800155/service-command-not-found
# service: command not found
# Solve the problem by adding
# export PATH="$PATH:/usr/sbin"
# to your .bashrc, .bash_aliases, .bash_profile, .profile
# =================================================================

# export PATH="$PATH:/usr/sbin"

touch .bash_profile  && \

printf "Add the following entry,\n  then write changes & exit.\n"
echo "    export PATH="'"$PATH:/usr/sbin"'"    "
echo "file:  .bash_profile"

echo "export PATH="'"$PATH:/usr/sbin"'"" >> ~/.bash_profile

sleep 3
######################mousepad .bash_profile  && \
# https://askubuntu.com/questions/108258/what-is-the-bash-equivalent-of-doss-pause-command
read -p ""  && \
# https://stackoverflow.com/questions/8467424/echo-newline-in-bash-prints-literal-n?rq=1
printf "Add the following entry,\n  then write changes & exit.\n"
echo "    export PATH="'"$PATH:/usr/sbin"'"    "
echo "file:  .bashrc"

echo "export PATH="'"$PATH:/usr/sbin"'"" >> ~/.bashrc

sleep 3
######################mousepad .bashrc  && \
read -p ""  && \
# https://stackoverflow.com/questions/8467424/echo-newline-in-bash-prints-literal-n?rq=1
printf "Add the following entry,\n  then write changes & exit.\n"
echo "    export PATH="'"$PATH:/usr/sbin"'"    "
echo "file:  .bash_aliases"

echo "export PATH="'"$PATH:/usr/sbin"'"" >> ~/.bash_aliases

sleep 3
######################mousepad .bash_aliases  && \
read -p ""  && \
# https://stackoverflow.com/questions/8467424/echo-newline-in-bash-prints-literal-n?rq=1
printf "Add the following entry,\n  then write changes & exit.\n"
echo "    export PATH="'"$PATH:/usr/sbin"'"    "
echo "file:  .profile"

echo "export PATH="'"$PATH:/usr/sbin"'"" >> ~/.profile

sleep 3
######################mousepad .profile  && \
# https://askubuntu.com/questions/108258/what-is-the-bash-equivalent-of-doss-pause-command
read -p " "  && \
sleep 1
source "/home/$(whoami)/.bashrc"  && \
source "/home/$(whoami)/.bash_aliases"  && \
source "/home/$(whoami)/.bash_profile"  && \
source "/home/$(whoami)/.profile"  && \

# =================================================================
# pip3 packages - path setup (END)
# =================================================================

# =================================================================
# pip3 packages - path setup
# =================================================================

# export PATH="$HOME/.local/bin/:$PATH"

touch .bash_profile  && \
# https://stackoverflow.com/questions/8467424/echo-newline-in-bash-prints-literal-n?rq=1
printf "Add the following entry,\n  then write changes & exit.\n"
echo "    export PATH="'"$HOME/.local/bin/:$PATH"'"    "
echo "file:  .bash_profile"

echo "export PATH="'"$HOME/.local/bin/:$PATH"'"" >> ~/.bash_profile


sleep 3
######################mousepad .bash_profile  && \
# https://askubuntu.com/questions/108258/what-is-the-bash-equivalent-of-doss-pause-command
read -p ""  && \
# https://stackoverflow.com/questions/8467424/echo-newline-in-bash-prints-literal-n?rq=1
printf "Add the following entry,\n  then write changes & exit.\n"
echo "    export PATH="'"$HOME/.local/bin/:$PATH"'"    "
echo "file:  .bashrc"

echo "export PATH="'"$HOME/.local/bin/:$PATH"'"" >> ~/.bashrc

sleep 3
######################mousepad .bashrc  && \
read -p ""  && \
# https://stackoverflow.com/questions/8467424/echo-newline-in-bash-prints-literal-n?rq=1
printf "Add the following entry,\n  then write changes & exit.\n"
echo "    export PATH="'"$HOME/.local/bin/:$PATH"'"    "
echo "file:  .bash_aliases"

echo "export PATH="'"$HOME/.local/bin/:$PATH"'"" >> ~/.bash_aliases

sleep 3
######################mousepad .bashrc  && \
# https://askubuntu.com/questions/108258/what-is-the-bash-equivalent-of-doss-pause-command
read -p " "  && \
sleep 1
source "/home/$(whoami)/.bashrc"  && \
source "/home/$(whoami)/.bash_profile"  && \
source "/home/$(whoami)/.profile"  && \

# =================================================================
# pip3 packages - path setup (END)
# =================================================================

# =================================================================
# Lock the Desktop folder on Linux
# =================================================================

# to avoid cluttering your Desktop with files and folders
# that in turn spoil the beauty of the installation
# https://www.cyberciti.biz/faq/howto-set-readonly-file-permission-in-linux-unix/
# https://chmodcommand.com/chmod-444/
# https://chmodcommand.com/
# Example: chmod 0444 permissiontest/
# Where 'permissiontest' is the intended folder to be locked
# Unlock:
# https://www.linux.com/training-tutorials/how-manage-file-and-folder-permissions-linux/
# chmod u+rw permissiontest/

yes | sudo chmod 0444 ~/Desktop/ && \

# Unlock (if you ever need):
# sudo chmod u+rw ~/Desktop/
# =================================================================
# Lock the Desktop folder on Linux (END)
# =================================================================


# VeraCrypt
# https://www.veracrypt.fr/en/Downloads.html
yes | sudo apt install libwxgtk3.2-1 && \
# sudo apt --fix-broken install
# sudo dpkg -i  veracrypt-x.xx.x-Debian-xx-amd64.deb \

# pnpm package manager:
echo "If you've executed the first install script 01_debian_essential.sh already, you have pnpm installed on your system. (yes I did = 1. No, I did not = 0)"
read choice
if [ "${choice}" != '1' ]; then
  echo "Ok!"
   sleep 1
   # https://pnpm.io/installation
   curl -fsSL https://get.pnpm.io/install.sh | sh -

fi

# Install 'c': Use C as a shell scripting language:
echo "If you've installed the 'c' scripting language support already, type 0 to skip installing it again. Type any other numbers to proceed with the installation."
echo "https://github.com/ryanmjacobs/c"
read choice
if [ "${choice}" != '0' ]; then
  echo "Ok! You'll install the 'c' scripting language support."
   sleep 1
   # ------------------------------------------------------------------------------
   # Install 'c': Use C as a shell scripting language:
   # Refer to '01_debian_essential.sh'.
   # https://github.com/ryanmjacobs/c
   cd ~/
   yes | sudo apt install build-essential trash-cli
   wget https://raw.githubusercontent.com/ryanmjacobs/c/master/c
   sudo install -m 755 c /usr/bin/c
   trash c
   # ------------------------------------------------------------------------------
else
  echo "Skipping..."
  sleep 1

fi

# =================================================================
# cpplint
# =================================================================
# https://pypi.org/project/cpplint/

pipx install cpplint \

echo "Install Flint++? (Yes, do it = 1. No = anything else.)."
read choice
if [ "${choice}" != '0' ]; then
  echo "Ok! Installing Flint++."
   sleep 1
   # Flint++
   # https://github.com/JossWhittle/FlintPlusPlus
   # Create a symbolic link:
   cd ~/
   rm -rf ~/FlintPlusPlus
   git clone https://github.com/JossWhittle/FlintPlusPlus.git

   rm -rf ~/FlintPlusPlus/.git
   rm -rf ~/FlintPlusPlus/bin/deb32
   rm -rf ~/FlintPlusPlus/bin/raspberry\ pi/
   rm -rf ~/FlintPlusPlus/bin/Win32
   rm -rf ~/FlintPlusPlus/bin/x64
   rm -rf ~/FlintPlusPlus/debian
   rm -rf ~/FlintPlusPlus/flint
   rm ~/FlintPlusPlus/.gitattributes ~/FlintPlusPlus/.gitignore ~/FlintPlusPlus/flint++.1


   echo "Type 1 (numeric one) if you already have Flint++ on your system."
   read choice
   if [ "${choice}" != '0' ]; then
     # Performing checks before running this automated installation script for the second time.

     sudo rm /usr/bin/flint++

    fi

   sudo ln -s ~/FlintPlusPlus/bin/deb64/flint++ /usr/bin/flint++
   chmod +x ~/FlintPlusPlus/bin/deb64/flint++

   # Ref: https://github.com/mcandre/linters
else
  echo "Ok, skipping..."
  sleep 1

fi

# =================================================================
# cpplint (END)
# =================================================================

echo "--------------------------------------"
echo "Done!"
echo "--------------------------------------"

