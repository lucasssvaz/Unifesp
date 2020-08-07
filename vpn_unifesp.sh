#!/bin/bash

pkgs=('git' 'build-essential' 'gettext' 'autoconf' 'automake' 'libproxy-dev' 'libxml2-dev' 'libtool' 'vpnc-scripts' 'zlib1g-dev' 'pkg-config' 'libgnutls28-dev')

file='/var/log/vpn_unifesp.log'

trap ctrl_c INT

function ctrl_c() {
	printf "\nDisconnecting...\n" | sudo tee -a $file
	sudo pkill -SIGINT openconnect
	sleep 3s
	sudo service network-manager reload
	exit 0
}

function run_install()
{ 
    printf "Installing Dependencies...\n" | sudo tee -a $file
    sudo apt-get install ${pkgs[@]} -y | sudo tee -a $file
    clear
}

printf 'Running Unifesp VPN Script\n' 2>&1 | sudo tee $file

printf 'Checking dependencies... ' 2>&1 | sudo tee -a $file

dpkg -s "${pkgs[@]}" >/dev/null 2>&1 || run_install | sudo tee -a $file

printf 'Dependencies Installed.\n' 2>&1 | sudo tee -a $file

printf 'Checking Openconnect... ' 2>&1 | sudo tee -a $file

if ! which openconnect &> /dev/null 2>&1; then
  	printf "Installing Openconnect...\n" | sudo tee -a $file
    cd /usr/src
    sudo git clone https://github.com/vrmiguel/openconnect-unifesp.git 2>&1 | sudo tee -a $file
    cd openconnect
    sudo ./autogen.sh 2>&1 | sudo tee -a $file
    sudo ./configure 2>&1 | sudo tee -a $file
    sudo make 2>&1 | sudo tee -a $file
    sudo make install 2>&1 | sudo tee -a $file
    sudo ldconfig 2>&1 | sudo tee -a $file
    clear
fi

printf 'Openconnect Installed.\n' 2>&1 | sudo tee -a $file

printf 'Connecting, press Ctrl+C to disconnect.\n' 2>&1 | sudo tee -a $file

sudo openconnect --protocol=gp pavpn.unifesp.br 2>&1 | sudo tee -a $file
