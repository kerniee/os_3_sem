J=lofsdisk

echo Matvey > $J/file1
echo Abramov > $J/file2
chmod 777 $J/

# Copy programs
mkdir -p $J/{bin,lib64,lib}
cp /bin/{bash,cat,echo,ls} $J/bin

# Copy shared libs
list="$(ldd /bin/bash | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp "$i" "${J}${i}"; done

list="$(ldd /bin/cat | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp "$i" "${J}${i}"; done

list="$(ldd /bin/echo | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp "$i" "${J}${i}"; done

list="$(ldd /bin/ls | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp "$i" "${J}${i}"; done

# Copy program
cp ./ex2.out $J/

echo "----Change root----" > ex2.txt
# Change root directory and run
sudo chroot $J ./ex2.out >> ex2.txt

echo '----Do not change root----' >> ex2.txt
# Run program again nd save output
./ex2.out >> ex2.txt
