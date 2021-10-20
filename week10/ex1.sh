declare -a FILES=(_ex1.txt _ex1_1.txt _ex1_2.txt)

# remove files

for file in "${FILES[@]}"
do
  [ ! -e "${file}" ] || rm "${file}"
done
[ ! -e ex1.txt ] || rm ex1.txt

echo Matvey > _ex1.txt
ln _ex1.txt _ex1_1.txt
ln _ex1.txt _ex1_2.txt

for file in "${FILES[@]}"
do
  ls -i "${file}" >> ex1.txt
done



# User(Owner) Group Other(All other)
# chmod a|u|g|o (all, user, group, other) +|-|~|= rwx