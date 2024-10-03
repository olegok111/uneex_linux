tputcomfile=$(mktemp)
x=0
y=0
while read -r -N 1 char; do
    char_octal=$(echo -ne "$char" | od -b -A none)
    char_octal=${char_octal# }
    echo -n "tput cup $y $x; printf '\\$char_octal'" >> $tputcomfile

    if [ $1 ]; then
        echo "; sleep $1" >> $tputcomfile
    else
        echo >> $tputcomfile
    fi

    if [ "$char_octal" = '012' ]; then
        y=$((y+1))
        x=0
    else
        x=$((x+1))
    fi
done
echo tput clear > ${tputcomfile}2
shuf $tputcomfile >> ${tputcomfile}2
chmod +x ${tputcomfile}2
${tputcomfile}2
rm -f $tputcomfile ${tputcomfile}2
tput cup $((y+1)) 0
