tputcomfile=$(mktemp)
x=0
y=0
while read -N 1 char; do
    if [ "$char" = "\\" ]; then
        echo Gotcha! >> /tmp/backslashes
        char_octal='134'
    else
        char_octal=$(echo -ne "$char" | od -b -A none)
        char_octal=${char_octal# }
    fi
    echo "tput cup $y $x; printf '\\$char_octal'" >> $tputcomfile
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
rm $tputcomfile ${tputcomfile}2
tput cup $((y+1)) 0
