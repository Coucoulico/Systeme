#!/bin/bash
#'ce programme bach est pour le lancement du programme copier ecrit en c'
src=$1
dest=$2
if [ -f "/usr/local/bin/copier.exe" ];then
exec /usr/local/bin/copier.exe $src $dest 
else
	echo "aucun programme :'copier' n'est installer dans la machine !"