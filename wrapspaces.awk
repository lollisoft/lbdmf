BEGIN {
}
/ / {
	printf("\"%s\"\n", $0);
	next;
}
{
	print $0;
}
