#!/bin/bash

yes | sudo apt update && sudo apt upgrade && \
yes | sudo apt update && \
yes | sudo apt list --upgradable && \
yes | sudo apt upgrade && \
yes | sudo apt update && \
yes | sudo apt install -f && \

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
sudo apt install fish \

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
yes | sudo apt install libwxgtk3.2-1 \
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

pipx install cpplint && \

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

