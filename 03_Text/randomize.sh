tputcomfile=$(mktemp)
y=0
while IFS= read -r str; do
    x=0
    str_octal=$(echo -n "$str" | od -b -A none)
    str_octal=${str_octal# }

    for octbyte in $str_octal; do
        echo -n "tput cup $y $x; printf '\\$octbyte'" >> $tputcomfile
        x=$((x+1))

        if [ $1 ]; then
            echo "; sleep $1" >> $tputcomfile
        else
            echo >> $tputcomfile
        fi
    done

    y=$((y+1))
done
echo tput clear > ${tputcomfile}2
shuf $tputcomfile >> ${tputcomfile}2
chmod +x ${tputcomfile}2
${tputcomfile}2
rm -f $tputcomfile ${tputcomfile}2
tput cup $((y+1)) 0
