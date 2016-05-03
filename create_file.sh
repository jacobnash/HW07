#Matthew Greci, ECE 335, HW5, Dr. Nava
#!/bin/sh

FILE=file_to_read.txt
rm -f $FILE

for x in {a..z}
do
	echo "$x\c" >> $FILE
done
