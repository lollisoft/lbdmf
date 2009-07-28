BEGIN {
	FS = " ";
}
{
	if (NR == 1) printf("%s %s", $1, $2);
}
