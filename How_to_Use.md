# The short 'HOW TO' guide:

Although the repository is named `ubuntu-script-runner-c`, it has been tested on Debian. At the project's inception, I was using Xubuntu, an official flavour of Ubuntu that features the XFCE GUI.

The program `installscriptrunner` will function on other distributions with minor modifications to the configuration files. Sample configuration files are included in a ZIP archive. These are the configuration files I use on my Debian machine.

## Steps to Follow:

Here are the steps to follow, presented as clearly and concisely as possible.

The repository [Pinaki82/Debian-minimal](https://github.com/Pinaki82/Debian-minimal.git) provides a thorough guide for installing Debian on your system. You can refer to the file named [00_debian-fresh-install.txt](https://github.com/Pinaki82/Debian-minimal/blob/main/00_debian-fresh-install.txt) for comprehensive details. Transfer/download the PDF version of this page to your phone. You will be able to access the links after opening [Pinaki82/Debian-minimal](https://github.com/Pinaki82/Debian-minimal.git) in your phone's browser.

---

### Step 1: Print or write down the following section (1).

Troubleshoot a blank screen after crossing the GRUB Menu section:

Ref: https://forums.debian.net/viewtopic.php?t=63844

Press `e` when the GRUB menu appears.
Find the line containing `ro quiet`.
Add the following commands to the end of the line,

```text
splash nomodeset
```

The line will look something like this:

`... ro quiet splash nomodeset`

**`CTRL`+`X`** [NOTE: On VirtualBox, use the Soft Keyboard from the menu bar.]

Install the OS. After installing the OS, you will need to repeat this step.

---

### Step 2: Enter the GUI desktop.

Once you enter the desktop:

Add the current user to `sudoers`:

```bash
su
sudo su root
sudo nano /etc/sudoers
```

Find the section:

```bash
root  ALL=(ALL:ALL) ALL
```

Then, add your username there as described below.

-------------------------------------

```bash
#User privilege specification
root  ALL=(ALL:ALL) ALL
yourusername ALL=(ALL: ALL) ALL
```

`yourusername` -> Your actual username.

-------------------------------------

Reboot the system.

```bash
sudo reboot now
```

Add the current user to `sudoers` again by doing:

```bash
sudo usermod -aG sudo $(whoami)
```

Edit the GRUB Bootloader:

Ref: https://unix.stackexchange.com/questions/538562/how-do-i-edit-grub-cfg-and-save-it

```bash
sudo nano /etc/default/grub
```

Find the line containing `ro quiet`.

Add the following in the same line:

```bash
splash nomodeset
```

If it was present, please leave everything as it is.

Issue the commands:

```bash
sudo update-grub
sudo update-grub2
```

> Hint: You are currently not seeing messages from other users and the system.
>      Users in groups 'adm', 'systemd-journal' can see all messages.
>      Pass -q to turn off this notice.
> Ref: https://serverfault.com/questions/717725/journalctl-access-for-non-root-users

```bash
sudo usermod -a -G systemd-journal $(whoami)
sudo reboot now
```

Update the system:

```bash
yes | sudo apt update && sudo apt upgrade
```

Do the following (issue commands):

> =========================================================
> 
> https://askubuntu.com/questions/800155/service-command-not-found
> 
> service: command not found
> 
> Solve the problem by adding
> 
> export PATH="$PATH:/usr/sbin"
> 
> to your .bashrc, .bash_aliases, .bash_profile, .profile
> 
> ==========================================================

```bash
echo "export PATH="'"$PATH:/usr/sbin"'"" >> ~/.bash_profile
echo "export PATH="'"$PATH:/usr/sbin"'"" >> ~/.bashrc
echo "export PATH="'"$PATH:/usr/sbin"'"" >> ~/.bash_aliases
echo "export PATH="'"$PATH:/usr/sbin"'"" >> ~/.profile
```

Add `$HOME/.local/bin/` to the `PATH`, for `pip/cargo/pipx`, etc.:

```bash
echo "export PATH="'"$HOME/.local/bin/:$PATH"'"" >> ~/.bash_profile
echo "export PATH="'"$HOME/.local/bin/:$PATH"'"" >> ~/.bashrc
echo "export PATH="'"$HOME/.local/bin/:$PATH"'"" >> ~/.bash_aliases
```

---

### Step 3: Execute `the_basics.sh`.

Execute the `the_basics.sh` shell script. Make sure to set the necessary permissions to execute the file by using the command: `chmod +x the_basics.sh`.

```bash
chmod +x the_basics.sh
./the_basics.sh
```

Some programs require complex installation steps. Attempting to create a fully automated workflow without any manual intervention would not be feasible. Therefore, our `installscriptrunner` program cannot handle every aspect on its own. It is designed to install programs found in the distribution's repository and to perform tasks that can be executed in a single command. However, it is not capable of executing nested bash scripts.

---

### Step 4: Build our `installscriptrunner` program.

If the executable binary for the X86_64 platform is not provided in the build directory, build it from source. Look at [BUILDING.md](https://github.com/Pinaki82/ubuntu-script-runner-c/blob/main/BUILDING.md).

To be precise, the commands to execute are as follows:

```bash
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build
```

---

### Step 5: 🚨 Edit configs 🚨. Extract the sample configuration files for inspection and modification.

Please refer to the sample configuration files in the zip archive after extracting it. Make the necessary changes. You might not require all the software packages that I use. Utilise the Find and Replace feature in your text editor to substitute `YOURUSERNAME` with your actual username. You can choose from programs like Geany, Kate, GVim, or any other text editing software you prefer.

---

### Step 6: Execute our `installscriptrunner` program.

Enter the build directory: `cd build/`

Set permission parameters: `chmod +x installscriptrunner`

Execute: `/.installscriptrunner`

#### Choose the option `install config directory` first.

The rest are quite self-explanatory once you run the program. `installscriptrunner` will guide you through other stages. The remaining options are self-explanatory once you run the program. The program `installscriptrunner` will assist you through the other stages.
