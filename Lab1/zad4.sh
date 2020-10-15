#!/bin/bash

#Polecenie shift usuwa pierwszy argument i przesuwa reszte w lewo tzn 
#wyoanie ./zad4 -m 5
# $1 == -m po shift $1 == 5 



while [ "$1" != "" ];
do
   case $1 in
   -m) shift
        arg0=$1
        ;;
   -n) shift
   		arg1=$1
        ;;
   -a) shift             
        arg2=$1  
        ;;
    *)  echo "Bledny argument $1"
        echo "Uzycie ./zad4 -m ilosc_dni -n rozszerzenie_pliku -a nazawa_archiwum"
        echo "Przyklad ./zad4 -m 5 -n txt -a archiwum"
        exit 
    ;;
    esac

    shift
done
if [ -z "$arg0" ]
then
      echo "Podaj ilosc dni: ";
      read;
      arg0=${REPLY}
fi

if [ -z "$arg1" ]
then
      echo "Podaj rozszerzeniec: ";
      read;
      arg1=${REPLY}
fi

if [ -z "$arg2" ]
then
      echo "Podaj nazwe archiwum: ";
      read;
      arg2=${REPLY}
fi

find -iname "*.$arg1" -mtime -$arg0 > pliki
tar -cvf $arg2.tar.gz -T pliki 