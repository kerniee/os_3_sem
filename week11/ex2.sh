J=lofsdisk

echo Matvey > $J/file1
echo Abramov > $J/file2
sudo chmod 777 $J/

# Copy programs
sudo mkdir -p $J/{bin,lib64,lib}
sudo cp /bin/{bash,cat,echo,ls} $J/bin

# Copy shared libs
list="$(ldd /bin/bash | egrep -o '/lib.*\.[0-9]')"
for i in $list; do sudo cp "$i" "${J}${i}"; done

list="$(ldd /bin/cat | egrep -o '/lib.*\.[0-9]')"
for i in $list; do sudo cp "$i" "${J}${i}"; done

list="$(ldd /bin/echo | egrep -o '/lib.*\.[0-9]')"
for i in $list; do sudo cp "$i" "${J}${i}"; done

list="$(ldd /bin/ls | egrep -o '/lib.*\.[0-9]')"
for i in $list; do sudo cp "$i" "${J}${i}"; done

# Compile and copy program
sudo gcc -0 ex2.out ex2.c
sudo cp ./ex2.out $J/

echo "----Change root----" > ex2.txt
# Change root directory and run
sudo chroot $J ./ex2.out >> ex2.txt

echo '----Do not change root----' >> ex2.txt
# Run program again nd save output
./ex2.out >> ex2.txt
