#!/bin/bash 

sudo apt-get install postfix mailutils -y

sciezka=$(pwd)

for adres in $(cat $sciezka/adresy.txt)
do
    mail -A $sciezka/spec*.pdf -s "PCV" $adres < $sciezka/tresc.txt
    echo $adres
done

