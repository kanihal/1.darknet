BEGIN{
	personIndex=0
	chairIndex=56
}
{
	if ($7==0 && $8==0 && $10~"person"){
		print personIndex" "$2" "$3" "$4" "$5>> $6.txt
	}else if ($7==0 && $8==0 && $10~"chair"){
                print chairIndex" "$2" "$3" "$4" "$5>> $6.txt
        }

}
