#!/bin/bash
if [ -f "/usr/local/bin/copier" ];then
sudo rm /usr/local/bin/copier
fi
if [ -f "/usr/local/bin/copier.exe" ];then
sudo rm /usr/local/bin/copier.exe
echo "programme 'copier' est bien desinstallé !"
else
	echo "le programme n'est pas installer sur votre machine !"
fi