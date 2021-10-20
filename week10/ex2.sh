declare -a FILES=(week01/file.txt week10/_ex2.txt)

# remove files
for file in "${FILES[@]}"
do
  [ ! -e "${file}" ] || rm "${file}"
done
[ ! -e ex1.txt ] || rm ex1.txt

mkdir week01
echo Matvey > week01/file.txt
mkdir week10
link week01/file.txt week10/_ex2.txt
INUM="$(ls -i week01/file.txt | grep -Eo '^[^ ]+')"
find . -inum "${INUM}" > ex2.txt
find . -inum "${INUM}" -exec rm {} \; >> ex2.txt