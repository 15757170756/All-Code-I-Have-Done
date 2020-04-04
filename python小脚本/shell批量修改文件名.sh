find . -type f -name "* *" |
while read name; do
	na=$(echo $name | sed 's/\ //g')
	mv "$name" "$na"
done