#!/bin/bash
if [ -f "/usr/local/bin/copier" ];then
	 rm /usr/local/bin/copier
	 rm /usr/local/bin/copier.exe
fi
 cp \.copier.sh /usr/local/bin/copier
 cp \.copier.exe /usr/local/bin/copier.exe
 echo "
 ***********.  installation reussite   .************
      "
 echo "vous pouvez maintenant utiliser la comande 'copier' de la maniere suivante 
       copier params[source] [destination] 
       pour:
       1-copier un fichier vers un autre .
       2-copier un fichier dans un repertoire.
       3-copier un repertoire dans un repertoire."