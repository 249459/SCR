
#!/bin/bash 

LC_ALL=C

dzien=$(date +%w)# +%w numer dnia tygdnia 


if [ $dzien -eq 6 ] || [ $dzien -eq 7 ]; then
    echo "Weekend"
else

    echo "Dzien roboczy"
fi
