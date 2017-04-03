i=0
for f in `ls images/`; do
	if [[ $i -eq 10 ]]; then
		let "i=0"
		readlink -f "images/$f" >> valid.txt
	else
		readlink -f "images/$f" >> train.txt
		let "i++"
	fi
done
	